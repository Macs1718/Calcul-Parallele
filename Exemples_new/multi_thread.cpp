# include <iostream>
# include <thread>
# include <vector>
// g++ -std=c++14 -o multi_thread.exe multi_thread.cpp -lpthread
int main()
{
    using std::cout;
    using std::endl;
    using std::thread;
    using std::vector;
    constexpr int nbThreads = 10;
    vector<thread> threads{nbThreads};
    for ( int i = 0; i < threads.size(); ++i )
        threads[i] = thread([](int i) { cout << "Hello from "
                                             << i << endl; }, i );
    for ( auto& t : threads ) t.join();
    return 0;
}