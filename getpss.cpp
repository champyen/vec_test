#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint32_t getpss(int pid)
{
    uint32_t ret = 0;

    char fname[1024];
    snprintf(fname, 1024, "/proc/%d/smaps", pid);

    FILE *smap_fp = fopen(fname, "r");
    if(smap_fp != NULL){
        char *line = NULL;
        size_t len = 0;
        ssize_t nread;

        while ((nread = getline(&line, &len, smap_fp)) != -1) {
            if(line[0] == 'P' && line[1] == 's' && line[2] == 's'){
                unsigned int pss;
                sscanf(line, "Pss: %d kB\n", &pss);
                ret += pss;
            }
        }

        free(line);
        fclose(smap_fp);
    }else{
        printf("%s open failed\n", fname);
    }

    return ret;
}

#ifdef GETPSS_TEST
int main(int argc, char** argv)
{
    if(argc != 2){
        printf("%s PID\n", argv[0]);
    } else {
        int pid = atoi(argv[1]);
        printf("pid - %d\n", pid);
        printf("Total PSS - %u kB\n", getpss(pid));
    }
    return 0;
}
#endif