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
		for(i=0; i<G; i++) p[i] = i;//���� ���� ���� - �̴� ��ŷ�� �� �ִ� ���� ���� ����Ʈ ��ȣ�� �ǹ�
		
		int answer = 0;
		boolean isFinished = false;//���̻� ����� �ʿ䰡 ������ Ȯ�� flag
		for(i=0; i<P; i++) {
			int n = Integer.parseInt(br.readLine()) - 1;
			if(isFinished) continue;
			
			int dockNum = find(n);//find �Լ� ���� ��ŷ�� �� �ִ� �ִ� ����Ʈ ��ȣ get
			if(dockNum < 0) {//0���� ������ �Ұ���, ī��Ʈ ��
				isFinished = true;
				continue;
			}
			//��ŷ�� ����Ʈ�� �̹� á���Ƿ� ��ȣ�� 1 ����
			//�� ���� ����Ʈ�� ���ִٰ� �ص� ���� find �Լ����� ����������
			p[dockNum]--;
			answer++;
		}
		
		System.out.println(answer);
	}
}
