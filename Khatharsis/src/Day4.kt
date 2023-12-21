import kotlin.math.pow

class Day4 : DaySolver(4) {
    override val testInput = """
		Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53
		Card 2: 13 32 20 16 61 | 61 30 68 82 17 32 24 19
		Card 3:  1 21 53 59 44 | 69 82 63 72 16 21 14  1
		Card 4: 41 92 73 84 69 | 59 84 76 51 58  5 54 83
		Card 5: 87 83 26 28 32 | 88 30 70 12 93 22 82 36
		Card 6: 31 18 13 56 72 | 74 77 10 23 35 67 36 11
	""".trimIndent().lines()

    private fun String.process() = substringAfter(": ")
        .substringBefore(" |")
        .split(" ")
        .filter { it.isNotBlank() }
        .map { it.toInt() } to substringAfter("| ")
        .split(" ")
        .filter { it.isNotBlank() }
        .map { it.toInt() }

    override fun firstPart(data: List<String>) = data.sumOf { line ->
        val (winningNumbers, drawnNumbers) = line.process()
        val count = drawnNumbers.count { it in winningNumbers }
        return@sumOf if (count == 0) 0 else 2.0.pow(count - 1).toInt()
    }.toString()

    private val countCopies = mutableMapOf<Int, Int>()
    override fun secondPart(data: List<String>) = data.forEach { line ->
        val i = line.substringBefore(":").substringAfterLast(" ").toInt()
        val (winningNumbers, drawnNumbers) = line.process()
        (1..drawnNumbers.count { it in winningNumbers }).forEach { j ->
            countCopies[i + j] = countCopies.getOrDefault(i + j, 0) + 1 +
                    countCopies.getOrDefault(i, 0)
        }
    }.let { (countCopies.values.sum() + data.size).toString() }
}
