import java.util.*;

class Solution {
    //이중 우선순위 큐 구현
    static class DblEndedPQ {  
        Set<Integer> s;  
        DblEndedPQ() { 
            s = new HashSet<Integer>(); 
        } 
        // 큐의 사이즈 리턴
        // 시간 복잡도: O(1)  
        int size(){  
            return s.size();  
        }  
  
        // 큐가 비어있는지 확인
        // 시간 복잡도: O(1)  
        boolean isEmpty(){  
            return (s.size() == 0);  
        }  
  
        // 큐에 item 삽입
        // 시간 복잡도: O(logN)     
        void insert(int x) {  
            s.add(x);  
        }  
  
        // 큐 중 minimum 찾기  
        // 시간 복잡도: O(N) 
        int getMin(){  
            return Collections.min(s,null);  
        }  
  
        // 큐 중 maximum 찾기  
        // 시간 복잡도: O(N)  
        int getMax() {  
            return Collections.max(s,null);  
        }  
      
        // 큐 중 min 찾아서 삭제
        // 시간 복잡도: O(N) 
        void deleteMin(){  
            if (s.size() == 0)  
                return;  
            s.remove(Collections.min(s,null));  
         }  
  
        // 큐 중 max 찾아서 삭제
        // 시간 복잡도: O(N) 
        void deleteMax(){  
            if (s.size() == 0)  
                return ;  
            s.remove(Collections.max(s,null));     
        }  
    };
    
    public int[] solution(String[] operations) {
        int[] answer = new int[2];
        DblEndedPQ d = new DblEndedPQ(); 
        for(String operation : operations){
            String[] splited = operation.split(" ");
            int number = Integer.parseInt(splited[1]);

            //파싱한 정보에 따라 정보 삽입 및 삭제
            if(splited[0].equals("I")){
                d.insert(number);
            }
            else{
                if(number == 1){
                    d.deleteMax();
                }
                else{
                    d.deleteMin();
                }
            }
        }

        if(d.size() == 0){
            answer[0] = 0;
            answer[1] = 0;
        }
        else{
            answer[0] = d.getMax();
            answer[1] = d.getMin();
        }
        
        return answer;
    }
}