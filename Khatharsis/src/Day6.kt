class Day6 : DaySolver(6) {
    override val testInput = """
		Time:      7  15   30
		Distance:  9  40  200
	""".trimIndent().lines()

    private fun String.process() = substringAfter(":").split(" ").filter { it.isNotBlank() }.map { it.toLong() }
    private fun List<String>.process() = this[0].process().zip(this[1].process()).map { Race(it.first, it.second) }


    private data class Race(val time: Long, val distance: Long) {
        fun countWaysToWin() = (1..<time).count { pressTime ->
            pressTime * (time - pressTime) > distance
        }
    }

    override fun firstPart(data: List<String>) = data.process().map { it.countWaysToWin() }.reduce {acc, i -> acc * i}.toString()

    override fun secondPart(data: List<String>) = Race(
        data[0].substringAfter(":").filter { it != ' ' }.toLong(),
        data[1].substringAfter(":").filter { it != ' ' }.toLong()
    ).countWaysToWin().toString()
}
