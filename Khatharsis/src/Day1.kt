class Day1 : DaySolver(1) {
    override val testInput = """
        two1nine
        eightwo1three
        abcone2threexyz
        xtwone3four
        4nineeightseven2
        zoneight234
        7pqrstsixteen
""".trimIndent().lines()

    override fun firstPart(data: List<String>): String = data
        .sumOf { (it.first { it.isDigit() }.toString() + it.last { it.isDigit() }).toInt() }
        .toString()

    private val wordToDigit = mapOf(
        "one" to "1",
        "two" to "2",
        "three" to "3",
        "four" to "4",
        "five" to "5",
        "six" to "6",
        "seven" to "7",
        "eight" to "8",
        "nine" to "9"
    )
    private val validDigits = wordToDigit.keys + wordToDigit.values
    private fun toNumber(s: String) = if (s in wordToDigit.keys) wordToDigit[s]!! else s
    override fun secondPart(data: List<String>) = data
        .sumOf { line ->
            val list = ArrayDeque<String>()
            line.indices.forEach { startingIndex ->
                validDigits.forEach { digit ->
                    if (startingIndex + digit.length <= line.length &&
                        line.substring(startingIndex, startingIndex + digit.length) == digit
                    ) {
                        list.add(line.substring(startingIndex, startingIndex + digit.length))
                    }
                }
            }
            val first = list.first()
            val last = list.last()

            return@sumOf (toNumber(first) + toNumber(last)).toLong()
        }
        .toString()
}