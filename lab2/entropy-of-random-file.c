#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

int main(int argc, char *argv[]) {

    FILE *fileptr;
    char *buffer;
    long filelen;

    fileptr = fopen("sample.txt", "rb");
    fseek(fileptr, 0, SEEK_END);
    filelen = ftell(fileptr);
    rewind(fileptr);

    buffer = (char *)malloc(filelen * sizeof(char));
    fread(buffer, filelen, 1, fileptr);
    fclose(fileptr);
 
    int counter1 = 0, counter0 = 0;

    for (int i = 0; i < filelen; i++) {
        for (int j = 0; j < 8; j++) {
            if ((buffer[i] >> j) & 0x01) {
                counter1++;
            } else {
                counter0++;
            }
        }
    }

    printf("\n Nr ones: %d, Nr zeros: %d \n", counter1, counter0);

    //  E = - (O/T)*log2(O/T) – (Z/T)*log2(Z/T)

    double onesPerTotal = (double)counter0 / (double)(filelen * 8);
    double zerosPerTotal = (double)1 - onesPerTotal;
    double entropy = - (onesPerTotal * log2l(onesPerTotal) - zerosPerTotal * log2l(zerosPerTotal));

    printf("onesPerTotal: %f, zerosPerTotal: %f, Entropy: %f \n", onesPerTotal, zerosPerTotal, entropy);

    return 0;
}