#include <iostream>
#include <string>
#include <mutex>
#include <thread>
#include <condition_variable>

#include "StringHandler.h"
#include "Summator.h"

#define BUFFER_SIZE 128

int main()
{
    char buffer[BUFFER_SIZE];
    std::fill(buffer, buffer + BUFFER_SIZE, '\0');
    bool isEnd = false;

    std::mutex mut;
    std::condition_variable cond;
    
    std::thread outputHandle([&]()
    {
        Summator summator;
        while(!isEnd)
        {
            std::unique_lock<std::mutex> lock(mut);
            cond.wait(lock, [&](){return (buffer[0] != '\0');});

            summator.SumFromKBString(std::string(buffer));
            
            std::cout << summator.GetSum() << "\n";
            std::fill(buffer, buffer + BUFFER_SIZE, '\0');

            lock.unlock();
            cond.notify_one();
        }
    });

    std::string input;
    StringHandler handler;

    while(input != "0")
    {
        std::unique_lock<std::mutex> lock(mut);
        cond.wait(lock, [&](){return buffer[0] == '\0';});

        std::cin >> input;
        
        handler.Handle(input);
        std::string res = handler.GetKBString();
        
        std::copy(res.begin(), res.end(), buffer);

        lock.unlock();
        cond.notify_one();
    }

    isEnd = true;

    outputHandle.join();

    return EXIT_SUCCESS;
}