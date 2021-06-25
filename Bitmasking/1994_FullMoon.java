import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

public class Main {
	static final int[] dy = {1, 0, -1, 0};
	static final int[] dx = {0, 1, 0, -1};
	static int N, M;
	static char[][] map;
	
	static class Point{
		int y, x;
		Point(int y, int x){
			this.y = y;
			this.x = x;
		}
	}
	
	static class Minsik{
		Point now;
		int keys;
		
		Minsik(Point now, int k){
			this.now = now;
			keys = k;
		}
	}

	public static void main(String[] args) throws IOException {
		int i, j;
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		map = new char[N][M];
		boolean[][][] isVisited = new boolean[N][M][1<<6];
		
		Minsik minsik = null;
		for(i=0; i<N; i++) {
			String row = br.readLine();
			for(j=0; j<M; j++) {
				map[i][j] = row.charAt(j);
				if(map[i][j] == '0') {//민식이 위치
					minsik = new Minsik(new Point(i,j), 0);
				}
			}
		}
		
		Queue<Minsik> q = new LinkedList<>();
		q.add(minsik);
		//System.out.println("now: (" +minsik.now.y + "," + minsik.now.x + ")");
		isVisited[minsik.now.y][minsik.now.x][0] = true;
		
		int answer = 0;
		while(!q.isEmpty()) {
			int qSize = q.size();
			for(int t=0; t<qSize; t++) {
				minsik = q.poll();
				//System.out.println("now: (" +minsik.now.y + "," + minsik.now.x + ")");
				if(map[minsik.now.y][minsik.now.x] == '1') {
					System.out.println(answer);
					return;
				}
				for(int d=0; d<4; d++) {
					Point next = new Point(minsik.now.y + dy[d], minsik.now.x + dx[d]);
					if(cannotMove(next, minsik.keys)) continue;
					if(isVisited[next.y][next.x][minsik.keys]) {
						//System.out.println("Already visited");
						continue;
					}

					isVisited[next.y][next.x][minsik.keys] = true;
					char nowInfo = map[next.y][next.x];
					int nextKeys = minsik.keys;
					if(nowInfo >= 'a' && nowInfo <= 'f') {//키 정보
						nextKeys = minsik.keys | (1<<(nowInfo - 'a'));
						isVisited[next.y][next.x][nextKeys] = true;
					}
					q.add(new Minsik(next, nextKeys));
				}
			}
			//System.out.println("-----------------");
			answer++;
		}
		System.out.println(-1);
		
	}

	private static boolean cannotMove(Point next, int keys) {
		//System.out.println("check: (" + next.y + "," + next.x + ")");
		if(next.y < 0 || next.x < 0 || next.y >= N || next.x >= M) {
			//System.out.println("out of range");
			return true;
		}
		
		char now = map[next.y][next.x];
		if(now == '#') {
			//System.out.println("wall");
			return true; // 벽
		}
		else if(now >= 'A' && now <= 'F') {//문일 시
			if((keys & (1<<(now - 'A'))) == 0) {//문을 열수 없으면 false
				//System.out.println("cannot open door");
				return true;
			}
		}
		return false;
	}

}
