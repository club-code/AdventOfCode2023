class Day2 : DaySolver(2) {
    override val testInput = """Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue
Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red
Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red
Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green""".trimIndent().lines()
    private fun List<String>.transform() = map { line ->
        Game(
            Regex("Game (\\d+)").matchAt(line, 0)!!.groupValues.last().toInt(),
            line.substringAfter(": ").split(";").map { gameLine ->
                Regex("(\\d+) (red|green|blue)").findAll(gameLine).toList().map { it.groupValues }
                    .associate {
                        it[2] to it[1].toInt()
                    }
            }
        )
    }


    data class Game(val id: Int, val setCubesRevelead: List<Map<String, Int>>) {
        override fun toString() = "Game $id: ${setCubesRevelead.size} sets\n" +
                setCubesRevelead.fold("") { acc, line -> acc + "\t$line\n" }

        fun isPossible(maxRed: Int, maxGreen: Int, maxBlue: Int) =
            setCubesRevelead.all {
                (it["red"] ?: 0) <= maxRed &&
                        (it["green"] ?: 0) <= maxGreen &&
                        (it["blue"] ?: 0) <= maxBlue
            }

        fun makePossible() = Triple(setCubesRevelead.maxOf { it["red"] ?: 0 },
            setCubesRevelead.maxOf { it["green"] ?: 0 },
            setCubesRevelead.maxOf { it["blue"] ?: 0 })
        fun power() = makePossible().let { it.first * it.second * it.third }
    }

    override fun firstPart(data: List<String>) = data.transform().filter { it.isPossible(12, 13, 14) }
        .sumOf { it.id }.toString()

    override fun secondPart(data: List<String>) = data.transform().sumOf { it.power() }.toString()
}
