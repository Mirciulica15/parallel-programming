#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

unsigned char *gen_rdm_bytestream (size_t num_bytes) {
    unsigned char *stream = malloc (num_bytes);
    size_t i;

    for (i = 0; i < num_bytes; i++) {
        stream[i] = rand();
    }

    return stream;
}

int main(int argc, char *argv[]) {

    int sequence_size = atoi(argv[1]);

    srand ((unsigned int) time (NULL));  
    
    unsigned char *arr = gen_rdm_bytestream(sequence_size);

    printf("%s", arr);

    int counter1 = 0, counter0 = 0;

    for (int i = 0; i < sequence_size; i++) {
        for (int j = 0; j < 8; j++) {
            if ((arr[i] >> j) & 0x01) {
                counter1++;
            } else {
                counter0++;
            }
        }
    }

    printf("\n Nr ones: %d, Nr zeros: %d \n", counter1, counter0);

    //  E = - (O/T)*log2(O/T) – (Z/T)*log2(Z/T)

    double onesPerTotal = (double)counter0 / (double)(sequence_size * 8);
    double zerosPerTotal = (double)1 - onesPerTotal;
    double entropy = - (onesPerTotal * log2l(onesPerTotal) - zerosPerTotal * log2l(zerosPerTotal));

    printf("onesPerTotal: %f, zerosPerTotal: %f, Entropy: %f \n", onesPerTotal, zerosPerTotal, entropy);

    return 0;
}