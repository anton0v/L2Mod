#include "TCPConnection.h"

TCPConError::TCPConError(const std::string & message)
    #ifdef _WIN32
    : std::runtime_error(message + std::string(" | sys error: ") + std::to_string(WSAGetLastError()))
    #else
    : std::runtime_error(message + std::string(" | sys error: ") + std::strerror(errno))
    #endif
{
}

#ifdef _WIN32
int TCPConnection::_sockCount = 0;
#endif

TCPConnection::TCPConnection(const std::string& ip, const int port) :
    _ip(ip),
    _port(port),
    _isOpen(false),
    _sock(INVALID_SOCKET_ID)
{
    #ifdef _WIN32
    if (_sockCount == 0)
    {
        WSADATA info;
        if (WSAStartup(MAKEWORD(2, 0), &info) != 0)
        {
            throw TCPConError("WSAStartup error");
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
        throw TCPConError("closesocket function failed with error: ");
        return false;
    }

    _isOpen = false;

    #ifdef _WIN32
    --_sockCount;
    #endif

    return true;
}

TCPConnection::TCPConnection(TCPConnection && other) noexcept
{
    if(!other._isOpen)
        return;
    
    _sock = other._sock;
    _ip = other._ip;
    _port = other._port;
    _isOpen = true;
    other._sock = INVALID_SOCKET_ID;
    other._isOpen = false;
}

TCPConnection & TCPConnection::operator=(TCPConnection && other) noexcept
{
    if(!other._isOpen)
        return *this;
    
    if(_isOpen)
        Close();
    
    _sock = other._sock;
    _ip = other._ip;
    _port = other._port;
    _isOpen = true;
    other._sock = INVALID_SOCKET_ID;
    other._isOpen = false;

    return *this;
}