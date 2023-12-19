import java.io.File
import java.nio.file.Files
import java.nio.file.Paths
import kotlin.io.path.exists
import kotlin.system.measureTimeMillis

abstract class DaySolver(private val day: Int) {
    private val year = 2023
    private val cookie = File("cookie.txt").useLines { it.toList() }.first()
    abstract val testInput: List<String>
    abstract fun firstPart(data:List<String>): String
    abstract fun secondPart(data:List<String>): String
    fun test() {
        println("Test step 1 : ${firstPart(testInput)}")
        println("Test step 2 : ${secondPart(testInput)}")
    }

    fun solve() {
        println(
            "Time to execute: ${
                measureTimeMillis {
                    println(
                        """Day $day responses:
            Step 1 : ${firstPart(data)}
            Step 2 : ${secondPart(data)}
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