#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

void lread(char *fname, unsigned int block_size, unsigned int block_count);
void lwrite(char *fname, unsigned int block_size, unsigned int block_count);
void cerror();


void lread(char *fname, unsigned int block_size, unsigned int block_count) {
    struct timeval begin, end;
    gettimeofday(&begin,0);
    long block_total = block_count*block_size;
    unsigned int *buffer;
    unsigned int result=0;
    buffer = (unsigned int *)malloc(block_total);
    int j = 1;
    FILE *fptr;
    if ((fptr = fopen(fname,"rb"))==NULL) {
        cerror();
    }
    double bound = fread(buffer,1,block_total,fptr);
    printf("bound:%f",bound);
    for(unsigned int i=0; i < (block_total/sizeof(unsigned int)); i++) {
        result ^= buffer[i];
    }
    printf("%8x\n",result);
    gettimeofday(&end,0);
    double elapsed = (end.tv_sec - begin.tv_sec) + ((double)(end.tv_usec - begin.tv_usec))*(1E-6);
    double mbCounter = (bound)/1000000;
    double perf = (mbCounter) / elapsed;
    printf("MB's Read: %f \nSeconds Elapsed: %f \nRead Calls: %d \nPerformance: %f MB/s \n", mbCounter, elapsed, j, perf);
    fclose(fptr);
    free(buffer);
}

void lwrite(char *fname, unsigned int block_size, unsigned int block_count) {
    struct timeval begin, end;
    gettimeofday(&begin,0);
    unsigned int block_total = block_count*block_size;
    FILE *fptr;
    fptr = fopen(fname,"wb");
    if (fptr == NULL) {
        cerror();
    }
    for (int i = 0; i < (block_total); i++) {
        if (i % 100 != 0 || i == 0) {
            fprintf(fptr, "%d", rand() % 10);
        }
        if (i % 100 == 0 && i != 0) {
            fprintf(fptr, "\n");
        }
    }
    gettimeofday(&end,0);
    double seconds = end.tv_sec - begin.tv_sec;
    double useconds = end.tv_usec - begin.tv_usec;
    double elapsed = seconds+useconds*(1e-6);
    double perf = ((double)block_total/1000000) / elapsed;
    printf("MB's Written: %f \nSeconds Elapsed: %f \nPerformance: %f MB/s \n", (double)block_total/1000000, elapsed, perf);
    fclose(fptr);
}

void cerror() {
    printf("There was an error, Try again. \n");
    exit(1);
}

int main(int argc, char *argv[]) {
    if(argc != 5) { 
        cerror();
    }
    unsigned int block_size, block_count;
    unsigned int j=2;
        if(argv[j][0] == '-')
        {
            char *fname = argv[1];
            block_size = (unsigned int)atoi(argv[j+1]);
            block_count = (unsigned int)atoi(argv[j+2]);
            switch(argv[j][1])
            {
                case 'r':
                    lread(fname, block_size, block_count);
                    break;
                case 'w':
                    lwrite(fname, block_size, block_count);
                    break;
                default:
                    cerror();
            }
        }
            else 
        {
            cerror();
    }
}
