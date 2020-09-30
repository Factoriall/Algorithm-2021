import java.util.*;

class Solution {
    public int solution(int[][] jobs) {
        int answer = 0;
        //순서를 시작 순서, 같을 시 소요 시간이 짧은 순서대로
        Arrays.sort(jobs, new java.util.Comparator<int[]>() {
            public int compare(int[] a, int[] b) {
                if(a[0] < b[0])
                    return -1;
                else if(a[0] > b[0])
                    return 1;
                else{
                    if(a[1] < b[1])
                        return -1;
                    else if(a[1] > b[1])
                        return 1;
                    else
                        return 0;
                }
            }
        });

        //minHeap 기준: 소요 시간이 짧은 순서대로, 같을 시 시작이 빠른 순서대로
        PriorityQueue<int[]> minHeap = new PriorityQueue<int[]>(new Comparator<int[]>() {
            @Override
            public int compare(int[] a, int[] b) {
                return a[1] - b[1];
            }
        });

        int sum = 0;
        int endTime = 0;
        for(int[] job: jobs){
            int start = job[0];
            int duration = job[1];
            if(start >= endTime){//만약 endTime이 현재 start보다 크다면
                if(minHeap.isEmpty()){//비어있음 그냥 넣기
                    sum += duration;
                    endTime = start + duration;
                }
                else{//minHeap 내의 정보 중 가장 짧은 것을 꺼내서 사용
                    int firstEnd = endTime;
                    if(start == firstEnd)//같으면 이것도 비교대상에 추가
                        minHeap.add(job);

                    while(!minHeap.isEmpty() && start >= endTime){
                        int[] best = minHeap.remove();
                        int bs = best[0];
                        int bd = best[1];

                        int wait = endTime - bs;
                        sum += (bd + wait);
                        endTime += bd;
                        System.out.println("endTime: " + endTime + ", sum: " + sum);
                    }

                    if(start != firstEnd)//위에서 안 넣었으면 지금 넣기
                        minHeap.add(job);
                }
            }
            else{//endTime이 start보다 작다면 기다려야 하므로 heap에 투입
                minHeap.add(job);
            }
        }

        //heap 비우기
        while(!minHeap.isEmpty()){
            int[] best = minHeap.remove();
            int bs = best[0];
            int bd = best[1];

            sum += (bd + (endTime - bs));
            endTime += bd;
            //System.out.println("endTime: " + endTime + ", sum: " + sum);
        }
        answer = sum / jobs.length;
        return answer;
    }
}