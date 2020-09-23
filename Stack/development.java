import java.util.*;

class Solution {
    public int[] solution(int[] progresses, int[] speeds) {
        int finished = 0;
        int pnum = progresses.length;
        
        //ArrayList, Stack같은 라이브러리의 경우 int같은 primitive type을 지정하지 못함
        //Integer 같은 class type으로 지정해야됨
        ArrayList<Integer> answerList = new ArrayList<Integer>();
        
        Stack<Integer> stack = new Stack<>();
        int start = 0;
        for(int i = 0; i<pnum; i++){
            int remained = 100 - progresses[i];//남은 진도
            int day = remained / speeds[i];//걸리는 시간
            if(remained % speeds[i] != 0)//나머지가 있음 day에 1 추가
                day += 1;
            if(i == 0){//초기
                start = day;
            }
            
            //만약 start보다 남은 날이 많다면 stack 내의 모든 progress가 사용된다는 의미
            //stack 비워주고 start 갱신
            if(!stack.empty() && start < day){
                answerList.add(stack.size());
                stack.clear();
                start = day;
            }
            //stack에 정보 넣기
            stack.push(day);
        }
        
        //나머지 정보 answerList에 넣고 stack 비우기
        answerList.add(stack.size());
        stack.clear();
        
        int[] answer = {};
        
        //answer은 int[] 타입이므로 ArrayList를 int[] 타입으로 변경해줘야 함
        answer = answerList.stream().mapToInt(Integer::intValue).toArray();

        return answer;
    }
}