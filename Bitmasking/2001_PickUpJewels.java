import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

public class Main {
	static int N, M, K;
	static boolean[][] isVisited;
	static List<Island> islands;
	
	static class IslandInQueue{
		int islandNum;
		int isVisited;
		
		IslandInQueue(int n, int iv){
			islandNum = n; isVisited = iv; 
		}
	}
	
	static class Island{
		List<Edge> adjs;
		int dpIdx = -1;
		
		Island(){
			adjs = new ArrayList<>();
		}
		
		void setExistense(int idx) {
			dpIdx = idx;
		}
		
		void addBridge(int to, int weight) {
			adjs.add(new Edge(to, weight));
		}
	}
	
	static class Edge{
		int to;
		int weight;
		Edge(int t, int w){
			to = t; weight = w;
		}
	}

	public static void main(String[] args) throws IOException {
		int i;
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");

		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		K = Integer.parseInt(st.nextToken());
		
		isVisited = new boolean[N][1<<K];
		
		islands = new ArrayList<>();
		for(i=0; i<N; i++) islands.add(new Island());
		for(i=0; i<K; i++) {
			int num = Integer.parseInt(br.readLine()) - 1;
			islands.get(num).setExistense(i);
		}
		
		//그래프 정보 저장
		for(i=0; i<M; i++) {
			st = new StringTokenizer(br.readLine(), " ");
			int c1 = Integer.parseInt(st.nextToken()) - 1;
			int c2 = Integer.parseInt(st.nextToken()) - 1;
			int w = Integer.parseInt(st.nextToken());
			
			islands.get(c1).addBridge(c2, w);
			islands.get(c2).addBridge(c1, w);
		}
		
		//BFS 구현
		Queue<IslandInQueue> q = new LinkedList<>();
		q.offer(new IslandInQueue(0, 0));
		isVisited[0][0] = true;
		
		int answer = 0;
		while(!q.isEmpty()) {
			int qSize = q.size();
			for(int t=0; t<qSize; t++) {
				IslandInQueue now = q.poll();
				int jewelNum = Integer.bitCount(now.isVisited);
				
				if(now.islandNum == 0) {//출발 지점으로 들어올 때마다 정보 갱신 
					int idx = islands.get(0).dpIdx;
					if(idx != -1 && ((now.isVisited & (1 << idx)) == 0)) answer = Math.max(answer, jewelNum + 1);
					else answer = Math.max(answer, jewelNum);
				}
				
				for(Edge next : islands.get(now.islandNum).adjs) {//다음 갈 수 있는 지역 탐색
					if(next.weight < jewelNum) continue;//다음 무게를 버틸 수 없으면 스킵
					
					Island nLand = islands.get(now.islandNum);
					if(nLand.dpIdx != -1) {
						int nextVisited = now.isVisited | (1<<nLand.dpIdx);
						if(next.weight != jewelNum && !isVisited[next.to][nextVisited]) {							
							q.add(new IslandInQueue(next.to, nextVisited));
							isVisited[next.to][nextVisited] = true;
						}
					}
					if(!isVisited[next.to][now.isVisited]) {
						q.add(new IslandInQueue(next.to, now.isVisited));
						isVisited[next.to][now.isVisited] = true;
					}
				}
			}
		}
		
		System.out.println(answer);
	}
}
