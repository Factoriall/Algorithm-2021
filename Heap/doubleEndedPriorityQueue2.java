import java.util.*;

class Solution {
    public int[] solution(String[] operations) {
        int[] answer = new int[2];
        PriorityQueue<Integer> minHeap = new PriorityQueue<>(); 
        PriorityQueue<Integer> maxHeap = new PriorityQueue<>(Collections.reverseOrder());
        for(String operation : operations){
            String[] splited = operation.split(" ");
            int number = Integer.parseInt(splited[1]);

            //파싱한 정보에 따라 정보 삽입 및 삭제
            if(splited[0].equals("I")){
                minHeap.add(number);
                maxHeap.add(number);
            }
            else{
                if(!maxHeap.isEmpty()){
                    if(number == 1){
                        delete(minHeap, maxHeap.remove());
                    }
                    else{
                        delete(maxHeap, minHeap.remove());
                    }
                }
            }
        }

        if(minHeap.size() == 0){
            answer[0] = 0;
            answer[1] = 0;
        }
        else{
            answer[0] = maxHeap.peek();
            answer[1] = minHeap.peek();
        }
        
        return answer;
    }

    public void delete(PriorityQueue<Integer> pq, int num){
        List<Integer> temp = new ArrayList<>();
        while(!pq.isEmpty()) {
            int extract = pq.poll();
            if(extract == num) break;
            temp.add(extract);
        }
        pq.addAll(temp);
    }
}