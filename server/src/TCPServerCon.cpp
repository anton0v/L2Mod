#include "TCPServerCon.h"

#include <iostream>
#include <cstring>

TCPServerCon::TCPServerCon(const std::string & ip, const int port) : 
    TCPConnection(ip, port),
    _hasClient(false)
{
    Bind(ip, port);
}

void TCPServerCon::Bind(const std::string& ip, const int port)
{
    if (ip == "")
        return;

    if (_isOpen)
        Close();

    _port = port;
    _ip = ip;

    std::memset(&_service, 0, sizeof(_service));

    std::cout << port << std::endl;
    _service.sin_family = PF_INET;
    //_service.sin_addr.s_addr = inet_addr(ip.c_str());
    _service.sin_port = htons(port); 

    _sock = socket(AF_INET, SOCK_STREAM, 0);
    if (_sock == INVALID_SOCKET_ID) {
        std::cout << "socket function failed with error: ";// << WSAGetLastError() << std::endl;
        return;
    }

    if (bind(_sock, reinterpret_cast<sockaddr *>(&_service), sizeof(_service)) != 0)
    {
        Close();
        throw std::runtime_error("Failed to 'bind()' socket to port #" +
            std::to_string(_port));
    }

    if (listen(_sock, 1) != 0)
    {
        Close();
        throw std::runtime_error("Failed to 'listen()' at port #" +
            std::to_string(_port));
    }

    _isOpen = true;
}

void TCPServerCon::Accept()
{
    if(_hasClient)
        return;

    if ((_clientSock = accept(_sock, nullptr, nullptr)) == INVALID_SOCKET_ID)
    {
        Close();
        throw std::runtime_error("Failed to 'accept()' with error #" +
            std::string(strerror(errno)));
    }
    

    _hasClient = true;
}

bool TCPServerCon::Recieve(char* buff, int size)
{
    if (!_isOpen)
        return false;

    int recvBytes = recv(_clientSock, buff, size, 0);
    if (recvBytes > 0)
    {
        std::cout << "Bytes received: " << recvBytes << std::endl;
        return true;
    }
    else if (recvBytes == 0)
        std::cout << "Connection closed\n" << std::endl;
    else
        std::cout << "recv failed with error: ";// << WSAGetLastError() << std::endl;

    _hasClient = false;

    return false;
}