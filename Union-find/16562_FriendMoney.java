import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.StringTokenizer;

public class Main {
	static int[] parent;
	
	static int find(int n) {
		if(parent[n] < 0) return n;
		parent[n] = find(parent[n]);
		return parent[n];
	}
	
	static void merge(int a, int b) {
		a = find(a);
		b = find(b);
		if(a == b) return;
		parent[b] = a;
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		
		int N = Integer.parseInt(st.nextToken());//���� x
		int M = Integer.parseInt(st.nextToken());//���� x
		StringBuilder sb = new StringBuilder();
		
		parent = new int[N+1];//n+1�� �ִ°���, ���� x
		Arrays.fill(parent, -1);//��Ʈ�� -1�� ����
		
		for(int i=0; i<M; i++) {
			st = new StringTokenizer(br.readLine(), " ");
			
			boolean check = (Integer.parseInt(st.nextToken()) == 1);
			int a = Integer.parseInt(st.nextToken());
			int b = Integer.parseInt(st.nextToken());
			
			if(check) {
				if(find(a) == find(b)) sb.append("YES\n");
				else sb.append("NO\n");
			}
			else merge(a, b);
			
			//printParent();
		}
		
		System.out.print(sb.toString());
	}

	private static void printParent() {
		for(int i=0; i< parent.length; i++) {
			System.out.print(parent[i] + " ");
		}
		System.out.println();
	}
}
