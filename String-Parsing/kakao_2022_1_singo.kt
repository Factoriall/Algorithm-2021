import java.util.*

class Solution {
    fun solution(id_list: Array<String>, report: Array<String>, k: Int): IntArray {
        var answer = IntArray(id_list.size)
        var sNum : MutableMap<String, Int> = mutableMapOf()
        var singo : MutableMap<String, MutableSet<String>> = mutableMapOf()
        var idxs :MutableMap<String, Int> = mutableMapOf()

        var idx = 0
        for(id in id_list){
            idxs[id] = idx++
            singo[id] = mutableSetOf()
            sNum[id] = 0
        }


        for(rep in report){
            val rSplit = rep.split(" ")
            val from = rSplit[0]
            val to = rSplit[1]

            if(!singo[from]!!.contains(to))
                sNum[to] = sNum[to]!!.plus(1)
            //println("sNum:" + sNum[to]!!)

            singo[from]!!.add(to)
        }

        for((key, value) in sNum){
            if(value >= k){
                for((key2, _) in singo)
                if(singo[key2]!!.contains(key)){
                    answer[idxs[key2]!!] += 1
                }
            }
        }


        return answer
    }
}

fun main(){
    val sol = Solution()

    val id_list = arrayOf("muzi", "frodo", "apeach", "neo")
    val report = arrayOf("muzi frodo","apeach frodo","frodo neo","muzi neo","apeach muzi")
    val k = 2
    val answer = sol.solution(id_list, report, k)

    for(ans in answer) println(ans)
}