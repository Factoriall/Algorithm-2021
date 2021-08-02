import java.io.*
import java.util.*

class FileInfo(val fileName : String, val extension : String)

private lateinit var osIdentified : MutableSet<String>

private val comparator = Comparator<FileInfo> { a, b ->
    when{
        (a.fileName != b.fileName) -> a.fileName.compareTo(b.fileName)
        (osIdentified.contains(a.extension) && !osIdentified.contains(b.extension)) -> -1
        (!osIdentified.contains(a.extension) && osIdentified.contains(b.extension)) -> 1
        else -> a.extension.compareTo(b.extension)
    }
}

private lateinit var fileNames : SortedSet<FileInfo>

fun main() = with(BufferedReader(InputStreamReader(System.`in`))){
    val st = StringTokenizer(readLine(), " ")
    val N = Integer.parseInt(st.nextToken())
    val M = Integer.parseInt(st.nextToken())
    osIdentified = mutableSetOf()
    fileNames = sortedSetOf(comparator)

    val fileNameList = mutableListOf<String>()
    repeat(N){
        fileNameList.add(readLine())
    }

    repeat(M){
        osIdentified.add(readLine())
    }

    for(file in fileNameList){
        val fileSplit = file.split(".")
        val fileInfo = FileInfo(fileSplit[0], fileSplit[1])
        fileNames.add(fileInfo)
    }

    for(result in fileNames){
        println(result.fileName + "." + result.extension)
    }
}