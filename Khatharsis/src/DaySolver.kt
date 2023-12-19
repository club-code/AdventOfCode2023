import java.io.File
import java.nio.file.Files
import java.nio.file.Paths
import kotlin.io.path.exists
import kotlin.system.measureTimeMillis

open class DaySolver(private val day: Int) {
    private val year = 2023
    private val cookie = File("cookie.txt").useLines { it.toList() }.first()
    open fun firstPart(): String = "unfinished"
    open fun secondPart(): String = "unfinished"
    fun test() {
        firstPart()
        secondPart()
    }

    fun solve() {
        println(
            "Time to execute: ${
                measureTimeMillis {
                    println(
                        """Day $day responses:
            Step 1 : ${firstPart()}
            Step 2 : ${secondPart()}
            """.trimMargin()
                    )
                }
            }ms")
    }

    val data: List<String> = run {
        val inputDir = Paths.get("inputs");
        if (!inputDir.exists()) Files.createDirectory(inputDir)
        if (!Files.exists(Paths.get("$inputDir/day$day.txt"))) {
            ProcessBuilder(
                "curl",
                "-s", "https://adventofcode.com/$year/day/$day/input",
                "-H", "Cookie:session=$cookie",
                "-o", "$inputDir/day$day.txt"
            ).redirectOutput(ProcessBuilder.Redirect.INHERIT)
                .redirectError(ProcessBuilder.Redirect.INHERIT)
                .start()
                .waitFor()
        }
        File("$inputDir/day$day.txt").useLines { it.toList() }
    }
}