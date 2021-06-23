import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

public class Main {
	//고정 전역변수 값
	static int N;
	static int K;

	//비트마스킹을 활용해서 문제 풀기
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");

		N = Integer.parseInt(st.nextToken());
		K = Integer.parseInt(st.nextToken());
		
		int num = 0;
		st = new StringTokenizer(br.readLine(), " ");
		
		for(int i=0; i<N; i++) {
			int n = Integer.parseInt(st.nextToken()) - 1;			
			num <<= 3;
			num += n; 
		}
	
		//오름차순이 나왔을 때의 값을 비트를 이용해 나오는 값을 target으로 지정
		int target = 0;
		for(int i=0; i<N; i++) {
			target <<= 3;
			target += i;
		}
		
		HashSet<Integer> set = new HashSet<>();//isVisited
		Queue<Integer> q = new LinkedList<>();
		
		set.add(num);
		q.add(num);
		
		//bfs 사용
		int count = 0;
		while(!q.isEmpty()) {
			int qSize = q.size();
			for(int t=0; t<qSize; t++) {
				int now = q.poll();
				if(now == target) {//답이면 끝
					System.out.println(count);
					return;
				}
				
				for(int i=0; i<=N-K; i++) {
					int newNum = reverse(now, i);//특정 구역을 리버스하는 함수
					if(!set.contains(newNum)) {
						set.add(newNum);
						q.offer(newNum);
					}
				}
			}
			count++;
		}
		
		System.out.println(-1);
	}

	private static int reverse(int now, int start) {
		int delIdx = (start << 1) + K - 1;//바뀌는 수 2개의 합은 항상  delIdx로 고정
		for(int i=start; i<start + K/2; i++) {
			final int CMP = 7;//이진수 111은 7
			
			//바뀔 부분의 위치 지정
			int idx1 = (N - 1 - i) * 3;
			int idx2 = (N - 1 - (delIdx - i)) * 3;
			
			//바뀌는 부분의 이진수 부분 추출
			int swp1 = CMP & (now >> idx1);
			int swp2 = CMP & (now >> idx2);
			
			//바뀌는 부분의 위치의 비트를 모두 0으로 치환
			now = now & ~(CMP<<idx1);
			now = now & ~(CMP<<idx2);
			
			//0으로 된 부분을 스와핑해서 채워넣기
			now += swp1 << idx2;
			now += swp2 << idx1;			
		}
		
		return now;
	}



}
