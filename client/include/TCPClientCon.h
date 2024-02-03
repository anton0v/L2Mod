#ifndef TCPCLIENTCON_H

#include "TCPConnection.h"

class TCPClientCon : public TCPConnection
{
public:
    TCPClientCon(const std::string& ip = "", const int port = 0);
    
    void Connect(const std::string& ip, const int port);
    bool Send(const char* buff) override;
    bool Recieve(char* buff, int size) override;
};

#endif