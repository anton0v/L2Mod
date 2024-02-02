#include "TCPConnection.h"

#include <iostream>
#include <cstring>

#ifdef _WIN32
int TCPConnection::_sockCount = 0;
#endif

TCPConnection::TCPConnection(const std::string& ip, const int port) : 
    _ip(ip),
    _port(port)
{
    #ifdef _WIN32
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
    #endif
    Connect(ip, port);
}

TCPConnection::~TCPConnection()
{
    Close();
    #ifdef _WIN32
    if(_sockCount == 0)
        WSACleanup();
    #endif
}

TCPConnection::TCPConnection(TCPConnection && other) noexcept
{
    _sock = other._sock;
    other._sock = NET_SOCKET_ERROR;
}

TCPConnection & TCPConnection::operator=(TCPConnection && other) noexcept
{
    _sock = other._sock;
    other._sock = NET_SOCKET_ERROR;
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
    if (_sock == INVALID_SOCKET_ID) {
        std::cout << "socket function failed with error: \n"; // << WSAGetLastError() << std::endl;
        return;
    }

    int iResult = connect(_sock, reinterpret_cast<sockaddr *>(&_service), sizeof(_service));
    if (iResult == NET_SOCKET_ERROR) {
        _isOpen = false;
        std::cout << "connect function failed with error: \n";// << WSAGetLastError() << std::endl;
        Close();
        return;
    }

    _isOpen = true;
}

bool TCPConnection::Close()
{
    if (!_isOpen)
        return false;
    
    #ifdef _WIN32
    int iResult = closesocket(_sock);
    #else
    int iResult = close(_sock);
    #endif
    if (iResult == NET_SOCKET_ERROR) {
        throw std::runtime_error("closesocket function failed with error: ");
            //+ std::to_string(WSAGetLastError()));
        return false;
    }

    _isOpen = false;

    #ifdef _WIN32
    --_sockCount;
    #endif

    return true;
}

bool TCPConnection::Send(const char* buff)
{
    if (!_isOpen)
        return false;

    int iResult = send(_sock, buff, (int)strlen(buff), 0);
    if (iResult == NET_SOCKET_ERROR) {
        std::cout << "send failed with error: \n";// << WSAGetLastError() << std::endl;
        Close();
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
        std::cout << "recv failed with error: \n";// WSAGetLastError() << std::endl;
        return false;
    }

    return true;
}