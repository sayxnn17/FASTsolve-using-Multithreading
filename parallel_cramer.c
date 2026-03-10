#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct
{
    int start;
    int end;
    int n;
    double **A;
    double *B;
    double *X;
    double detA;

} ThreadJob;

extern double determinant(double **M,int n);
extern double **allocate_matrix(int n);
extern void free_matrix(double **m,int n);

void *thread_worker(void *arg)
{
    ThreadJob *job = (ThreadJob*)arg;

    for(int k=job->start;k<job->end;k++)
    {
        int n = job->n;

        double **temp = allocate_matrix(n);

        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(j==k)
                    temp[i][j] = job->B[i];
                else
                    temp[i][j] = job->A[i][j];
            }
        }

        double detAi = determinant(temp,n);

        job->X[k] = detAi / job->detA;

        free_matrix(temp,n);
    }

    pthread_exit(NULL);
}

double parallel_cramer(int n,int threads,double **A,double *B,double *X)
{
    pthread_t *tids = malloc(sizeof(pthread_t)*threads);
    ThreadJob *jobs = malloc(sizeof(ThreadJob)*threads);

    double detA = determinant(A,n);

    if(detA==0)
    {
        printf("No unique solution\n");
        exit(1);
    }

    int chunk = n/threads;
    int remainder = n%threads;
    int index = 0;

    struct timespec start,end;

    clock_gettime(CLOCK_MONOTONIC,&start);

    for(int t=0;t<threads;t++)
    {
        int size = chunk + (t<remainder?1:0);

        jobs[t].start=index;
        jobs[t].end=index+size;
        jobs[t].n=n;
        jobs[t].A=A;
        jobs[t].B=B;
        jobs[t].X=X;
        jobs[t].detA=detA;

        pthread_create(&tids[t],NULL,thread_worker,&jobs[t]);

        index += size;
    }

    for(int t=0;t<threads;t++)
        pthread_join(tids[t],NULL);

    clock_gettime(CLOCK_MONOTONIC,&end);

    double time = (end.tv_sec-start.tv_sec) +
                  (end.tv_nsec-start.tv_nsec)/1e9;

    free(tids);
    free(jobs);

    return time;
}