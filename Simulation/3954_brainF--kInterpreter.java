import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.util.*;

public class Main {

	private static final int MAX_CNT = 50000000;
	private static final int MOD = 256;
	
	static Map<Integer, Integer> bracketTo = new HashMap<>();

	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int T = Integer.parseInt(br.readLine());
		for(int t=0; t<T; t++) {
			StringTokenizer st = new StringTokenizer(br.readLine(), " ");
			int sm = Integer.parseInt(st.nextToken());
			int sc = Integer.parseInt(st.nextToken());
			int si = Integer.parseInt(st.nextToken());
			
			char[] cmd = br.readLine().toCharArray();
			char[] input = br.readLine().toCharArray();
			int[] bit8Array = new int[sm];
			
			Stack<Integer> brackets = new Stack<>();
			for(int i=0; i<sc; i++) {
				if(cmd[i] == '[') {
					brackets.push(i);
				}
				else if(cmd[i] == ']') {
					bracketTo.put(brackets.peek(), i);
					bracketTo.put(i, brackets.peek());
					brackets.pop();
				}
			}
			
			
			int pointer = 0;//메모리
			int iIdx = 0;//입력 읽는 idx
			int cIdx = 0;//현 cmd 위치
			
			int cnt = 0;
			while(cIdx < cmd.length && cnt < MAX_CNT) {
				switch(cmd[cIdx]) {
				case '+':
					bit8Array[pointer] = (bit8Array[pointer] + 1) % MOD;
					break;
				case '-':
					bit8Array[pointer] 
							= bit8Array[pointer] == 0 ? MOD -1 : bit8Array[pointer] - 1;
					break;
				case '>':
					pointer = (pointer + 1) % sm;
					break;
				case '<':
					pointer = pointer == 0 ? sm - 1 : pointer - 1;
					break;
				case '[':
					if(bit8Array[pointer] == 0) cIdx = bracketTo.get(cIdx);
					break;
				case ']':
					if(bit8Array[pointer] != 0) cIdx = bracketTo.get(cIdx);
					break;
				case ',':
					if(iIdx == si) bit8Array[pointer] = 255;
					else bit8Array[pointer] = input[iIdx++];
				}
				cIdx++;
				cnt++;
			}
			
			if(cnt == MAX_CNT) {
				cnt = 0;
				int maxIdx = cIdx;
				int minIdx = cIdx;
				while(cnt < MAX_CNT) {
					switch(cmd[cIdx]) {
					case '+':
						bit8Array[pointer] = (bit8Array[pointer] + 1) % MOD;
						break;
					case '-':
						bit8Array[pointer] 
								= bit8Array[pointer] == 0 ? MOD -1 : bit8Array[pointer] - 1;
						break;
					case '>':
						pointer = (pointer + 1) % sm;
						break;
					case '<':
						pointer = pointer == 0 ? sm - 1 : pointer - 1;
						break;
					case '[':
						if(bit8Array[pointer] == 0) cIdx = bracketTo.get(cIdx);
						break;
					case ']':
						if(bit8Array[pointer] != 0) cIdx = bracketTo.get(cIdx);
						break;
					case ',':
						if(iIdx == si) bit8Array[pointer] = 255;
						else bit8Array[pointer] = input[iIdx++];
					}
					maxIdx = Math.max(maxIdx, cIdx + 1);
					minIdx = Math.min(minIdx, cIdx);
					cIdx++;
					cnt++;
				}
				System.out.println("Loops " + minIdx + " " + maxIdx);
			}
			else System.out.println("Terminates");
		}
	}
}