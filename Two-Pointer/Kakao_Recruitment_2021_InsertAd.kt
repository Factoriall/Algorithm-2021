import java.text.SimpleDateFormat

fun solution(play_time: String, adv_time: String, logs: Array<String>): String {
    val playSecs = getSecondFromString(play_time)
    val advSeconds = getSecondFromString(adv_time)
    val advNumArr = IntArray(advSeconds)

    for(log in logs){
        val logSplit = log.split("-")
        val s = getSecondFromString(logSplit[0])
        val e = getSecondFromString(logSplit[1])
        for (i in s until e)
            advNumArr[i] += 1
    }

    var advTime : Long = 0
    for(i in 0 until advSeconds) advTime += advNumArr[i]

    var maxTime : Long = advTime
    var answerTime = 0
    for(i in advSeconds until playSecs){
        advTime -= advNumArr[i - advSeconds]
        advTime += advNumArr[i]
        if(maxTime < advTime){
            maxTime = advTime
            answerTime = i - advSeconds + 1
        }
    }

    val hours = answerTime / 3600
    val minutes = (answerTime % 3600) / 60
    val seconds = answerTime % 60

    return String.format("%02d:%02d:%02d", hours, minutes, seconds)
}

fun main(){
    val play_time = "50:00:00"
    val adv_time = "50:00:00"
    val logs = arrayOf("15:36:51-38:21:49", "10:14:18-15:36:51", "38:21:49-42:51:45")
    println(solution(play_time, adv_time, logs))
}

fun getSecondFromString(time: String) : Int{
    val dateFormat = SimpleDateFormat("HH:mm:ss")
    val reference = dateFormat.parse("00:00:00")
    val date = dateFormat.parse(time)
    Long
    return ((date.time - reference.time) / 1000L).toInt()
}