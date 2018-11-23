# include <iostream>
# include <cstdio>
# include <omp.h>

int main() {
  float a = 92290;
# pragma omp parallel default(none) private(a) shared(std::cout)
  { // Début de la région parallèle
    a = a + 290;
    // std::cout ne marche pas ???
    std::cout << " a = " << a << std::endl;
  }
  return 0;
}
