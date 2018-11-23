# include <iostream>
# include <omp.h>

int main() {
  float a = 92000;
# pragma omp parallel default(none) firstprivate(a) shared(std::cout)
  { // Début de la région parallèle
    a = a + 290;
    std::cout << " a = " << a << std::endl;
  }
  return 0;
}
