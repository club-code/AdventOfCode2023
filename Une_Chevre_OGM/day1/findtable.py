from Crypto.Util.number import *

number_base = ["one", "two", "three", "four", "five", "six", "seven",
           "eight", "nine"]

number = []
for k in number_base:
    number.append(k + " " + str(bytes_to_long(k[::-1].encode())))
print(number)