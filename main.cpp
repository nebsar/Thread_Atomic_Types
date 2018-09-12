/* 
 * File:   main.cpp
 * Author: Eagleye
 *
 * Created on September 12, 2018, 12:32 AM
 */

/* The C++11 Concurrency Library introduces Atomic Types as a template class: std::atomic.
 * You can use any Type you want with that template and the operations on that variable will be atomic and so thread-safe.
 * It has to be taken into account that it is up to the library implementation
 * to choose which syncronization mechanism is used to make the operations on that type atomic.
 * On standard platforms for integral types like int, long, float, ... it will be some lock-free technique.
 * If you want to make a big type (let's saw 2MB storage), you can use std::atomic as well, but mutexes will be used.
 * In this case, there will be no performance advantage.
 * The main functions that std::atomic provide are the store and load functions that atomically set and get the contents of the std::atomic.
 * Another interesting function is exchange, that sets the atomic to a new value and returns the value held previously.
 * Finally, there are also two functions compare_exchange_weak and 
 * compare_exchance_strong that performs atomic exchange only if the value is equal to the provided expected value.
 * These two last functions can be used to implement lock-free algorithms.
 * std::atomic is specialized for all integral types to provide member functions specific to integral (like operators ++, --, fetch_add, fetch_sub, ...).
 * It is fairly easy to make the counter safe with std::atomic: 
 */

#include <thread>
#include <atomic>
#include <iostream>
#include <vector>

struct AtomicCounter {
    std::atomic<int> value;

    AtomicCounter() : value(0) {
    }

    void increment() {
        ++value;
    }

    void decrement() {
        --value;
    }

    int get() {
        return value.load();
    }
};

int main() {
    AtomicCounter counter;

    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i) {
        threads.push_back(std::thread([&counter]() {
            for (int i = 0; i < 500; ++i) {
                counter.increment();
            }
        }));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    std::cout << counter.get() << std::endl;

    return 0;
}
