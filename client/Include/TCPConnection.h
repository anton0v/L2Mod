#ifndef CONNECTION_H

#include <stdexcept>
#include <WinSock2.h>
#include <string>

class TCPConnection
{
private:
    static int _sockCount;
    static void InitWSA();
    static void CloseWSA();
    SOCKET _sock;
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
    void Connect(const std::string& ip, const int port);
    bool Send(const char* buff);
    bool Recieve(char* buff, int size);
};

#endif