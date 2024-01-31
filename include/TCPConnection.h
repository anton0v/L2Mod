#ifndef TCPCONNECTION_H

#include "Connection.h"

class TCPConnection : public Connection
{
public:
    TCPConnection(const std::string& ip = "", const int port = 0) :
        Connection(ip, port) {}
    void Send(const char* buff) const override;
    void Recieve(char* buff, int size) override;
};

#endif