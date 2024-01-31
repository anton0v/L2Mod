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
        int res = atoi(buff);
        if(res > 99 && res % 32 == 0)
            std::cout << res << std::endl;
        else
            std::cout << "ERROR" << std::endl;
    }

    return EXIT_SUCCESS;
}