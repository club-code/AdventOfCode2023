#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

#define FILENAME "input"

//const uint8_t lennum[] = {0, 3, 3, 5, 4, 4, 3, 5, 5, 4};

const uint8_t lennum[] = {0, 2, 2, 4, 4, 3, 3, 4, 4, 3};
//const uint8_t lennum[] = {0, 1, 1, 1, 1, 1, 1, 1, 1, 1};
static inline int to_int(uint64_t a){
    switch (a & 0xffffffffffL){
    case 435493693556L:
        return 3;
    case 474148660595L:
        return 7;
    case 499967813989L:
        return 8;
    default:
        break;
    }

    switch (a & 0xffffffffL){
    case 1920298854L:
        return 4;
    case 1702259046L:
        return 5;
    case 1701734766L:
        return 9;
    default:
        break;
    }

    switch (a & 0xffffffL){
    case 6647407L:
        return 1;
    case 7305076L:
        return 2;
    case 7891315L:
        return 6;
    default:
        break;
    }
    return 0;
}

int main(int argc, char* argv[]){
    FILE* fp = fopen(FILENAME, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    char* line = NULL;
    size_t len = 0;
    uint32_t sum = 0;
    uint8_t c = 0;
    uint8_t incr = 0;
    uint8_t converted = 0;
    uint32_t k = 0;
    char l = 0;
    while (getline(&line, &len, fp) != -1) {
        c = l = 0;
        for (uint32_t i = 0; line[i] != '\n'; i++){
            converted = 0;
            if ((converted = to_int(*(uint64_t*)(line + i))) || isdigit(line[i])){
                if (converted){
                    l = converted;
                    incr = lennum[l];
                } 
                else{
                    l = (line[i] - '0');
                    incr = 1;
                }
                c = l * 10;
                //printf("%s, :", line + i + incr);
                k = i + incr;
                for (uint32_t j = k; line[j] != '\n';j += incr){
                    incr = 1;
                    if ((converted = to_int(*(uint64_t*)(line + j))) || isdigit(line[j])){
                        if (converted){
                            l = converted;
                            incr = lennum[l];
                        } 
                        else
                            l = (line[j] - '0');
                    }
                }
                c += l;
                break;
            }
        }
        sum += c;
    }
    printf("%d\n", sum);
    fclose(fp);
    return 0;
}