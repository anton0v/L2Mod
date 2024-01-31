#include <iostream>
#include <string>

#include "TCPServerCon.h"

int main()
{
    TCPServerCon server;

    server.Bind("127.0.0.1", 88005);
    server.Accept();
    const int bufSize = 10;
    char buff[bufSize];

    while(true)
    {
        server.Recieve(buff, bufSize);
        std::cout << std::string(buff) << std::endl;
    }

    return EXIT_SUCCESS;
}