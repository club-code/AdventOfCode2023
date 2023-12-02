#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define RED_DEFAULT   0
#define BLUE_DEFAULT  0
#define GREEN_DEFAULT 0


int main(int argc, char* argv[]){
    FILE* fp = fopen("input", "r");
    uint32_t sum = 0;
    uint32_t game_nbr;

    int32_t n_blue = BLUE_DEFAULT;
    int32_t n_red = RED_DEFAULT;
    int32_t n_green = GREEN_DEFAULT;

    int32_t nc_blue = BLUE_DEFAULT;
    int32_t nc_red = RED_DEFAULT;
    int32_t nc_green = GREEN_DEFAULT;

    int32_t n;
    uint8_t ok = 0;
    
    while (fscanf(fp, "Game %u: ", &game_nbr) > 0){
        n_blue = BLUE_DEFAULT;
        n_red = RED_DEFAULT;
        n_green = GREEN_DEFAULT;
        
        nc_blue = BLUE_DEFAULT;
        nc_red = RED_DEFAULT;
        nc_green = GREEN_DEFAULT;

        //printf("Game %03u :", game_nbr);

        ok = 0;
        while (!ok){
            assert(fscanf(fp, " %d ", &n) > 0);

            switch (fgetc(fp)){
            case 'b':
                nc_blue = MAX(nc_blue, n);
                fseek(fp, 3, SEEK_CUR);
                break;
            case 'r':
                nc_red = MAX(nc_red, n);
                fseek(fp, 2, SEEK_CUR);
                break;
            case 'g':
                nc_green = MAX(nc_green, n);
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
                n_red = MAX(nc_red, n_red);
                n_green = MAX(nc_green, n_green);
                n_blue = MAX(nc_blue, n_blue);

                nc_blue = BLUE_DEFAULT;
                nc_red = RED_DEFAULT;
                nc_green = GREEN_DEFAULT;

                break;
            case '\n':
                n_red = MAX(nc_red, n_red);
                n_green = MAX(nc_green, n_green);
                n_blue = MAX(nc_blue, n_blue);

                ok = 1;
                break;
            default:
                assert(2 == 0);
                break;
            }
        }

        //printf(" [r: %d, g: %d, b: %d]\n", n_red, n_green, n_blue);
        sum += n_red * n_green * n_blue;
        
    }
    printf("SUM : %u\n", sum);
    fclose(fp);
    return 0;
}