import java.io.*
import java.util.*

fun main() = with(BufferedReader(InputStreamReader(System.`in`))){
    val st = StringTokenizer(readLine(), " ")
    val n = Integer.parseInt(st.nextToken())
    val k = Integer.parseInt(st.nextToken())
    var memo = IntArray(k+1)
    memo[0] = 1

    val coins = IntArray(n)
    for(i in 0 until n)
        coins[i] = Integer.parseInt(readLine())

    //Sliding Window 기법 활용
    for(i in 0 until n){
        var newMemo = IntArray(k + 1)
        newMemo[0] = 1
        for(j in 1..k){
            val colAdd = if(i == 0) 0 else memo[j]
            val rowAdd = if(j - coins[i] < 0) 0 else newMemo[j - coins[i]]
            newMemo[j] = colAdd + rowAdd
        }
        memo = newMemo
    }

    println(memo[k])
}
