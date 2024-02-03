#ifndef TCPSERVERCON_H

#include "TCPConnection.h"

class TCPServerCon : public TCPConnection
{
private:
    bool _hasClient;
    SocketID _clientSock;
public:
    TCPServerCon(const std::string& ip = "", const int port = 0);

    bool Send(const char* buff) override { return false;}
    bool Recieve(char* buff, int size) override;
    
    void Bind(const std::string& ip, const int port);
    void Accept();
};

#endif