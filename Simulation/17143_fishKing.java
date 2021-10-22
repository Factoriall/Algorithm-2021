import java.io.*;
import java.util.*;

public class Main {
	static int R, C, M;
	static final int[] dy = {-1, 1, 0, 0};
	static final int[] dx = {0, 0, 1, -1};
	static int answer = 0;
	static int[][] map;
	
	static class Shark implements Comparable<Shark>{
		int r, c, s, d, z;
		boolean canMove = true;
		Shark(int r, int c, int s, int d, int z){
			this.r = r;
			this.c = c;
			this.s = s;
			this.d = d;
			this.z = z;
		}
		
		public void isEaten() {
			canMove = false;
		}
		
		@Override
		public int compareTo(Shark o) {
			return z - o.z;
		}
		//0: 위, 1: 아래, 2: 오른쪽, 3:왼쪽
		public void changeDirIfNeeded() {
			if(d == 0 && r == 0) d = 1;
			else if(d == 1 && r == R-1) d = 0;
			else if(d == 2 && c == C-1) d = 3;
			else if(d == 3 && c == 0) d = 2;
		}
	}
	
	static List<Shark> sharks = new ArrayList<>();
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		
		R = Integer.parseInt(st.nextToken());
		C = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		map = new int[R][C];
		
		
		for(int i=0; i<M; i++) {
			int r, c, s, d, z;
			st = new StringTokenizer(br.readLine(), " ");
			r = Integer.parseInt(st.nextToken()) - 1;
			c = Integer.parseInt(st.nextToken()) - 1;
			s = Integer.parseInt(st.nextToken());
			d = Integer.parseInt(st.nextToken()) - 1;
			z = Integer.parseInt(st.nextToken());
			
			sharks.add(new Shark(r,c,s,d,z));
		}
		Collections.sort(sharks);
		
		int idx = 1;
		for(Shark s: sharks) {
			map[s.r][s.c] = idx++;
		}
		
		//printMap();
		
		for(int j=0; j<C; j++) {
			fishing(j);
			//printMap();
			sharkMove();
			//printMap();
			//System.out.println("==============");
		}
		
		System.out.println(answer);
	}
	
	static void printMap() {
		int[][] print = new int[R][C];
		for(Shark s : sharks) print[s.r][s.c] = s.z;
		for(int i=0; i<R; i++) {
			for(int j=0; j<C; j++) {
				System.out.print(print[i][j] + " ");
			}
			System.out.println();
		}
		System.out.println();
	}

	private static void fishing(int j) {
		for(int i=0; i<R; i++) {
			if(map[i][j] != 0) {
				int idx = map[i][j] - 1;
				answer += sharks.get(idx).z;
				sharks.remove(idx);
				map[i][j] = 0;
				break;
			}
		}
	}

	private static void sharkMove() {
		int[][] newMap = new int[R][C];
		int idx = 1;
		for(Shark shark: sharks) {
			if(!shark.canMove) continue;
			
			int cnt = 0;
			while(cnt < shark.s) {
				shark.changeDirIfNeeded();
				shark.r += dy[shark.d];
				shark.c += dx[shark.d];
				cnt++;
			}
			//System.out.println("r,c: " + shark.r + "," + shark.c);
			
			if(newMap[shark.r][shark.c] != 0) 
				sharks.get(newMap[shark.r][shark.c] - 1).isEaten();	
			newMap[shark.r][shark.c] = idx++;
		}
		
		for(int i=sharks.size() - 1; i>=0; i--) {
			if(!sharks.get(i).canMove) sharks.remove(i);
		}
		//System.out.println("sharksize: " + sharks.size());
		for(int i=0; i<sharks.size(); i++) {
			newMap[sharks.get(i).r][sharks.get(i).c] = i+1;
		}
		
		for(int i=0; i<R; i++) {
			for(int j=0; j<C; j++) {
				map[i][j] = newMap[i][j];
			}
		}
		
	}

}
