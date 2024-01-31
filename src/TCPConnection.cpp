#include "TCPConnection.h"

#include <iostream>

void TCPConnection::Send(const char* buff) const
{
    if (!_isOpen)
        return;

    int iResult = send(_sock, buff, (int)strlen(buff), 0);
    if (iResult == SOCKET_ERROR) {
        std::cout << "send failed with error: " << WSAGetLastError() << std::endl;
        closesocket(_sock);
    }
}

void TCPConnection::Recieve(char* buff, int size)
{
    if (!_isOpen)
        return;

    int recvBytes = recv(_sock, buff, size, 0);
    if (recvBytes > 0)
    {
        std::cout << "Bytes received: " << recvBytes << std::endl;
    }
    else if (recvBytes == 0)
        std::cout << "Connection closed\n" << std::endl;
    else
        std::cout << "recv failed with error: " << WSAGetLastError() << std::endl;
}