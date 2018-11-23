# include <iostream>
# include <omp.h>

int main() {
#pragma omp parallel
{
  double a = 92290.;
# pragma omp master
  {
      a = -92290.;
  }
  int rang = omp_get_thread_num();
  std::cout << "rang " << rang << " : a = " << a << std::endl;
}

  return 0;
}
