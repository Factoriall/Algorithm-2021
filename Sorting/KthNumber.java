import java.util.*;

class Solution {
    public int[] solution(int[] array, int[][] commands) {
        int len = commands.length;
        int[] answer = new int[len];
        int idx = 0;
        for(int[] command : commands){
            int begin = command[0] - 1;
            int end = command[1] - 1;
            int order = command[2] - 1;
            
            //copyOfRange함수를 이용해 subArray를 구하기
            int[] subArray = Arrays.copyOfRange(array, begin, end+1);
            
            //오름차순 정렬
            Arrays.sort(subArray);
            
            //위치에 맞는 부분 찾기
            answer[idx++] = subArray[order];
        }
        return answer;
    }
}