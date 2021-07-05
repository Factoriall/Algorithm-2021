import java.util.*
import java.io.*


fun main() = with (BufferedReader(InputStreamReader(System.`in`))){
    val n = Integer.parseInt(readLine())

    var cnt = 0

    val funcN = mutableListOf<Int>()//f(n)
    funcN.add(0)//index 0 추가해서 헷갈림 방지

    var sum = 0
    var num = 1
    while(cnt < n){
        when (num) {//점화식 구현
            1 -> {//1이면 1 추가
                sum += 1
                funcN.add(1)
                cnt += 1
            }
            2 -> {//2이면 2 추가
                sum += 4
                funcN.add(2)
                funcN.add(2)
                cnt += 2
            }
            else -> {//나머지는 점화식 따라 발전
                cnt += funcN[num]
                if(sum > n) {
                    num += 1
                    continue
                }
                repeat(funcN[num]) {
                    sum += num
                    funcN.add(num)
                }
            }
        }

        num += 1
    }
    println(num - 1)//넘을 때가 num보다 1 큰 경우
}