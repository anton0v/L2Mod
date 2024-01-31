#include "TCPConnection.h"

#include <iostream>

int TCPConnection::_sockCount = 0;

void TCPConnection::InitWSA()
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

void TCPConnection::CloseWSA()
{
    if (_sockCount != 0)
        throw std::runtime_error("must be zero sockets");

    WSACleanup();
}

TCPConnection::TCPConnection(const std::string& ip, const int port) : 
    _ip(ip),
    _port(port)
{
    InitWSA();
    Connect(ip, port);
}

TCPConnection::~TCPConnection()
{
    Close();
    if(_sockCount == 0)
        CloseWSA();
}

TCPConnection::TCPConnection(TCPConnection && other) noexcept
{
    _sock = other._sock;
    other._sock = SOCKET_ERROR;
}

TCPConnection & TCPConnection::operator=(TCPConnection && other) noexcept
{
    _sock = other._sock;
    other._sock = SOCKET_ERROR;
    return *this;
}

void TCPConnection::Connect(const std::string& ip, const int port)
{
    if (ip == "")
        return;

    _service.sin_family = AF_INET;
    _service.sin_addr.s_addr = inet_addr(ip.c_str());
    _service.sin_port = htons(port);

    if (_isOpen)
        Close();

    _sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (_sock == INVALID_SOCKET) {
        std::cout << "socket function failed with error: " << WSAGetLastError() << std::endl;
        return;
    }

    int iResult = connect(_sock, (SOCKADDR*)&_service, sizeof(_service));
    if (iResult == SOCKET_ERROR) {
        _isOpen = false;
        std::cout << "connect function failed with error: " << WSAGetLastError() << std::endl;
        iResult = closesocket(_sock);
        if (iResult == SOCKET_ERROR)
            std::cout << "closesocket function failed with error: " << WSAGetLastError() << std::endl;
        return;
    }

    _isOpen = true;
}

bool TCPConnection::Close()
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

bool TCPConnection::Send(const char* buff)
{
    if (!_isOpen)
        return false;

    int iResult = send(_sock, buff, (int)strlen(buff), 0);
    if (iResult == SOCKET_ERROR) {
        std::cout << "send failed with error: " << WSAGetLastError() << std::endl;
        closesocket(_sock);
        _isOpen = false;
        return false;
    }
    return true;
}

bool TCPConnection::Recieve(char* buff, int size)
{
    if (!_isOpen)
        return false;

    int recvBytes = recv(_sock, buff, size, 0);
    if (recvBytes > 0)
    {
        std::cout << "Bytes received: " << recvBytes << std::endl;
    }
    else if (recvBytes == 0)
        std::cout << "Connection closed\n" << std::endl;
    else
    {
        std::cout << "recv failed with error: " << WSAGetLastError() << std::endl;
        return false;
    }

    return true;
}