# include <iostream>
# include <omp.h>

void function(double& a, double& b) {
    b = a + omp_get_thread_num();
    std::cout << "b = " << b << std::endl;
}

int main()
{
  double a = 92290, b;
# pragma omp parallel shared(a) private(b)
  {
      function(a,b);
  }
  return 0;
}
