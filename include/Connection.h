#ifndef CONNECTION_H

#include <stdexcept>
#include <WinSock2.h>
#include <string>

class Connection
{
private:
    static int _sockCount;
    static void InitWSA();
    static void CloseWSA();
protected:
    SOCKET _sock;
	std::string _ip;
    int _port;
	bool _isOpen;
    sockaddr_in _service;
public:
    Connection(const std::string& ip = "", const int port = 0);
    ~Connection();

    Connection(const Connection & other) = delete;
    Connection & operator = (const Connection & other) = delete;

    Connection(Connection && other) noexcept;
    Connection & operator = (Connection && other) noexcept;
    
    bool IsOpen() const { return _isOpen; }
    bool Close();
    void Connect(const std::string& ip, const int port);
    virtual void Send(const char* buff) const = 0;
    virtual void Recieve(char* buff, int size) = 0;
};

#endif