fun solution(key: Array<IntArray>, lock: Array<IntArray>): Boolean {
    //미리 변수로 지정해줘서 헷갈리는 부분 최대한 방지
    val kSize = key.size
    val lSize = lock.size
    val fullSize = 2*kSize + lSize - 2
    val lStartIdx = kSize-1
    val lEndIdx = kSize + lSize - 2

    //fullLock으로 옆으로 삐져나가는 경우까지 고려
    val fullLock = Array(fullSize){IntArray(fullSize)}
    var remain = 0
    for(i in lStartIdx..lEndIdx){
        for(j in lStartIdx..lEndIdx){
            fullLock[i][j] = lock[i-lStartIdx][j-lStartIdx]
            if(fullLock[i][j] == 0) remain++
        }
    }

    var newKey = key
    repeat(4){
        newKey = rotate(newKey)//4번 회전

        for(si in 0..lEndIdx){
            for(sj in 0..lEndIdx){//si, sj는 fullLock에서 시작점 위치

                var isNotFit = false
                var cnt = 0
                for(i in si until si + kSize){
                    for(j in sj until sj + kSize){//i, j는 실제 조사 위치

                        if(!isInLockRange(i, j, lStartIdx, lEndIdx)) continue

                        //key의 진짜 크기는 fullLock보다 작기 때문에 조정
                        val ki = i - si
                        val kj = j - sj
                        if(fullLock[i][j] == newKey[ki][kj]) {//둘이 맞지 않으면 아예 끝
                            isNotFit = true
                            break
                        }
                        else if(fullLock[i][j] == 0 && newKey[ki][kj] == 1) cnt++//홈에 끼워지면 count 늘림
                    }
                    if(isNotFit) break
                }
                if(isNotFit) continue//isNotFit이면 아래 볼 필요도 없음
                if(remain == cnt) return true//정답
            }
        }
    }

    return false//모두 확인해도 안되는 것 확인
}

fun isInLockRange(i: Int, j: Int, lStartIdx: Int, lEndIdx: Int): Boolean {//fullLock의 진짜 범위 안에 들어가는지 체크
    return i >= lStartIdx && j >= lStartIdx && i <= lEndIdx && j <= lEndIdx
}

fun rotate(arr: Array<IntArray>): Array<IntArray>{//90도 회전 구현
    val n = arr.size
    val rotatedArr = Array(n){IntArray(n)}
    for(i in 0 until n){
        for(j in 0 until n){
            rotatedArr[i][j] = arr[j][n-1-i]
        }
    }

    return rotatedArr
}

fun main(){
    val key = arrayOf(
        intArrayOf(0, 0, 0),
        intArrayOf(1, 0, 0),
        intArrayOf(0, 1, 1))
    val lock = arrayOf(
        intArrayOf(1, 1, 1),
        intArrayOf(1, 1, 0),
        intArrayOf(1, 0, 1))
    println(solution(key, lock))
}
