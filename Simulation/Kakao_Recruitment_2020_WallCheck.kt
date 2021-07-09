const val INF = 987654321

var answer : Int = INF
val set : HashSet<Int> = HashSet()

fun solution(n: Int, weak: IntArray, dist: IntArray): Int {
    for(d in dist) if(d >= n) return 1 //dist 중 하나라도 n보다 크거나 같은 게 있다면 한 명이 끝내기 가능
    getPermutations(n, weak, dist, mutableListOf())

    return if(answer == INF) -1 else answer
}

fun getPermutations(n: Int, weak: IntArray, dist: IntArray, permutation: MutableList<Int>) {//이 부분에 대해서 테스트 방법을 만들어야 됨
    if(set.size == dist.size){
        getCheckNum(n, weak, permutation as List<Int>)
    }

    for(idx in dist.indices){
        if(set.contains(idx)) continue

        permutation.add(dist[idx])
        set.add(idx)

        getPermutations(n, weak, dist, permutation)

        permutation.removeAt(permutation.size - 1)
        set.remove(idx)
    }
}

fun getCheckNum(n: Int, weak: IntArray, permutation: List<Int>) {
    for(i in weak.indices){
        var cpNum = 0
        var cwNum = 0
        var now = weak[i]//현재 위치
        var nIdx = i

        for(d in permutation){
            cpNum += 1
            var maxDist = now + d

            do{
                nIdx = getNextIdx(nIdx, weak.size)
                if(nIdx == 0) maxDist -= n
                cwNum += 1
            }while(maxDist >= weak[nIdx])

            if(cwNum >= weak.size) break // 종료 조건
            now = weak[nIdx]
        }

        if(cwNum < weak.size) continue

        answer = answer.coerceAtMost(cpNum)
    }
}

fun getNextIdx(idx: Int, size: Int): Int {
    return if(idx < size - 1) (idx + 1) else 0
}