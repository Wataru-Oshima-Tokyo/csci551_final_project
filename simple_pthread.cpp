#include <iostream>
#include <pthread.h>
#define NUM_THREADS 3
using namespace std;
#define ROW 9
#define COL 9
#define rep(i,a,b) for(int i=a; i<b;i++)
#define MULTI
int p[ROW][COL];

struct arg_struct{
    int index;
};

//Failed!!!

void *test2(void *args){
    arg_struct _args  = *((struct arg_struct*)args);
    int idx = _args.index;
    int coefficient = (ROW/NUM_THREADS);
    int r_start = idx%coefficient*coefficient;
    int r_end = r_start+coefficient;
    int x=0;
    while(idx>coefficient*x)
        x++;
    int c_start = x* coefficient;
    int c_end = c_start + coefficient;
    int i,j;
    cout << "ROW: " << r_start << " to " << r_end
    << "\nCOL: " << c_start << " to " <<c_end <<endl;
    for(i=r_start; i<r_end;i++)
        for(j=c_start; j<c_end;j++)
            p[i][j] =1;
    pthread_exit(0);
}



void *test(void *args){
    arg_struct _args  = *((struct arg_struct*)args);
    int idx = _args.index;
    int p_start = (idx*(ROW/NUM_THREADS));
    int p_end = p_start + (ROW/NUM_THREADS);
    // cout << idx << " " << p_start << " "<<p_end << endl;
    int i,j;
    for(i=p_start; i<p_end;i++)
        for(j=0; j<COL;j++)
            // p[i][j] =i*COL+j;
            p[i][j] =1;
    pthread_exit(0);
}


int main(){
   std::cout << "hello world" << std::endl;
   pthread_t threads[NUM_THREADS];
	struct timespec start, stop;
	double fstart, fstop;
//    pthread_attr_t attr;
//    pthread_attr_init(&attr);

   int rc;
   int i;
   arg_struct args[NUM_THREADS];

   clock_gettime(CLOCK_MONOTONIC, &start); fstart=(double)start.tv_sec + ((double)start.tv_nsec/1000000000.0);
rep(i,0,5){


    #ifdef MULTI
    for(i=0; i<NUM_THREADS; i++){
        //  struct arg_struct *args = (struct arg_struct *)malloc(sizeof(struct arg_struct));
        //  std::cout << "cretae a thread no." << i << std::endl;
        args[i].index =i;
        //  cout << args[i].index <<endl;
        rc = pthread_create(&threads[i], NULL, test2, (void *)&args[i]);
        if(rc){
        std::cout << "Error: unable to create thread, " << rc <<std::endl;
        exit(-1);
        }
    }
    for(int i=0; i<NUM_THREADS;i++)
            pthread_join(threads[i], NULL);
    puts("pthread finsied");
    #else
        rep(i,0,ROW)
            rep(j,0,COL)
                p[i][j] =1;
    #endif
}
   clock_gettime(CLOCK_MONOTONIC, &stop); fstop=(double)stop.tv_sec + ((double)stop.tv_nsec/1000000000.0);
    rep(i,0,ROW){
        rep(j,0,COL){
            printf("%d ", p[i][j]);
        }
        printf("\n");
    }
    printf("\nThe toatal time is %f\n", (fstop-fstart));
    return 0;
}