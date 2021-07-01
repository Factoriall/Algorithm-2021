import java.util.*
import java.io.*
import kotlin.properties.Delegates

const val INF = 987654321
private lateinit var adjList : MutableList<MutableList<Edge>>
private var n by Delegates.notNull<Int>()

class Edge(val to : Int, val weight: Int)
class PQInfo(val cNum : Int, val sum: Int) : Comparable<PQInfo>{
    override fun compareTo(other: PQInfo): Int {
        return sum - other.sum
    }
}

fun main() = with (BufferedReader(InputStreamReader(System.`in`))){
    var st = StringTokenizer(readLine(), " ")
    n = Integer.parseInt(st.nextToken())
    val s = Integer.parseInt(st.nextToken()) - 1
    val a = Integer.parseInt(st.nextToken()) - 1
    val b = Integer.parseInt(st.nextToken()) - 1

    val pn = Integer.parseInt(st.nextToken())

    adjList = ArrayList()
    for(i in 0 until n) adjList.add(mutableListOf())
    for(i in 0 until pn) {
        st = StringTokenizer(readLine(), " ")
        val c1 = Integer.parseInt(st.nextToken()) - 1
        val c2 = Integer.parseInt(st.nextToken()) - 1
        val w = Integer.parseInt(st.nextToken())

        adjList[c1].add(Edge(c2, w))
        adjList[c2].add(Edge(c1, w))
    }

    //solution
    var answer = INF
    for(via in 1..n){
        val minDistance = getMinDistance(n, via, s, a, b)
        answer = answer.coerceAtMost(minDistance)
    }

    println(answer)
}

fun getMinDistance(n: Int, s: Int, e1: Int, e2: Int, e3: Int) : Int{
    val dist = IntArray(n + 1) { INF }
    val visited = BooleanArray(n + 1) { false }
    val pq : PriorityQueue<PQInfo> = PriorityQueue()

    dist[s] = 0
    pq.add(PQInfo(s, 0))
    while(!pq.isEmpty()){
        var cur : Int
        do{
            cur = pq.poll().cNum
        }while(!pq.isEmpty() && visited[cur])
        if(visited[cur]) break
        if(visited[e1] && visited[e2] && visited[e3]) break

        visited[cur] = true
        for(edge in adjList[cur]){
            val next = edge.to
            if(dist[next] > dist[cur] + edge.weight){
                dist[next] = dist[cur] + edge.weight
                pq.offer(PQInfo(next, dist[next]))
            }
        }
    }
    if(dist[e1] == INF || dist[e2] == INF || dist[e3] == INF) return INF

    return dist[e1] + dist[e2] + dist[e3]
}