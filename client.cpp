#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <IP Address> <Port Number>\n";
        return 1;
    }

    const char* ip_address = argv[1];
    int port_number = std::stoi(argv[2]);

    // Create a socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Socket creation failed");
        return 1;
    }

    // Set up server address
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port_number);
    if (inet_pton(AF_INET, ip_address, &server_address.sin_addr) <= 0) {
        perror("Invalid IP Address");
        close(client_socket);
        return 1;
    }

    // Connect to the server
    if (connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        perror("Connection failed");
        close(client_socket);
        return 1;
    }

    std::cout << "Connected to " << ip_address << ":" << port_number << std::endl;

    // You can now send and receive data through client_socket

    // Close the socket when done
    close(client_socket);

    return 0;
}

