import java.util.*;

class Solution {
    public int solution(String[][] clothes) {
        //key는 의상 종류, value는 종류의 개수를 저장하는 map 생성
        Map<String, Integer> map = new HashMap<String, Integer>();

        //의상 종류에 맞게 map에 저장
        for(String[] cloth : clothes){
            if(map.get(cloth[1]) == null)
                map.put(cloth[1], 1);
            else
                map.put(cloth[1], map.get(cloth[1]) + 1);
        }
        
        //map의 의상 종류 개수를 활용해 answer 구하기
        int answer = 1;
        for (String key: map.keySet()) {
            answer *= (map.get(key) + 1);
        }
        
        return answer - 1;
    }
}