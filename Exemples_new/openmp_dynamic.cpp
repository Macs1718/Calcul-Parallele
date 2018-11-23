# include <iostream>
# include <omp.h>
# include <vector>

int main()
{
    constexpr int n = 1024;
    std::vector<double> a;
    int nbTaches;
#   pragma omp parallel shared(nbTaches)
    {
        nbTaches = omp_get_num_threads();
    }
    a.resize(n*nbTaches);
#   pragma omp parallel shared(a)
    {
        int rang = omp_get_thread_num();
        int deb  = rang*n;
        int fin  = (rang+1)*n-1;
        for ( int i = deb; i <= fin; ++i ) a[i] = 92290+i;
    #   pragma omp critical
        {
            std::cout << "A[" << deb << "] = " << a[deb] << "... A["
                      << fin << "] = " << a[fin] << std::endl;
        }
    }
    return 0;
}