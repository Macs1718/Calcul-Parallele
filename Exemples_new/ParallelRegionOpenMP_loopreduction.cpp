# include <iostream>
# include <omp.h>

int main() {
  const int n = 5;
  int i, s = 0, p = 1, r = 1;
  
# pragma omp parallel for reduction(+:s) reduction(*:p,r)
  for ( i = 1; i <= n; ++i ) {
      s += 1;
      p *= 2;
      r *= 3;
  }
  std::cout << "s = "<<s<< ", p = " <<p<< ", r = " <<r<< std::endl;
  return 0;
}
