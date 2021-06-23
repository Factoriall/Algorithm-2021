import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;

public class Main {
	//���� �������� ��
	static int N;
	static int K;

	//��Ʈ����ŷ�� Ȱ���ؼ� ���� Ǯ��
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
	
		//���������� ������ ���� ���� ��Ʈ�� �̿��� ������ ���� target���� ����
		int target = 0;
		for(int i=0; i<N; i++) {
			target <<= 3;
			target += i;
		}
		
		HashSet<Integer> set = new HashSet<>();//isVisited
		Queue<Integer> q = new LinkedList<>();
		
		set.add(num);
		q.add(num);
		
		//bfs ���
		int count = 0;
		while(!q.isEmpty()) {
			int qSize = q.size();
			for(int t=0; t<qSize; t++) {
				int now = q.poll();
				if(now == target) {//���̸� ��
					System.out.println(count);
					return;
				}
				
				for(int i=0; i<=N-K; i++) {
					int newNum = reverse(now, i);//Ư�� ������ �������ϴ� �Լ�
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
		int delIdx = (start << 1) + K - 1;//�ٲ�� �� 2���� ���� �׻�  delIdx�� ����
		for(int i=start; i<start + K/2; i++) {
			final int CMP = 7;//������ 111�� 7
			
			//�ٲ� �κ��� ��ġ ����
			int idx1 = (N - 1 - i) * 3;
			int idx2 = (N - 1 - (delIdx - i)) * 3;
			
			//�ٲ�� �κ��� ������ �κ� ����
			int swp1 = CMP & (now >> idx1);
			int swp2 = CMP & (now >> idx2);
			
			//�ٲ�� �κ��� ��ġ�� ��Ʈ�� ��� 0���� ġȯ
			now = now & ~(CMP<<idx1);
			now = now & ~(CMP<<idx2);
			
			//0���� �� �κ��� �������ؼ� ä���ֱ�
			now += swp1 << idx2;
			now += swp2 << idx1;			
		}
		
		return now;
	}



}
