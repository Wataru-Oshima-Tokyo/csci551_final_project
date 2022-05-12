#include <iostream>
#include <pthread.h>
#include <unistd.h>
#define rep(i,a,b) for(int i=a; i<b;i++)
#define Z 10000
int p[Z][Z];
void* DoWork(void* args) {
    printf("ID: %lu, CPU: %d\n", pthread_self(), sched_getcpu());
    // int p[Z][Z];
    int i,j;
    for(i=0; i<Z; i++){
        for(j=0; j<Z; j++){
            p[i][j] = 1;
        }
    }
    return 0;
}

int main() {   

    int numberOfProcessors = sysconf(_SC_NPROCESSORS_ONLN);
    printf("Number of processors: %d\n", numberOfProcessors);

    pthread_t threads[numberOfProcessors];

    pthread_attr_t attr;
    cpu_set_t cpus;
    pthread_attr_init(&attr);
    rep(z,0,5){
        for (int i = 0; i < numberOfProcessors; i++) {
       CPU_ZERO(&cpus);
       CPU_SET(i, &cpus);
       pthread_attr_setaffinity_np(&attr, sizeof(cpu_set_t), &cpus);
       pthread_create(&threads[i], &attr, DoWork, NULL);
    }

    for (int i = 0; i < numberOfProcessors; i++) {
        pthread_join(threads[i], NULL);
    }
    }


    return 0;
}