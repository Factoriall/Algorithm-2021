import java.util.EnumSet.range

class Solution {

    val db = ArrayList<ArrayList<ArrayList<ArrayList<ArrayList<Int>>>>>()

    fun solution(info: Array<String>, query: Array<String>): IntArray {
        var answer: ArrayList<Int> = arrayListOf()

        repeat(3){
            val list1 = ArrayList<ArrayList<ArrayList<ArrayList<Int>>>>()
            repeat(2){
                val list2 = ArrayList<ArrayList<ArrayList<Int>>>()
                repeat(2){
                    val list3= ArrayList<ArrayList<Int>>()
                    repeat(2){
                        val list4 = ArrayList<Int>()
                        list3.add(list4)
                    }
                    list2.add(list3)
                }
                list1.add(list2)
            }
            db.add(list1)
        }

        for(inf in info){
            val splitInfo = inf.split(" ")
            val pIdx = if(splitInfo[0] == "cpp") 0
            else if(splitInfo[0] == "java") 1
            else 2

            val oIdx = if(splitInfo[1] == "backend") 0
            else 1

            val cIdx = if(splitInfo[2] == "junior") 0
            else 1

            val fIdx = if(splitInfo[3] == "chicken") 0
            else 1


            db[pIdx][oIdx][cIdx][fIdx].add(splitInfo[4].toInt())
        }

        //정렬
        for(i in 0..2){
            for(j in 0..1){
                for(k in 0..1){
                    for(l in 0..1){
                        db[i][j][k][l].sort()
                    }
                }
            }
        }

        for(q in query){
            val splitQuery = q.split(" ")
            val pIdxs = mutableListOf<Int>()
            val oIdxs = mutableListOf<Int>()
            val cIdxs = mutableListOf<Int>()
            val fIdxs = mutableListOf<Int>()

            when(splitQuery[0]){
                "cpp" -> pIdxs.add(0)
                "java" -> pIdxs.add(1)
                "python" -> pIdxs.add(2)
                "-" -> {
                    pIdxs.add(0)
                    pIdxs.add(1)
                    pIdxs.add(2)
                }
            }
            when(splitQuery[2]){
                "backend" -> oIdxs.add(0)
                "frontend" -> oIdxs.add(1)
                "-" -> {
                    oIdxs.add(0)
                    oIdxs.add(1)
                }
            }
            when(splitQuery[4]){
                "junior" -> cIdxs.add(0)
                "senior" -> cIdxs.add(1)
                "-" -> {
                    cIdxs.add(0)
                    cIdxs.add(1)
                }
            }
            when(splitQuery[6]){
                "chicken" -> fIdxs.add(0)
                "pizza" -> fIdxs.add(1)
                "-" -> {
                    fIdxs.add(0)
                    fIdxs.add(1)
                }
            }

            var ans = 0
            for(p in pIdxs){
                for(o in oIdxs){
                    for(c in cIdxs){
                        for(f in fIdxs){
                            //println("$p,$o,$c,$f")
                            val subDb = db[p][o][c][f]
                            ans += binSearch(subDb, splitQuery[7].toInt())
                        }
                    }
                }
            }
            answer.add(ans)
        }

        return answer.toIntArray()
    }

    private fun binSearch(subDb: ArrayList<Int>, margin: Int): Int {
        var lo = -1
        var hi = subDb.size
        while(lo + 1 < hi){
            val mid = (lo + hi) / 2
            if(subDb[mid] >= margin) hi = mid
            else lo = mid
        }

        return subDb.size - hi
    }
}

fun main(){
    val info : Array<String> = arrayOf("java backend junior pizza 150",
        "python frontend senior chicken 210",
        "python frontend senior chicken 150",
        "cpp backend senior pizza 260",
        "java backend junior chicken 80",
        "python backend senior chicken 50")
    val query : Array<String> = arrayOf("java and backend and junior and pizza 100","python and frontend and senior and chicken 200","cpp and - and senior and pizza 250","- and backend and senior and - 150","- and - and - and chicken 100","- and - and - and - 150")
    var answer = Solution().solution(info, query)

    for(ans in answer) println(ans)
}