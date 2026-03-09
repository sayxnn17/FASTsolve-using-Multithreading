#include <stdio.h>
#include <stdlib.h>

double **allocate_matrix(int n)
{
    double **m = malloc(n * sizeof(double*));

    for(int i=0;i<n;i++)
        m[i] = malloc(n*sizeof(double));

    return m;
}

void free_matrix(double **m,int n)
{
    for(int i=0;i<n;i++)
        free(m[i]);

    free(m);
}

double determinant(double **M,int n)
{
    if(n==1)
        return M[0][0];

    double det=0;

    for(int col=0;col<n;col++)
    {
        double **minor = allocate_matrix(n-1);

        for(int i=1;i<n;i++)
        {
            int cindex=0;

            for(int j=0;j<n;j++)
            {
                if(j==col) continue;

                minor[i-1][cindex++] = M[i][j];
            }
        }

        double sign = (col%2==0)?1:-1;

        det += sign * M[0][col] * determinant(minor,n-1);

        free_matrix(minor,n-1);
    }

    return det;
}