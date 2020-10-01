class Solution {
    public int solution(int[] citations) {
        int answer = 0;
        //Integer[] cites = Arrays.stream(citations).boxed().toArray(Integer[]::new);
        //Arrays.sort(cites, Collections.reverseOrder());
        Arrays.sort(citations); // 위 방법보다 이것이 훨씬 빠름
        
        /*for(int cite : cites){
            if(cite < answer+1)
                break;
            answer += 1;
        }*/
        
        //reverseOrder 억지로 하지 말고 반대로 돌리기
        for(int i = citations.length - 1; i >= 0 ; i--){
            if(citations[i] < answer+1)
                break;
            answer += 1;
        }
        return answer;
    }
}