#ifndef TCPSERVERCON_H

#include <stdexcept>
#ifdef _WIN32
#include <WinSock2.h>
typedef SOCKET SocketID;
#define INVALID_SOCKET_ID INVALID_SOCKET
#define NET_SOCKET_ERROR SOCKET_ERROR
#else
//#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
//#include <fcntl.h>
//#include <netdb.h>
//#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
typedef int SocketID;
#define INVALID_SOCKET_ID (-1)
#define NET_SOCKET_ERROR (-1)
#endif

#include <string>

class TCPServerCon 
{
private:
#ifdef _WIN32
    static int _sockCount;
    static void InitWSA();
    static void CloseWSA();
#endif
    sockaddr_in _service;
    SocketID _sock;
	std::string _ip;
    int _port;
	bool _isOpen;
    bool _hasClient;
    SocketID _clientSock;
public:
    TCPServerCon(const std::string& ip = "", const int port = 0);
    ~TCPServerCon();
    
    TCPServerCon(const TCPServerCon & other) = delete;
    TCPServerCon & operator = (const TCPServerCon & other) = delete;

    TCPServerCon(TCPServerCon && other) noexcept;
    TCPServerCon & operator = (TCPServerCon && other) noexcept;
    
    bool IsOpen() const { return _isOpen; }
    bool Close();
    void Send(const char* buff) const;
    bool Recieve(char* buff, int size);
    
    void Bind(const std::string& ip, const int port);
    void Accept();
};

#endif