import java.util.*;
import java.io.*;
public class Main {
	static int N, M, H;
	final static int MOD = 10007;
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		
		N = Integer.parseInt(st.nextToken());
		M = Integer.parseInt(st.nextToken());
		H = Integer.parseInt(st.nextToken());
	
		int[][] memo = new int[N+1][1001];
		for (int i = 1; i <= N; i++) {
			st = new StringTokenizer(br.readLine(), " ");
			memo[i][0] = 1;
			for (int j = 1; j <= 1000; j++) memo[i][j] = memo[i-1][j];
			while(st.hasMoreTokens()) {
				int num = Integer.parseInt(st.nextToken());
				memo[i][num] += 1;
				for (int j = 1; j <= 1000; j++) {
					if (j - num <= 0) continue;
					memo[i][j] = (memo[i][j] + memo[i - 1][j - num]) % MOD;
				}
			}
		}
		/*
		for (int i = 1; i <= N; i++) {
			for (int j = 0; j <= 15; j++) {
				System.out.print(memo[i][j] + " "); 
			}
			System.out.println();
		}*/
		
		System.out.println(memo[N][H]);
	}

}
