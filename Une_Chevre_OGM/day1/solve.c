#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

#define FILENAME "input"

int main(int argc, char* argv[]){
    FILE* fp = fopen(FILENAME, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    char* line = NULL;
    size_t len = 0;
    uint32_t sum = 0;
    uint8_t c = 0;
    char l = 0;
    while (getline(&line, &len, fp) != -1) {
        c = l = 0;
        for (uint32_t i = 0; line[i] != '\n'; i++){
            if (isdigit(line[i])){
                c += (line[i] - '0') * 10;
                for (uint32_t j = i; line[j] != '\n'; j++){
                    if (isdigit(line[j]))
                        l = line[j];
                }
                c += l - '0';
                break;
            }
        }
        sum += c;
    }
    printf("%d\n", sum);
    fclose(fp);
    return 0;
}