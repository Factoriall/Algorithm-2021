import java.util.*;

class Solution {
    public String solution(int[] numbers) {
        String answer = "";

        //1. int형으론 Comparator 지정 불가능하므로 Integer형으로 변환
        //Integer[] nums = Arrays.stream(numbers).boxed().toArray(Integer[]::new);

        //2. List형으로 바꿔서 삽입 - 위 방법보다 더 빠름
        List<Integer> nums = new ArrayList<>();
        for(int i = 0; i < numbers.length; i++) {
            nums.add(numbers[i]);
        }
        
        //Array Comparator를 둘이 합친 것을 비교해서 더 큰 것을 오른쪽에 두는 방식으로 재정의
        Collections.sort(nums, new Comparator<Integer>(){
            @Override
            public int compare(Integer n1, Integer n2){
                String s1 = Integer.toString(n1);
                String s2 = Integer.toString(n2);
                
                int sum1 = Integer.parseInt(s1 + s2);
                int sum2 = Integer.parseInt(s2 + s1);
                
                return sum2 - sum1;
            }
        });
        
        //답에 삽입
        for (Integer i : nums){
            if(answer.isEmpty() && i == 0){}
            else
                answer += Integer.toString(i);
        }
        //비어있음 0 삽입
        if(answer.isEmpty()){
            answer += "0";
        }
        return answer;
    }
}