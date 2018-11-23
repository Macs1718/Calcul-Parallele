# include <iostream>
# include <thread>
// g++ -std=c++14 -o one_thread.exe one_thread.cpp -lpthread
void call_from_thread() {
    std::cout << "Hello world !" << std::endl;
}

int main()
{
    using std::cout;
    using std::endl;
    using std::thread;
    thread t1(call_from_thread);
    thread t2([]() 
        { cout << "Another hello !" << endl; });
    t1.join();
    t2.join();
    return 0;
}