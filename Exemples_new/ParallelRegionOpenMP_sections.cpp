# include <iostream>
# include <omp.h>

int main() {
# pragma omp parallel
{
#  pragma omp sections nowait
   {
#     pragma omp section 
      for (int i = 0; i < 10; ++i)
	std::cout << "Thread one ! --> " << i << std::endl;
#     pragma omp section
      for (int i = -10; i < 0; i += 2)
	std::cout << "Thread two ! --> " << i << std::endl;
    }
}
  return 0;
}
