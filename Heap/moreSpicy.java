import java.util.*;

class Solution {
    public int solution(int[] scoville, int K) {
        int answer = 0;
        
        PriorityQueue<Integer> minHeap = new PriorityQueue<Integer>();
        
        //우선순위 큐에 삽입
        for(int s : scoville){
            minHeap.add(s);
        }
        
        int cnt = 0;
        //스코빌 지수 계산 및 조건 만족할때 까지 반복
        while(minHeap.peek() < K && minHeap.size() != 1 ){
            int first = minHeap.remove();
            int second = minHeap.remove();
            
            int scv = first + (second * 2);
            minHeap.add(scv);
            cnt++;
        }
        
        //answer 계산
        if(minHeap.peek() < K){
            answer = -1;
        }
        else{
            answer = cnt;
        }
        
        return answer;
    }
}