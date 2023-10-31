#include "TCPServer.h"
#include <iostream>
#include <unistd.h>

int main(int argc, char* argv[])
{
    std::cout<< argc << std::endl;
    if (argc != 3) {
        std::cerr << "Usage: <IP Address> <Port Number>\n";
        return 1;
    }

    int port = atoi(argv[2]);

    TCPServerController server(argv[1], port,"server");
    server.start();
    while (true)
    {
        sleep(60);
    }
    
}