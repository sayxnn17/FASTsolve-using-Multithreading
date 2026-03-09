#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

extern double **allocate_matrix(int n);
extern void free_matrix(double **m,int n);
extern double parallel_cramer(int n,int threads,double **A,double *B,double *X);

void write_equations(double **A,double *B,int n)
{
    FILE *f = fopen("equation.txt","w");

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            fprintf(f,"%.2lf*x%d",A[i][j],j);

            if(j<n-1) fprintf(f," + ");
        }

        fprintf(f," = %.2lf\n",B[i]);
    }

    fclose(f);
}

void print_equations(double **A,double *B,int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            printf("%.2lf*x%d",A[i][j],j);

            if(j<n-1) printf(" + ");
        }

        printf(" = %.2lf\n",B[i]);
    }
}

int main(int argc,char *argv[])
{
    if(argc!=2)
    {
        printf("Usage: %s <num_equations>\n",argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);

    srand(time(NULL));

    double **A = allocate_matrix(n);
    double *B = malloc(sizeof(double)*n);

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
            A[i][j] = (rand()%20)-10;

        B[i] = (rand()%20)-10;
    }

    write_equations(A,B,n);

    if(n<10)
    {
        printf("\nGenerated system:\n\n");
        print_equations(A,B,n);
    }

    double *X = malloc(sizeof(double)*n);

    int cpu_threads = sysconf(_SC_NPROCESSORS_ONLN);

    double time_var = parallel_cramer(n,n,A,B,X);
    double time_cpu = parallel_cramer(n,cpu_threads,A,B,X);

    FILE *sol = fopen("solution.txt","w");

    fprintf(sol,"===== Solution Using Cramer's Rule =====\n\n");

    for(int i=0;i<n;i++)
        fprintf(sol,"x%d = %.6lf\n",i,X[i]);

    fprintf(sol,"\n--- Performance Comparison ---\n");

    fprintf(sol,"Threads = Variables (%d)\n",n);
    fprintf(sol,"Execution Time: %lf seconds\n\n",time_var);

    fprintf(sol,"Threads = CPUs (%d)\n",cpu_threads);
    fprintf(sol,"Execution Time: %lf seconds\n",time_cpu);

    fclose(sol);

    printf("\nResults written to solution.txt\n");

    free_matrix(A,n);
    free(B);
    free(X);

    return 0;
}
