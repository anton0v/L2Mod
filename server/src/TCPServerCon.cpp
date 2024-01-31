#include "TCPServerCon.h"

#include <iostream>

int TCPServerCon::_sockCount = 0;

void TCPServerCon::InitWSA()
{
    if (_sockCount == 0)
    {
        WSADATA info;
        if (WSAStartup(MAKEWORD(2, 0), &info) != 0)
        {
            throw std::runtime_error("WSAStartup error" 
                + std::to_string(WSAGetLastError()));
        }
    }

    ++_sockCount;
}

void TCPServerCon::CloseWSA()
{
    if (_sockCount != 0)
        throw std::runtime_error("must be zero sockets");

    WSACleanup();
}

TCPServerCon::TCPServerCon(const std::string & ip, const int port) : 
    _hasClient(false)
{
    InitWSA();
    Bind(ip, port);
}

TCPServerCon::~TCPServerCon()
{
    Close();
    if(_sockCount == 0)
        CloseWSA();
}

bool TCPServerCon::Close()
{
    if (!_isOpen)
        return false;
    
    int iResult = closesocket(_sock);
    if (iResult == SOCKET_ERROR) {
        throw std::runtime_error("closesocket function failed with error: "
            + std::to_string(WSAGetLastError()));
        return false;
    }

    _isOpen = false;

    --_sockCount;

    return true;
}

void TCPServerCon::Send(const char* buff) const
{
    if (!_isOpen)
        return;

    int iResult = send(_clientSock, buff, (int)strlen(buff), 0);
    if (iResult == SOCKET_ERROR) {
        std::cout << "send failed with error: " << WSAGetLastError() << std::endl;
        closesocket(_sock);
    }
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
        std::cout << "recv failed with error: " << WSAGetLastError() << std::endl;

    _hasClient = false;

    return false;
}

void TCPServerCon::Bind(const std::string& ip, const int port)
{
    if (ip == "")
        return;

    if (_isOpen)
        Close();

    _service.sin_family = AF_INET;
    _service.sin_addr.s_addr = inet_addr(ip.c_str());
    _service.sin_port = htons(port); 

    _sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (_sock == INVALID_SOCKET) {
        std::cout << "socket function failed with error: " << WSAGetLastError() << std::endl;
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

    if ((_clientSock = accept(_sock, nullptr, nullptr)) == SOCKET_ERROR)
    {
        Close();
        throw std::runtime_error("Failed to 'accept()' at port #" +
            std::to_string(_port));
    }
    

    _hasClient = true;
}