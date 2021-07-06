import java.io.*
import java.util.*

fun main() = with(BufferedReader(InputStreamReader(System.`in`))){
    val n = Integer.parseInt(readLine())
    var st : StringTokenizer
    //Sliding Window를 활용해서 최소한의 공간을 활용
    var maxDp = IntArray(3)
    var minDp = IntArray(3)

    for(i in 0 until n){
        st = StringTokenizer(readLine(), " ")
        val row = IntArray(3)
        for(j in 0 until 3) row[j] = Integer.parseInt(st.nextToken())

        //값을 갱신해주기 위한 배열 생성
        val newMax = IntArray(3)
        val newMin = IntArray(3)
        //점화식 따라 newMax 및 minMax 생성
        newMax[0] = maxDp[0].coerceAtLeast(maxDp[1]) + row[0]
        newMax[1] = maxDp[0].coerceAtLeast(maxDp[1]).coerceAtLeast(maxDp[2]) + row[1]
        newMax[2] = maxDp[1].coerceAtLeast(maxDp[2]) + row[2]

        newMin[0] = minDp[0].coerceAtMost(minDp[1]) + row[0]
        newMin[1] = minDp[0].coerceAtMost(minDp[1]).coerceAtMost(minDp[2]) + row[1]
        newMin[2] = minDp[1].coerceAtMost(minDp[2]) + row[2]

        //Sliding Window 기법 따라 배열 교체
        maxDp = newMax
        minDp = newMin
    }

    val max = maxDp[0].coerceAtLeast(maxDp[1]).coerceAtLeast(maxDp[2])
    val min = minDp[0].coerceAtMost(minDp[1]).coerceAtMost(minDp[2])
    println("$max $min")
}