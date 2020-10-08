/*
    Dawson Dauphinais
    CS426, Homework 2
    Date Last Modified: 09/29/2020

    The purpose of this program is to use multiple threads to print the prime numbers in the specified range using producer and consumers.

    I had help from Jared V. in several places.
    I used GeeksForGeeks as a reference fror the timing code.
*/
#include <iostream>           // cout
#include <thread>             // thread
#include <mutex>              // mutex, unique_lock
#include <condition_variable> // condition_variable
#include <unistd.h>           // usleep
#include <chrono>
using namespace std;
mutex mtx;
condition_variable cv;

class Buffer
{
private:
    condition_variable cv;
    mutex mtx;
    int top_stack;
    int *stack;
    int max_size;

public:
    Buffer(int size)
    {
        top_stack = -1;
        max_size = size;
        stack = new int[size];
    }
    ~Buffer()
    {
        delete stack;
    }
    bool is_empty()
    {
        return (top_stack == -1);
    }
    bool is_full() { return (top_stack == max_size - 1); }
    void put(int x)
    {
        unique_lock<mutex> lock(mtx);
        while (is_full())
        {
            cv.wait(lock);
        }
        top_stack++;
        stack[top_stack] = x;
        cv.notify_all();
    }
    int get()
    {
        unique_lock<mutex> lock(mtx);
        int val;
        while (is_empty())
        {
            cv.wait(lock);
        }
        val = stack[top_stack];
        top_stack--;
        cv.notify_all();
        return val;
    }
};
Buffer buffer(5);
bool isPrime(int maybe)
{
    if (maybe % 2 == 0)
        return false;
    for (int i = 3; i < maybe; i += 2)
        if (maybe % i == 0)
            return false;
    return true;
}
void makePrimes(int start, int stop)
{
    for (int i = start; i < stop; i++)
        if (isPrime(i))
            buffer.put(i);
}
void print()
{
    while (1)
        cout << "Prime " << buffer.get() << endl;
}

int main(int argc, char *argv[])
{
    int num_threads = atoi(argv[1]);
    int thread_job = 1000 / num_threads;
    int beg = 100000001;
    int end = beg + thread_job;
    thread prod[num_threads];
    for (int i = 0; i < num_threads; i++)
    {
        cout << "Range for thread " << i << "-> Start: " << beg << " -> End: " << end << endl;
        prod[i] = thread(makePrimes, beg, end);
        beg = end + 1;
        end += thread_job;
    }
    thread cons = thread(print);

    for (int i = 0; i < num_threads; i++)
    {
        prod[i].join();
    }
    _exit(0);
}