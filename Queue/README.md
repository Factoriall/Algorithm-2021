# Queue

## 특징
- 먼저 집어 넣은 데이터가 먼저 나오는 FIFO(First In First Out) 형식의 자료구조

## 라이브러리 제외 코드
~~~java

//LinkedList로 구현
public class MyQueue {
  private static class QueueNode {
    private T data;
    private QueueNode next;

    public QueueNode(T data) {//constructor
      this.data = data;
    }
  }

  private QueueNode first;//나가는 곳
  private QueueNode last;//들어가는 곳

  //add 메서드: last쪽에 data 넣기
  public void add(T item) {
    QueueNode t = new QueueNode(item);

    //끝 처리
    if (last != null) last.next = t;
    last = t;
    if (first == null) first = last;
  }

  //remove 메서드: first 쪽의 data 꺼내고 삭제
  public T remove() {
    if (first == null) throw new NoSuchElementException();
    T data = first.data;
    first = first.next;

    //끝 처리
    if (first == null) last = null;
    return data;
  }

  //peek 메서드: first쪽의 data 정보만 꺼내기
  public T peek() {
    if (first == null) throw new NoSuchElementException();
    return first.data;
  }
  //isEmpty 메서드: queue가 비었는지 확인
  public boolean isEmpty() {
    return first == null;
  }
}
~~~
- 출처: https://gmlwjd9405.github.io/2018/08/02/data-structure-queue.html

## 사용 사례
- 너비 우선 탐색(BFS, Breadth-First Search) 구현: 처리해야할 노드 리스트를 저장하는 용도로 큐 사용
- 캐시(Cache) 구현
- 우선순위가 같은 작업 예약(인쇄 대기열)
- 선입선출

## 정의 방법
- import java.util.Queue 및 import java.util.LinkedList 통해 라이브러리 import
- Queue\<E> queue = new LinkedList<>(); 통해 E 타입의 비어있는 큐 정의

## 사용 메서드
1. 수행 실패 시 예외 발생 메서드
  - queue.add(E item): item을 큐의 rear에 삽입
  - queue.element(): 큐의 front에 있는 item을 삭제하지 않고 반환
  - queue.remove(): 큐의 front에 있는 item 삭제 및 반환 
2. 수행 실패 시 false 또는 null 반환 메서드
  - queue.offer(E item): add(e)와 동일, 삽입 실패 시 false 반환
  - queue.peek(): element()와 동일, 삽입 실패 시 null 반환
  - queue.poll(): remove()와 동일, 삽입 실패 시 null 반환

## 문제 사이트 및 코드
- truckOnTheBridge.java(다리를 지나는 트럭): https://programmers.co.kr/learn/courses/30/lessons/42583
- printer.java(프린터): https://programmers.co.kr/learn/courses/30/lessons/42587