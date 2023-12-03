#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#define RED_DEFAULT   12
#define BLUE_DEFAULT  14
#define GREEN_DEFAULT 13

int main(int argc, char* argv[]){
    FILE* fp = fopen("input", "r");
    uint32_t sum = 0;
    uint32_t game_nbr;

    int32_t n_blue = BLUE_DEFAULT;
    int32_t n_red = RED_DEFAULT;
    int32_t n_green = GREEN_DEFAULT;

    int32_t n;
    uint8_t ok = 0;
    
    while (fscanf(fp, "Game %u: ", &game_nbr) > 0){
        n_blue = BLUE_DEFAULT;
        n_red = RED_DEFAULT;
        n_green = GREEN_DEFAULT;
        
        //printf("Game %03u :", game_nbr);

        ok = 0;
        while (!ok){
            //printf(" w");
            assert(fscanf(fp, " %d ", &n) > 0);

            switch (fgetc(fp)){
            case 'b':
                n_blue -= n;
                fseek(fp, 3, SEEK_CUR);
                break;
            case 'r':
                n_red -= n;
                fseek(fp, 2, SEEK_CUR);
                break;
            case 'g':
                n_green -= n;
                fseek(fp, 4, SEEK_CUR);
                break;
            default:
                assert(1 == 0);
                break;
            }

            switch (fgetc(fp)){
            case ',': 
                break;
            case ';':
                //printf(" [r: %d, g: %d, b: %d]", n_red, n_green, n_blue);
                if (n_green < 0 || n_blue < 0 || n_red < 0){
                    ok = 2;
                    //printf(" nop");
                }
                else{
                    ok = 0;
                    //printf(" ok");
                    n_blue = BLUE_DEFAULT;
                    n_red = RED_DEFAULT;
                    n_green = GREEN_DEFAULT;
                }
                break;
            case '\n':
                //printf(" end");
                if (n_green < 0 || n_blue < 0 || n_red < 0)
                    ok = 3;
                else
                    ok = 1;
                break;
            default:
                assert(2 == 0);
                break;
            }
        }
        if (ok == 1){
            //printf(" OK\n");
            sum += game_nbr;
        }
        else{
            if (ok == 2)
                while (fgetc(fp) != '\n') {}
            //printf(" NOP \n");
        }
    }
    printf("SUM : %u\n", sum);
    fclose(fp);
    return 0;
}