import java.util.*;

class Solution {
    public boolean solution(String[] phone_book) {
        boolean answer = true;

        //그대로 저장 시 시간 초과 발생하므로 쪼갤 필요! 
        //맨 앞자리를 기준으로 하는 2차원 ArrayList 생성
        //C++의 배열 내의 vector와 유사
        //Java에서는 array 내의 ArrayList는 에러를 발생시키므로 ArrayList 내 ArrayList로 생성해야됨
        ArrayList<ArrayList<String>> al = new ArrayList<ArrayList<String>>();
        for (int i = 0; i < 10; ++i) {
            ArrayList<String> row = new ArrayList<String>();
            al.add(row);
        }
        
        //맨 앞자리(0-9)를 확인하고 맞는 위치에 삽입
        for(String s : phone_book){
            int start = s.charAt(0) - '0';
            al.get(start).add(s);
        }
        
        for(ArrayList<String> numList : al){
            //compare 메서드 재정의 - String의 길이 순서대로
            Comparator<String> cmp = new Comparator<String>(){
                @Override
                public int compare(String o1, String o2){
                    return Integer.compare(o1.length(), o2.length());
                }
            };
            //sort 진행
            Collections.sort(numList, cmp);
            
            Boolean isFinished = false;//탈출 여부 확인 flag 설정
            //짧은 순서대로 정렬을 진행했으므로 뒤의 것과 비교해서 접두어 확인
            for(int i=0; i < numList.size(); i++){
                String s1 = numList.get(i);
                for(int j=i+1; j < numList.size(); j++){
                    String s2 = numList.get(j).substring(0, s1.length());
                    //equals는 value가 같은지 확인
                    //추신: ==의 경우 reference(객체 주소)가 같은지 확인
                    if(s1.equals(s2)){//같으면 접두어가 있다는 의미이므로 종료
                        answer = false;
                        isFinished = true;
                        break;
                    }
                    if(isFinished)
                        break;
                }
                if(isFinished)
                    break;
            }
            if(isFinished)
                break;
        }
        
        return answer;
    }
}