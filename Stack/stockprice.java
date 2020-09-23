import java.util.*;

class Solution {
    public int[] solution(int[] prices) {
        //index 및 price 배열을 저장하는 Stack 정의
        Stack<int[]> stack = new Stack<>();
        
        int length = prices.length;
        
        //answer 크기 지정
        int[] answer = new int[length];
        
        //price와 stack의 top과 비교
        //index - stack.peek()[0]를 통해 가격이 떨어진 시간 구할 수 있음
        int index = 0;
        for(int price : prices){
            while(!stack.empty() && stack.peek()[1] > price){
                answer[stack.peek()[0]] = index - stack.peek()[0];
                stack.pop();
            }
            int[] pair = {index, price};
            stack.push(pair);
            index++;
        }
        
        //결과 구하기 위해 계산하면서 stack 비워주기
        while(!stack.empty()){
            answer[stack.peek()[0]] = index - 1 - stack.peek()[0];
            stack.pop();
        }
    
        return answer;
    }
}