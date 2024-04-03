#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>

bool check_vampire(int n) {
    int aux = n;
    int digitarray[10] = {0};
    while(aux != 0) {
        int remainder = aux % 10;
        digitarray[remainder]++;
        aux /= 10;
    }
    for(int i = 2; i <= n / 2; i++) {
        int j;
        if(n % i == 0) {
            j = n / i;
        } else {
            continue;
        }
        int aux1 = i;
        int digitarray1[10] = {0};
        int nrDigits1 = 0;
        while(aux1 != 0) {
            int remainder = aux1 % 10;
            digitarray1[remainder]++;
            aux1 /= 10;
            nrDigits1++;
        }
        int aux2 = j;
        int digitarray2[10] = {0};
        int nrDigits2 = 0;
        while(aux2 != 0) {
            int remainder = aux2 % 10;
            digitarray2[remainder]++;
            aux2 /= 10;
            nrDigits2++;
        }
        if(nrDigits1 == nrDigits2) {
            bool flag = true;
            for(int k = 0; k < 10; k++) {
                int nr = digitarray1[k] + digitarray2[k];
                if(nr != digitarray[k]) {
                    flag = false;
                    break;
                }
            }
            if(flag) {
                return true;
            }
        }
    }

    return false;
}

void swap(int* p1, int* p2)
{
    int temp;
    temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int vampire_numbers[10000];
int current = 0;

int main(int argc, char *argv[]) {
    #pragma omp parallel num_threads(atoi(argv[1]))
    {
        int numbers_found = 0;
        #pragma omp for
        for(int i = 1000; i <= 2000; i++) {
            if(check_vampire(i) == 1) {
                numbers_found++;

                #pragma omp atomic write
                vampire_numbers[current] = i;
                
                #pragma omp atomic
                current++;
            }
        }
        printf("Thread %ld found %d vampire numbers!\n", pthread_self(), numbers_found);
    }
    
    printf("Total count of vampire numbers found is %d!\n", current);

    quickSort(vampire_numbers, 0, current - 1);

    int fd = open("Vnumbers.txt", O_WRONLY | O_CREAT, 0644);

    char buffer[5];
    buffer[4] = '\0';
    for(int i = 0; i < current; i++) {
        printf("Number: %d\n", vampire_numbers[i]);
        int aux = vampire_numbers[i];
        int nr_digits = 0;
        while(aux > 0) {
            aux /= 10;
            nr_digits++;
        }
        int current_index = 0;
        while(aux > 0) {
            buffer[nr_digits - current_index -1] = (char)(aux % 10 + '0');
            aux /= 10;
            current_index++;
        }
        write(fd, buffer, nr_digits);
    }

    close(fd);

    return 0;
}