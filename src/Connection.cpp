#include "Connection.h"

int Connection::_sockCount = 0;

void Connection::InitWSA()
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

void Connection::CloseWSA()
{
    if (_sockCount != 0)
        throw std::runtime_error("must be zero sockets");

    WSACleanup();
}

Connection::Connection(const std::string& ip, const int port)
{
    Connect(ip, port);
}

Connection::~Connection()
{
    Close();
    if(_sockCount == 0)
        CloseWSA();
}

Connection::Connection(Connection && other) noexcept
{
    _sock = other._sock;
    other._sock = SOCKET_ERROR;
}

Connection & Connection::operator=(Connection && other) noexcept
{
    _sock = other._sock;
    other._sock = SOCKET_ERROR;
    return *this;
}

void Connection::Connect(const std::string& ip, const int port)
{
    if (ip == "")
        return;

    _service.sin_family = AF_INET;
    _service.sin_addr.s_addr = inet_addr(ip.c_str());
    _service.sin_port = htons(port);

    _isOpen = true;
}

bool Connection::Close()
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