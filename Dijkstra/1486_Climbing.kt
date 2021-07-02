import java.io.*
import java.util.*
import kotlin.math.*

//방향 배열
private val dy = arrayOf(1, 0, -1, 0)
private val dx = arrayOf(0, 1, 0, -1)

private const val INF = 987654321
private lateinit var mountain : Array<CharArray>

//특정 위치 클래스
class MtPoint(val y: Int, val x: Int){
    fun isOutOfRange(n: Int, m: Int) : Boolean {
        return y < 0 || x < 0 || y >= n || x >= m
    }
}

//다익스트라를 위한 정보 클래스
class PQInfo(val mtPoint: MtPoint, val total : Int) : Comparable<PQInfo> {
    override fun compareTo(other: PQInfo): Int {
        return total - other.total
    }
}

fun main() = with(BufferedReader(InputStreamReader(System.`in`))){
    var st = StringTokenizer(readLine(), " ")
    val n = Integer.parseInt(st.nextToken())
    val m = Integer.parseInt(st.nextToken())
    val t = Integer.parseInt(st.nextToken())
    val d = Integer.parseInt(st.nextToken())

    mountain = Array(n){ CharArray(m) }

    for(i in 0 until n){
        val line = readLine()
        for(j in 0 until m){
            mountain[i][j] = line[j]
        }
    }

    val distUp = getDistList(n, m, t, true)//올라갈 때의 정보 저장
    val distDown = getDistList(n, m, t, false)//내려갈 때의 정보 저장

    var answer = 0
    for(i in 0 until n){
        for(j in 0 until m) {
            if(distUp[i][j] == INF || distDown[i][j] == INF) continue
            val total = distUp[i][j] + distDown[i][j]
            if(total <= d) answer = max(answer, getHeight(mountain[i][j]))
        }
    }

    println(answer)
}

fun getDistList(n: Int, m: Int, t: Int, isGoingUp: Boolean): Array<IntArray> {
    val dist = Array(n){ IntArray(m){ INF } }
    val visited = Array(n){ BooleanArray(m) }

    val pq = PriorityQueue<PQInfo>()
    dist[0][0] = 0
    pq.offer(PQInfo(MtPoint(0,0), 0))

    //다익스트라 알고리즘 구현현
   while(!pq.isEmpty()){
        var cur : MtPoint
        do{
            cur = pq.poll().mtPoint
        }while (!pq.isEmpty() && visited[cur.y][cur.x])

        if(visited[cur.y][cur.x]) break
        visited[cur.y][cur.x] = true

        for(dir in 0 until 4) {
            val next = MtPoint(cur.y + dy[dir], cur.x + dx[dir])
            if(next.isOutOfRange(n,m)) continue

            val nextHeight = getHeight(mountain[next.y][next.x])
            val nowHeight = getHeight(mountain[cur.y][cur.x])
            if(abs(nextHeight - nowHeight) > t) continue
            val time =
                if(isGoingUp) {//올라갈 시 next 높이와 now 높이를 재서 제곱만큼의 시간 소요
                    if (nextHeight > nowHeight) (nextHeight - nowHeight) * (nextHeight - nowHeight)
                    else 1
                }
                else{//내려갈 시 반대로 now가 next이고 next가 now이므로 부호 방향을 반대로 조정
                    if (nextHeight < nowHeight) (nextHeight - nowHeight) * (nextHeight - nowHeight)
                    else 1
                }

            if(dist[next.y][next.x] > dist[cur.y][cur.x] + time){
                dist[next.y][next.x] = dist[cur.y][cur.x] + time
                pq.offer(PQInfo(next, dist[cur.y][cur.x] + time))
            }
        }
    }
    return dist
}

fun getHeight(alp : Char) : Int{
    return if(alp in 'A'..'Z') (alp - 'A')
    else (alp - 'a' + 26)
}