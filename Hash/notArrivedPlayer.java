import java.util.*;

class Solution {
    public String solution(String[] participant, String[] completion) {
        String answer = "";
        
        //key는 사람 이름, Integer는 같은 이름을 가진 사람의 숫자 기록
        Map<String, Integer> map = new HashMap<String, Integer>();
        
        //participant의 정보를 map에 삽입, 없으면 추가, 있으면 +1 갱신
        for(String p : participant){
            if(map.get(p) == null)
                map.put(p, 1);
            else
                map.put(p, map.get(p) + 1);
        }
        
        //도착한 사람의 정보를 map과 대조, 1명이면 제거하고 2명 이상이면 수 줄이기
        for(String c : completion){
            if(map.get(c) == 1)
                map.remove(c);
            else
                map.put(c, map.get(c) - 1);
        }
        
        //answer에 map에 홀로 남아있는 객체의 key를 저장
        answer = map.keySet().iterator().next();
        return answer;
    }
}