# Heap

## 특징
- 완전 이진트리의 일종
- 완전히 정렬된 상태가 아니며 완전 이진트리와 다르게 중복값이 허용
- 삽입/삭제 시간 복잡도: O(logN)
- 우선순위 큐가 힙으로 많이 구현
- 최소 힙(MinHeap)과 최대 힙(MaxHeap)으로 나눠짐
  * 최소 힙: 부모 노드가 자식 노드보다 작아야 함
  * 최대 힙: 부모 노드가 자식 노드보다 커야 함

## 라이브러리 제외 코드
- 최소 힙
~~~java
import java.util.*;

public class MinHeap{
    private int size;//minHeap 안에 들어있는 정보 개수
    private ArrayList<Integer> minHeap;//최소 힙 구현
    
    public MinHeap(){//생성자
        minHeap = new ArrayList<Integer>();
        minHeap.add(0);//index 0에 필요없는 값 삽입 
        this.size = 0;
    }
    
    private int parent(int pos) {//부모 노드
        return pos / 2;
    }
    private int leftChild(int pos) {//왼쪽
        return (2 * pos);
    }

    private int rightChild(int pos) {//오른쪽
        return (2 * pos) + 1;
    }

    //현재의 노드가 자식 노드가 없는지 확인
    private boolean isLeaf(int pos) {
        return pos * 2 > size;
    }
    
    /*
    public void printHeap(){
        System.out.println(Arrays.toString(minHeap.toArray()));
    }*/
    
    public void insert(int input) {
        minHeap.add(input);
        int current = ++size;
        while (current > 1 && minHeap.get(current) < minHeap.get(parent(current))) {
            Collections.swap(minHeap, current, parent(current));
            current = parent(current);
        }
        //printHeap();
    }
    
    //Heap 맨 위(index 1) 삭제, 이후 minHeapify 진행
    public int delete(){
        if(size == 0){
            return 0;
        }
        
        //root 노드 삭제, 그리고 맨 마지막 노드를 minHeap root에 옮김
        int pop = minHeap.get(1);
        minHeap.set(1, minHeap.get(size));
        minHeap.remove(size--);
        
        //size가 0이 아니면 조정할 필요 있음
        if(size != 0)
            minHeapify(1);
        //printHeap();
        return pop;
    }
    
    //delete한 이후 minHeap 규칙에 맞게 변경
    private void minHeapify(int pos) {
        //자식 노드가 없으면 더이상 할 필요 없음
        if (isLeaf(pos)) {
            return;
        }

        //isLeaf가 false면 완전 이진트리이므로 왼쪽 노드 무조건 존재
        int minPos = leftChild(pos);
        int min = minHeap.get(leftChild(pos));

        //오른쪽 자식이 존재하고 왼쪽보다 오른쪽이 작다면 min 및 minPos 교체
        if (leftChild(pos) != size && minHeap.get(leftChild(pos)) > minHeap.get(rightChild(pos))) {
            minPos = rightChild(pos);
            min = minHeap.get(rightChild(pos));
        }
        
        //만약 부모가 자식보다 작으면 더이상 할 필요 없음
        if(min > minHeap.get(pos))
            return;
        else{//자식이 부모보다 작을 시 swap 진행하고 아래 노드로 이동
            Collections.swap(minHeap, pos, minPos);
            minHeapify(minPos);
        }
    }
}
~~~

## 사용 사례
- 우선순위 큐: 우선순위에 따라 작업을 처리할 때 사용
  * 시뮬레이션 시스템
  * 네트워크 트래픽 제어
  * 운영 체제에서의 작업 스케쥴링
  * 수치 해석적인 계산

## 정의 방법
- import java.util.PriorityQueue 로 우선순위 큐 라이브러리 import
- PriorityQueue\<E> pq = new PriorityQueue<>(); 통해 E 타입의 빈 우선순위 큐 정의

## 사용 메서드
- Queue와 기본적으로 동일
1. 수행 실패 시 예외 발생 메서드
  - pq.add(E item): item을 큐의 rear에 삽입
  - pq.element(): 큐의 front에 있는 item을 삭제하지 않고 반환
  - pq.remove(): 큐의 front에 있는 item 삭제 및 반환 
2. 수행 실패 시 false 또는 null 반환 메서드
  - pq.offer(E item): add(e)와 동일, 삽입 실패 시 false 반환
  - pq.peek(): element()와 동일, 삽입 실패 시 null 반환
  - pq.poll(): remove()와 동일, 삽입 실패 시 null 반환
- pq.isEmpty(): 비어있음 true, 아닐 시 false 반환

## 문제 사이트 및 코드
- Heap 파트: https://programmers.co.kr/learn/courses/30/parts/12117