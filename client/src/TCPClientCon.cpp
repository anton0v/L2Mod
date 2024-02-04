#include "TCPClientCon.h"

#include <iostream>
#include <cstring>

TCPClientCon::TCPClientCon(const std::string& ip, const int port) : 
    TCPConnection(ip, port)
{
    Connect(ip, port);
}

void TCPClientCon::Connect(const std::string& ip, const int port)
{
    if (ip == "")
        return;

    _service.sin_family = AF_INET;
    _service.sin_addr.s_addr = inet_addr(ip.c_str());
    _service.sin_port = htons(port);

    if (_isOpen)
        Close();

    _sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (_sock == INVALID_SOCKET_ID)
        throw TCPConError("socket function failed");

    int iResult = connect(_sock, reinterpret_cast<sockaddr *>(&_service), sizeof(_service));
    if (iResult == NET_SOCKET_ERROR) {
        std::cout << "connect function failed with error: ";
        #ifdef _WIN32
        std::cout << std::to_string(WSAGetLastError()) << std::endl;
        #else
        std::cout <<  std::strerror(errno) << std::endl; 
        #endif
        Close();
        return;
    }

    _isOpen = true;
    #ifdef _WIN32
    ++_sockCount;
    #endif
}

bool TCPClientCon::Send(const char* buff)
{
    if (!_isOpen)
        return false;

    #ifdef _WIN32
    int iResult = send(_sock, buff, (int)strlen(buff), 0);
    #else
    int iResult = send(_sock, buff, (int)strlen(buff), MSG_NOSIGNAL);
    #endif
    
    if (iResult == NET_SOCKET_ERROR) {
        std::cout << "send failed with error: ";
        #ifdef _WIN32
        std::cout << std::to_string(WSAGetLastError()) << std::endl;
        #else
        std::cout <<  std::strerror(errno) << std::endl; 
        #endif
        Close();
        return false;
    }
    return true;
}

bool TCPClientCon::Recieve(char* buff, int size)
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
        std::cout << "recv failed with error: ";
        #ifdef _WIN32
        std::cout << std::to_string(WSAGetLastError()) << std::endl;
        #else
        std::cout <<  std::strerror(errno) << std::endl; 
        #endif
        return false;
    }

    return true;
}