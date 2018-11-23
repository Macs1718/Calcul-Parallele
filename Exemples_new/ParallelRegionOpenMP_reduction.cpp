# include <iostream>
# include <omp.h>

int main() {
    int s = 0;
#  pragma omp parallel default(none) reduction(+:s)
    {
        s = omp_get_thread_num()+1;
    }
    std::cout << "s = " << s << std::endl;
    return 0;
}
