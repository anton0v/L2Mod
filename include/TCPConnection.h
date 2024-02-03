#ifndef TCPCONNECTION_H

#include <stdexcept>
#ifdef _WIN32
#include <WinSock2.h>
typedef SOCKET SocketID;
#define INVALID_SOCKET_ID INVALID_SOCKET
#define NET_SOCKET_ERROR SOCKET_ERROR
#else
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
typedef int SocketID;
#define INVALID_SOCKET_ID (-1)
#define NET_SOCKET_ERROR (-1)
#endif
#include <string>
#include <cstring>

class TCPConError : public std::runtime_error 
{
public:
    TCPConError(const std::string & message);
};

class TCPConnection
{
protected:
    #ifdef _WIN32
    static int _sockCount;
    #endif
    SocketID _sock;
	std::string _ip;
    int _port;
	bool _isOpen;
    sockaddr_in _service;
public:
    TCPConnection(const std::string& ip = "", const int port = 0);
    ~TCPConnection();

    TCPConnection(const TCPConnection & other) = delete;
    TCPConnection & operator = (const TCPConnection & other) = delete;

    TCPConnection(TCPConnection && other) noexcept;
    TCPConnection & operator = (TCPConnection && other) noexcept;
    
    bool IsOpen() const { return _isOpen; }
    bool Close();
    virtual bool Send(const char* buff) = 0;
    virtual bool Recieve(char* buff, int size) = 0;
};

#endif