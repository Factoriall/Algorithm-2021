import java.io.*;

public class Main {
	static int[] p;
	
	static int find(int n) {
		if(p[n] == n) return n;
		if(p[n] < 0) return -1;
		p[n] = find(p[n]);
		return p[n];
	}

	public static void main(String[] args) throws NumberFormatException, IOException {
		int i;
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int G = Integer.parseInt(br.readLine());
		int P = Integer.parseInt(br.readLine());
		p = new int[G];
		for(i=0; i<G; i++) p[i] = i;//같은 수를 저장 - 이는 도킹할 수 있는 제일 높은 게이트 번호를 의미
		
		int answer = 0;
		boolean isFinished = false;//더이상 계산할 필요가 없는지 확인 flag
		for(i=0; i<P; i++) {
			int n = Integer.parseInt(br.readLine()) - 1;
			if(isFinished) continue;
			
			int dockNum = find(n);//find 함수 통해 도킹할 수 있는 최대 게이트 번호 get
			if(dockNum < 0) {//0보다 작으면 불가능, 카운트 끝
				isFinished = true;
				continue;
			}
			//도킹할 게이트가 이미 찼으므로 번호를 1 내림
			//그 내린 게이트가 차있다고 해도 다음 find 함수에서 재조정해줌
			p[dockNum]--;
			answer++;
		}
		
		System.out.println(answer);
	}
}
