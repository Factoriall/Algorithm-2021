import java.util.*;

class Solution {
    public int solution(int[] priorities, int location) {
        
        Queue<int[]> q = new LinkedList<>();
        
        for(int i = 0; i<priorities.length; i++){//중요도 및 index의 정보 저장
            int[] pair = {i, priorities[i]};
            q.add(pair);
        }
        
        Arrays.sort(priorities);//중요도가 낮은 것부터 배치 
        
        int answer = 1;
        int maxIdx = priorities.length - 1;
        
        while(true){
            int[] p = q.peek();
            int idx = p[0];
            int prior = p[1];
            
            System.out.println("idx: " + idx);
            System.out.println("location: " + location);
            
            if(prior < priorities[maxIdx]){//중요도가 높은 문서가 하나라도 존재 시 뒤로 빼기
                q.remove();
                int[] pair = {idx, prior};
                q.add(pair);
            }
            
            else{//중요도 높은 문서가 없을 시 문서 인쇄
                if(idx == location){
                    break;
                }
                q.remove();
                maxIdx -= 1;
                answer += 1;
            }
        }
        
        return answer;
    }
}