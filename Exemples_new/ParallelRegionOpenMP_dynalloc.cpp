# include <iostream>
# include <omp.h>

int main() {
    int nbTaches, i, deb, fin, rang, n = 1024;
    double* a;
#   pragma omp parallel
    { nbTaches = omp_get_num_threads(); }

    a = new double[n*nbTaches];
    
#   pragma omp parallel default(none) private(deb,fin,rang,i) \
                        shared(a,n,std::cout)
    {
        rang = omp_get_thread_num();
        deb  = rang*n; fin = (rang+1)*n-1;
        for ( i = deb; i <= fin; i++ ) a[i] = 92290. + double(i);
        std::cout << "Rang : " << rang << " A[" << deb << "] = " << a[deb]
                  << ", A[" << fin << "] = " << a[fin] << std::endl;
    }
    
    delete [] a;
    return 0;
}
