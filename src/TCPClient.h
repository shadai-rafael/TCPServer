/*Copyright 2023 Shadai Rafael Lopez Garcia
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
#ifndef _TCP_CLIENT_
#define _TCP_CLIENT_

#include <stdint.h>

class TCPServerController;

class TCPClient {
    private:
    public:
        uint32_t ip_addr;
        uint16_t port_no;
        uint32_t server_ip_addr;
        uint16_t server_port_no;
        int comm_fd;
        TCPServerController *tCPServerController;
        TCPClient(uint32_t _ip_addr, uint16_t _port_no);
        ~TCPClient();
};

 #endif //_TCP_CLIENT_