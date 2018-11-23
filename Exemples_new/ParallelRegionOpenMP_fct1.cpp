# include <iostream>
# include <omp.h>


void function() {
    double a = 92290;
    a += omp_get_thread_num();
    std::cout << "a = " << a << std::endl;
}
int main() {
# pragma omp parallel
{
  function();
}
  return 0;
}
