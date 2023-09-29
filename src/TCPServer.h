/*Copyright 2021 Shadai Rafael Lopez Garcia
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software
* and associated documentation files (the "Software"), to deal in the Software without restriction,
* including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
* subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all copies or substantial
* portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
* LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
* WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#ifndef TCPSERVERCONTROLLER_H
#define TCPSERVERCONTROLLER_H

#include <list>
#include "NetworkUtils.h"
#include <stdint.h> 
#include <string>
#include "TCPClient.h"

class TCPServerController;

class TCPConnectionAcceptor
{
private:
    TCPServerController* tcp_service_controller;
public:
    TCPConnectionAcceptor(TCPServerController* _tcp_service_controller);
    ~TCPConnectionAcceptor();
};

class TCPClientDBMgr
{
private:
    std::list<TCPClient*> tcp_client_db;
    TCPServerController* tcp_service_controller;
public:
    TCPClientDBMgr(TCPServerController* _tcp_service_controller);
    ~TCPClientDBMgr();
};

class TCPClientServiceMgr
{
private:
    TCPServerController* tcp_service_controller;
public:
    TCPClientServiceMgr(TCPServerController* _tcp_service_controller);
    ~TCPClientServiceMgr();
};

class TCPServerController{
private:
    TCPConnectionAcceptor *TCA;
    TCPClientDBMgr *TCDB;
    TCPClientServiceMgr *TCSM;
public:
    uint32_t ip_addr;
    uint16_t port_no;
    std::string name;

    TCPServerController(const char* _ip, uint16_t _port_no, std::string name);
    ~TCPServerController();
    void start();
    void stop();

};

#endif // TCPSERVERCONTROLLER_H
