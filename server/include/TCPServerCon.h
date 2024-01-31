#ifndef TCPSERVERCON_H

#include <stdexcept>
#include <WinSock2.h>
#include <string>

class TCPServerCon 
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
    bool _hasClient;
    SOCKET _clientSock;
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
    void Recieve(char* buff, int size);
    
    void Bind(const std::string& ip, const int port);
    void Accept();
};

#endif