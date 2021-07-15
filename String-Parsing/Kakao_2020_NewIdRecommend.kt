fun solution(new_id: String): String {
    //step 1
    var recommend = new_id
    recommend = recommend.lowercase()
    println("step1: $recommend")

    //step 2
    val re1 = Regex("[^a-z0-9-_.]")
    recommend = recommend.replace(re1, "")
    println("step2: $recommend")

    //step 3
    val re2 = Regex("[.]{2,}")
    recommend = recommend.replace(re2, ".")
    println("step3: $recommend")

    //step 4
    if(recommend.isNotEmpty() && recommend[0] == '.') recommend = recommend.substring(1)
    if(recommend.isNotEmpty() && recommend[recommend.length-1] == '.') recommend = recommend.substring(0, recommend.length-1)

    println("step4: $recommend")

    //step 5
    if(recommend.isEmpty()) recommend = "a"
    println("step5: $recommend")

    //step 6
    if(recommend.length > 15){
        recommend = recommend.substring(0, 15)
        if(recommend[14] == '.') recommend = recommend.substring(0,14)
    }

    println("step6: $recommend")

    //step 7
    while(recommend.length < 3){
        recommend += recommend[recommend.length - 1]
    }

    println("step7: $recommend")

    return recommend
}


fun main(){
    val id = "...!@BaT#*..y.abcdefghijklm"
    println(solution(id))
}