#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
    if (argc != 3) {
        exit(-1);
    }
    char *fname = argv[1];
    int n = atoi(argv[2]);
    FILE *fptr;
    if ((fptr = fopen(fname,"rb"))==NULL) {
        exit(-1);
    }
    for(int i = 0; i < n; i++) {
        lseek(fptr, 0, i);
    }
}