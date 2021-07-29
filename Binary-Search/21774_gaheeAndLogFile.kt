import java.io.BufferedReader
import java.io.InputStreamReader
import java.util.*

fun main() = with(BufferedReader(InputStreamReader(System.`in`))){
    val st = StringTokenizer(readLine(), " ")
    val N = Integer.parseInt(st.nextToken())
    val Q = Integer.parseInt(st.nextToken())

    //굳이 LocalDateTime 할 필요 없이 String으로 해도 포맷이 똑같기 때문에 정렬은 다 됨
    val logs = List(7){mutableListOf<String>()}
    repeat(N){
        val lg = readLine().split("#")
        val logTime = lg[0]
        val logLevel = lg[1].toInt()
        logs[logLevel].add(logTime)
    }

    val sb = StringBuilder()
    repeat(Q){
        val query = readLine().split("#")
        val start = query[0]
        val end = query[1]
        val lv = query[2].toInt()

        var count = 0
        for(level in lv..6) {//레벨 범위로 확인
            var logList = logs[level]
            var sIdx = getLowerBound(logList, start)//start 이상이 되지 않는 않은 idx 가져오기
            var eIdx = getUpperBound(logList, end)//end 이하가 되지 않은 idx 가지고 오기
            count += eIdx - sIdx
        }
        sb.append("" + count + "\n")
    }

    println(sb)
}

//중복되는 값이 있을 시 가장 작은 값 return
fun getLowerBound(logList: MutableList<String>, start: String): Int {
    var lo = 0
    var hi = logList.size
    while(lo < hi){
        val mid = (lo + hi) / 2
        if(logList[mid] >= start) hi = mid
        else lo = mid + 1
    }
    return hi
}

//중복되는 값이 있을 시 가장 큰 값 return
fun getUpperBound(logList: MutableList<String>, end: String): Int {
    var lo = 0
    var hi = logList.size
    while(lo < hi){
        val mid = (lo + hi) / 2
        if(logList[mid] <= end) lo = mid + 1
        else hi = mid
    }
    return lo
}
