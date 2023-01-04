#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void lread(char *fname, long block_size);
void cerror();

void lread(char *fname, long block_size){
    struct timeval begin, end;
    unsigned int *buffer;
    buffer = (unsigned int *)malloc(block_size*4);
    unsigned int result = 0;
    double bound; 
    double readCycle = 0;
    int j = 0;
    FILE *fptr;
    if ((fptr = fopen(fname,"rb"))==NULL) {
        cerror();
    }
    gettimeofday(&begin,0);
    while((bound = fread(buffer,4,block_size,fptr)) > 0) {
        for (unsigned int i = 0; i < bound; i++) {
            result ^= buffer[i];
        }
        j++;
        readCycle += bound;
     
    }
    gettimeofday(&end,0);
    printf("%8x\n",result);
    double elapsed = (end.tv_sec - begin.tv_sec) + ((double)(end.tv_usec - begin.tv_usec))*(1E-6);
    double mbCounter = (readCycle*4)/1000000;
    double perf = (mbCounter) / elapsed;
    printf("MB's Read: %f \nSeconds Elapsed: %f \nRead Calls: %d \nPerformance: %f MB/s \nThe block_count for this read was %ld\n", mbCounter, elapsed, j, perf, (unsigned long)(mbCounter*1e6/block_size));
    fclose(fptr);
}

int main(int argc, char *argv[]) {
	printf("Fastest Read: MB/S Read: 2818.738176, Seconds: 1.050364, Performance: 2683.582240 MB/s \n");
    char *fname = argv[1];
    lread(fname, 20480);
}
