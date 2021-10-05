import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Stack;

public class Main {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String str = br.readLine();
		
		Stack<Character> st = new Stack<>();
		for(int i=0; i<str.length(); i++) {
			if(str.charAt(i) == 'A') {
				if(st.size() < 2 || i == str.length() - 1 || str.charAt(i+1) == 'A') {
					System.out.println("NP");
					return;
				}
				st.pop();
				st.pop();
				i += 1;
			}
			st.push('P');
		}
		if(st.size() == 1) System.out.println("PPAP");
		else System.out.println("NP");
	}
}