import java.io.*
import java.util.*

fun main() = with(BufferedReader(InputStreamReader(System.`in`))){
    val st = StringTokenizer(readLine(), " ")
    val N = Integer.parseInt(st.nextToken())
    val M = Integer.parseInt(st.nextToken())

    val keywords = mutableSetOf<String>()
    repeat(N){
        keywords.add(readLine())
    }

    val sb = StringBuilder()
    repeat(M){
        val blogMemos = readLine().split(",")
        for(memo in blogMemos){
            keywords.remove(memo)
        }
        sb.append("" + keywords.size + "\n")
    }

    print(sb)
}