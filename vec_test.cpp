#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>
#include <utility>

#include "getpss.h"

using namespace std;
int main(void)
{
    vector<uint64_t> vec1;
    vector<vector<uint64_t>> vec2;
    vector<pair<uint64_t, uint64_t>> vec3;
    vector<uint64_t> vec4;
    vector<uint64_t> vec5;
    vector<uint64_t> vec6;

    srand(time(NULL));

    for(int i = 0; i < 1024*1024+1024; i++){
        vec1.emplace_back(rand());
        vec2.emplace_back();
        vec3.emplace_back(rand(), rand());
        vec4.emplace_back(rand());

        if(i > 1024){
            for(int j = 0; j < 6; j++){
                int idx = rand() % i;
                vec2[idx].emplace_back(rand());
            }
        }
    }

    printf("capacity %lu %lu %lu %lu %lu %lu\n",
        vec1.capacity(),
        vec2.capacity(),
        vec3.capacity(),
        vec4.capacity(),
        vec5.capacity(),
        vec6.capacity()
    );

    // if the next 3 lines are commented out, Pss value of each process will decrease.
    #if 1
    vector<uint64_t>().swap(vec1);
    vector<vector<uint64_t>>().swap(vec2);
    vector<pair<uint64_t, uint64_t>>().swap(vec3);
    #endif

    printf("Before fork[%d] %u KB\n", getpid(), getpss(getpid()));

    for(int i = 0; i < 32; i++){
        int pid = fork();
        if(pid == 0) break;
    }

    for(int i = 0; i < 1024*1024+1024; i++){
        vec5.emplace_back(rand());
        vec6.emplace_back(rand());
    }

    vector<uint64_t>().swap(vec4);
    vector<uint64_t>().swap(vec5);
    vector<uint64_t>().swap(vec6);

    printf("pid-%d %u KB\n", getpid(), getpss(getpid()));

    return 0;
}
