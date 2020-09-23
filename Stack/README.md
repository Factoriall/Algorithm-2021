# Stack

## 특징
- 한쪽에서만 자료를 넣고 뺄 수 있는 LIFO(Last In Last Out) 형식의 자료구조
- 가장 최근에 추가된 것이 가장 먼저 제거될 항목

## 라이브러리 제외 코드
~~~java
//LinkedList로 구현
public class MyStack {
  private static class StackNode {
    private T data;//데이터 정보
    private StackNode next;//다음으로 꺼내야할 item 의미

    public StackNode(T data) {
      this.data = data;
    }
  }

  private StackNode top;//stack 맨 위의 item 가리킴

  //pop 함수: 맨 위에 data 가져오고 next로 이동
  public T pop() {
    if (top == null) throw new NoSuchElementException();
    T item = top.data;
    top = top.next;

    return item;
  }

  //push 함수: StackNode class의 item 생성 및 맨 위에 놓기
  public void push(T item) {
    StackNode t = new StackNode(item);
    t.next = top;
    top = t;
  }

  //peek 함수: 맨 위의 data 가져오기
  public T peek() {
    if (top == null) throw new NoSuchElementException();
    return top.data;
  }

  //isEmpty 함수: 스택이 비어있는지 확인
  public boolean isEmpty() {
    return top == null;
  }
}
~~~
- 출처: https://gmlwjd9405.github.io/2018/08/03/data-structure-stack.html

## 스택 사용 사례
- 재귀 알고리즘: 재귀적으로 함수 호출하는 경우에 임시 데이터를 스택에 넣어주고 backtrack할 때 스택에 넣었던 임시 데이터를 빼준다.
- 실행 취소(undo)
- 역순 문자열 만들기
- 수식 괄호 검사
- 후위 표기법 계산

## 정의 방법
- import java.util.Stack 통해 라이브러리 import
- Stack\<E> stack = new Stack<>(); 통해 E 타입의 빈 스택 정의

## 사용 메서드
- stack.push(E item): stack의 top에 item 삽입
- stack.pop(): stack의 top의 item 삭제하고 해당 item 반환
- stack.peek(): stack의 top의 item 삭제하지 않고 해당 item 반환
- stack.empty(): stack이 비어있을 시 true, 아닐 시 false 반환
- stack.search(Object o): 해당 Object와 일치하는 맨 위의 item 반환
  * stack의 top은 1, 그 아래로 수가 점점 늘어남
  * 해당 Object와 일치하는 item 없을 시 -1 반환 

## 문제 사이트 및 코드
- stockprice.java(주식가격): https://programmers.co.kr/learn/courses/30/lessons/42584
- development.java(기능개발): https://programmers.co.kr/learn/courses/30/lessons/42586
