import java.util.*;

class Solution {
    public int solution(int bridge_length, int weight, int[] truck_weights) {
        //트럭의 무게 및 다리에 오른 시간을 기록하는 queue 정의
        Queue<int[]> q = new LinkedList<>();
        
        int totalWeight = 0;
        int answer = 1;//현재 시간
        for(int w : truck_weights){
            //1. 트럭이 다리를 지났다면 queue에서 꺼내기
            while(!q.isEmpty() && answer >= q.peek()[1] + bridge_length){
                totalWeight -= q.peek()[0];
                q.remove();
            }
            
            //2. 다리 위의 트럭 + 들어갈 트럭 무게가 한도보다 많이 나간다면 트럭 빠질 때 까지 대기
            while(totalWeight + w > weight){
                totalWeight -= q.peek()[0];
                answer = q.peek()[1] + bridge_length;
                q.remove();
            }
            
            //3. 트럭 출발 및 totalWeight, answer 갱신
            int[] pair = {w, answer};
            q.add(pair);
            
            totalWeight += w;
            answer += 1;
        }
        
        //4. 위 반복문 탈출 시 나머지 트럭 모두 처리
        while(!q.isEmpty()){
            answer = q.peek()[1] + bridge_length;
            q.remove();
        }
        
        return answer;
    }
}