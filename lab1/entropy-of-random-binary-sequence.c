#include <stdlib.h>
#include <stdio.h>
#include <time.h>

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
    int nr_zeros, nr_ones = 0;    
    
    unsigned char *arr = gen_rdm_bytestream(sequence_size);

    printf("%s", arr);

    printf("First byte %d %d", arr[0], arr[1]);

    for(int i = 0; i < sequence_size; i++) {
        for(int j = 0; j < 8; j++) {
            ((a >> 3)  & 0x01)
        }
    }
    
    return 0;
}