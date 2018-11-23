  # include <iostream>
  # include <omp.h>
  
  int main() {
    float a;
    int p;
    a = 92290; p = 0;
  # pragma omp parallel
    { // Début de la région parallèle
      p = omp_in_parallel();
      std::cout << " a = " << a << " et p = " << p << std::endl;
    }
    return 0;
  }
