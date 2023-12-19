#!/bin/bash
if [ $# -ne 1 ]; then
  echo "Wrong number of argument: need at least one" >&2
  exit 1
fi

dayNumber=$1
filename="src/Day$dayNumber.kt"
if [ -f "$filename" ]; then
  echo "Day already exists" >&2
  exit 2
fi

touch "$filename"
echo "class Day$dayNumber : DaySolver($dayNumber) {" >> "$filename"
echo -e "\toverride val testInput= \"\"\"\"\"\".trimIndent().lines()" >> "$filename"
echo -e "\toverride fun firstPart(data: List<String>) = \"unfinished\"" >> "$filename"
echo -e "\toverride fun secondPart(data: List<String>) = \"unfinished\"" >> "$filename"
echo "}" >> "$filename"
git add "$filename"
