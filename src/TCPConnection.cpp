#include "TCPConnection.h"


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
    #endif
}

TCPConnection::~TCPConnection()
{
    Close();
    #ifdef _WIN32
    if(_sockCount == 0)
        WSACleanup();
    #endif
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