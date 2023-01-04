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
void cerror() {
    printf(" Usage: ./run1 <filename> <blocksize> \n");
    exit(1);
}
int main(int argc, char *argv[]) {
    if(argc != 3) { 
        cerror();
    }
    if (!((argv[1][0] >= 'A' && argv[1][0] >= 'Z')|| (argv[1][0] >= 'a' && argv[1][0] <= 'z'))) {
        cerror();
    }
    if ((atoi(argv[2]) <= 0) || (atoi(argv[2]) > 4294967295)) {
    	printf("<blocksize> cannot exceed uint size of %ld and must be greater than 0 \n", 4294967295);
    	cerror();
    }
    char *fname = argv[1];
    long block_size = (long)atoi(argv[2]);
    lread(fname, block_size);
}
