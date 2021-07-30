import java.io.BufferedReader
import java.io.BufferedWriter
import java.io.InputStreamReader
import java.io.OutputStreamWriter
import java.util.*

class Command(val isAdd: Boolean, val alp: Char?, val idx: Int?)

lateinit var pCardIdxInfo: IntArray
var N: Int = 0
var C: Int = 0
lateinit var playerInfo: MutableList<MutableList<Int>>//플레이어 카드 정보
lateinit var cmdInfo: MutableList<MutableList<Command>>//커맨드 정보
lateinit var set: SortedSet<String>//정렬된 set

fun main() = with(BufferedReader(InputStreamReader(System.`in`))) {
    var st = StringTokenizer(readLine(), " ")
    N = Integer.parseInt(st.nextToken())
    C = Integer.parseInt(st.nextToken())
    set = sortedSetOf()

    playerInfo = mutableListOf()
    //player의 정보 저장
    repeat(N) {
        st = StringTokenizer(readLine(), " ")
        val num = Integer.parseInt(st.nextToken())
        val numList = mutableListOf<Int>()
        repeat(num) {
            numList.add(Integer.parseInt(st.nextToken()) - 1)
        }
        playerInfo.add(numList)
    }

    pCardIdxInfo = IntArray(N) { 0 }
    cmdInfo = mutableListOf()
    //커맨드 정보 저장
    repeat(C) {
        val commands = readLine().split(",")
        val cmdList = mutableListOf<Command>()

        for (command in commands) {//startsWith 통해 맨 앞의 커맨드 추출 가능
            if (command.startsWith("ADD")) cmdList.add(Command(true, command[4], null))
            else cmdList.add(Command(false, null, command.substring(4).toInt()))
        }
        cmdInfo.add(cmdList)
    }
    getOrder("", 0)//str를 dfs로 돌려서 결과 추출

    //시간 문제가 있을 시 bufferedWriter를 적극적으로 사용해보자!
    val bw = BufferedWriter(OutputStreamWriter(System.out))
    val sb = StringBuilder()
    for (answer in set)
        sb.append(answer + "\n")
    bw.write(sb.toString())
    bw.close()
}

//dfs 따라 순서 정해서 문자열 구하기
fun getOrder(str: String, cmdCnt : Int) {
    if (cmdCnt == C) { // 탈출 조건, command 수를 모두 사용할 시
        if (str != "") set.add(str)//정상 값 저장
        else set.add("EMPTY")//비어있음 empty 저장
        return
    }
    //player의 카드는 "순서대로" 진행할 필요가 있음
    //이에 따라 pCardIdxInfo라는 실행해야하는 인덱스를 저장하는 배열 생성 후
    //이 배열의 한 부분이 사용되면 인덱스를 계속 더한다
    var pIdx = 0
    for (playerCard in playerInfo) {
        if (playerCard.size == pCardIdxInfo[pIdx]) {//만약 이 플레이어의 모든 카드를 소모했다면 끝
            pIdx++
            continue
        }

        //현재 플레이어의 사용해야 할 카드 번호를 추출해서 실제로 실행
        val cNum = playerCard[pCardIdxInfo[pIdx]]
        val ret = calculateString(str, cNum)
        if(ret == "ERROR"){
            pIdx++
            continue
        }

        //백트래킹 작업
        pCardIdxInfo[pIdx]++
        getOrder(ret, cmdCnt + 1)
        pCardIdxInfo[pIdx]--
        pIdx++
    }
}

//실제 string을 커맨드에 따라 조정해서 결과값 return하는 함수
fun calculateString(str : String, num : Int) : String {
    var ret = str
    val cmd = cmdInfo[num]
    for (cd in cmd) {
        if (cd.isAdd) ret += cd.alp
        else {
            val idx = cd.idx!!
            if (ret.length > idx)
                ret = ret.substring(0, idx) + ret.substring(idx + 1)
            else {
                set.add("ERROR")
                return "ERROR"
            }
        }
    }
    return ret
}

