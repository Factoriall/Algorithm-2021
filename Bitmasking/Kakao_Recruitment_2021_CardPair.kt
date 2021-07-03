import java.util.*

val dy = arrayOf(0, 1, 0, -1)
val dx = arrayOf(1, 0, -1, 0)

class Point(var r: Int, var c: Int){//현재 위치 관련 클래스
    fun isOutOfRange(): Boolean{
        return r < 0 || c < 0 || r >= 4 || c >= 4
    }
}

class QInfo(val point: Point, val hold : Int, val tileExist: Int)//큐에 들어갈 정보

fun solution(board: Array<IntArray>, r: Int, c: Int): Int {
    var bitmask = 0

    //bitmask에 값 저장, 비트 1은 아직 있는 것, 0은 이미 제거된 것
    for(i in 0 until 4){
        for(j in 0 until 4){
            if(board[i][j] != 0) bitmask = bitmask or (1 shl getIdxOfBit(i, j))
        }
    }

    //BFS 구현
    val q : Queue<QInfo> = LinkedList()
    val visited = Array(4){ Array(4){BooleanArray(1 shl 16)}}
    q.offer(QInfo(Point(r, c), 0, bitmask))
    visited[r][c][bitmask] = true

    var answer = 0
    while(!q.isEmpty()){
        val qSize = q.size
        repeat(qSize){
            val now = q.poll()
            if(now.tileExist == 0) return answer // 탈출 조건

            val tNum = board[now.point.r][now.point.c]//현재 위치의 타일
            val bitIdx = getIdxOfBit(now.point.r, now.point.c)//bitmasking위한 bit 구하기
            if(tNum != 0 && ((now.tileExist and (1 shl bitIdx)) != 0)){//tile이 있다면 enter 버튼 활성화
                if(now.hold == 0){//hold가 0이면 enter 버튼으로 타일 회수
                    val afterRemove = now.tileExist and (1 shl bitIdx).inv()//status & ~(1<<bitIdx)로 bitIdx 위치의 비트를 0으로 교체
                    checkAndInsert(now.point, tNum, afterRemove, q, visited)
                }
                else{//아니라면 확인
                    if(now.hold == tNum){//hold와 같으면 제거
                        val afterRemove = now.tileExist and (1 shl bitIdx).inv()//status & ~(1<<bitIdx)로 bitIdx 위치의 비트를 0으로 교체
                        checkAndInsert(now.point, 0, afterRemove, q, visited)
                    }
                }
            }

            for(d in 0 until 4){//4방향 이동, ctrl 누를수도 안 누를수도 있음
                //1. 그냥 이동
                val np = Point(now.point.r + dy[d], now.point.c + dx[d])
                if(np.isOutOfRange()) continue
                checkAndInsert(np, now.hold, now.tileExist, q, visited)

                //2. ctrl 이동
                if(board[np.r][np.c] != 0 && (now.tileExist and (1 shl getIdxOfBit(np.r, np.c))) != 0) continue//지금 위치에 타일 있으면 ctrl 눌러도 안 움직임

                val nnp = Point(np.r, np.c)
                while(!Point(nnp.r + dy[d], nnp.c + dx[d]).isOutOfRange()){
                    nnp.r += dy[d]
                    nnp.c += dx[d]
                    if(board[nnp.r][nnp.c] != 0 && (now.tileExist and (1 shl getIdxOfBit(nnp.r, nnp.c))) != 0) break//현재 그 타일을 집은 상태가 아니면서 board가 0이 아니면 끝
                }
                checkAndInsert(nnp, now.hold, now.tileExist, q, visited)
            }
        }
        answer += 1
    }

    return -1
}

fun getIdxOfBit(i: Int, j: Int): Int {//현재 위치에 대응되는 bit 위치 가져오는 함수
    return (i shl 2) + j
}

fun checkAndInsert(
    point: Point,
    tNum: Int,
    tileRemoved: Int,
    q: Queue<QInfo>,
    visited: Array<Array<BooleanArray>>
) {
    if(!visited[point.r][point.c][tileRemoved]){
        visited[point.r][point.c][tileRemoved] = true
        q.offer(QInfo(point, tNum, tileRemoved))
    }
}

fun main(){
    val board = arrayOf(
        intArrayOf(3,0,0,2),
        intArrayOf(0,0,1,0),
        intArrayOf(0,1,0,0),
        intArrayOf(2,0,0,3)
    )
    val r = 0
    val c = 1

    println(solution(board, r, c))
}