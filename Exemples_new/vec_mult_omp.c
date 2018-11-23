# include <stdio.h>
# include <string.h>
# include <stdlib.h>
#define THRESHOLD1 1000000
#define THRESHOLD2 1000

void init( float* u, float* v, int dim )
{
  for ( int i = 0; i < dim; ++i ) {
    u[i] = i+1;
    v[i] = 2-i;
  }
}

void output( float* u, int dim )
{
  for ( int i = 0; i < dim; ++i ) {
    printf("%f ", u[i]);
  }
  printf("\n");
}

void vec_mult( float* p, float* v1, float *v2, int N )
{
    int i;
    init(v1, v2, N);
#   pragma omp target if (N>THRESHOLD1) map(to: v1[0:N], v2[:N]) map(from: p[0:N])
#   pragma omp parallel for if (N>THRESHOLD2)
    for ( i = 0; i < N; ++i )
        p[i] = v1[i] * v2[i];
    output(p, N);
}

int main( int nargs, char *vargs[])
{
    int dim = 1000;
    if ( nargs > 1 )
        dim = atoi(vargs[1]);
    float* u = (float*)malloc(dim*sizeof(float));
    float* v = (float*)malloc(dim*sizeof(float));
    float* p = (float*)malloc(dim*sizeof(float));
    vec_mult( p, u, v, dim );
    return EXIT_SUCCESS; 
}
