#include "TCPServer.h"

#include<unistd.h>
#include<cassert>

//*********

TCPConnectionAcceptor::TCPConnectionAcceptor(TCPServerController* _tcp_service_controller):
tcp_service_controller{_tcp_service_controller}
{
    server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    connection_thread = NULL;
    
    if (server_fd < 0) {
        std::cerr << "Error : Could not create Accept FD\n";
        exit(1);
    }

    connection_thread = (pthread_t *)calloc(1,sizeof(pthread_t));
    if(!connection_thread){
        std::cerr<<"Thread allocation failed."<<std::endl;
        exit(1);
    }

    std::cout<<"Connection Acceptor initialized"<<std::endl;
}

TCPConnectionAcceptor::~TCPConnectionAcceptor(){

}

void TCPConnectionAcceptor::connection_acceptor_thread_internal(){
    int opt = 1;
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(this->tcp_service_controller->port_no);
    server_addr.sin_addr.s_addr = htonl(this->tcp_service_controller->ip_addr);

    //This option allows multiple sockets to bind to the same address and port combination.
    //It allows a new instance of the server to bind to the same address and port while the
    //previous instance might still be closing its connections.
    if (setsockopt(this->server_fd, SOL_SOCKET,
                   SO_REUSEADDR, (char*) &opt, sizeof(opt))<0) {
        std::cerr<<"setsockopt Failed at configuting the address errno: "<< errno <<std::endl;
        exit(1);
    }

    //This option allows multiple sockets to bind to the same address and port combination. 
    //It's used when you want to build a high-performance server that can handle many incoming
    //connections simultaneously and distribute the load across multiple processes or threads
    if (setsockopt(this->server_fd, SOL_SOCKET,
                   SO_REUSEPORT, (char*)&opt, sizeof(opt))<0) {
        std::cerr<<"setsockopt Failed at configuting the address errno: "<< errno <<std::endl;
        exit(1);
    }

    if (bind(this->server_fd, (struct sockaddr *)&server_addr,
                sizeof(struct sockaddr)) == -1) {
        std::cerr<<"Acceptor socket bind failed "<<std::endl;
        exit(1);
    }

    //FD accept connection on file descriptor
    //N maximum number of conections queued
    if (listen(this->server_fd, 5) < 0 ) {
        std::cout<<"Listen failed"<<std::endl;
        exit(1);
    }

    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);
    int comm_socket_fd;

    while (true) {
        comm_socket_fd =  accept (this->server_fd,
                            (struct sockaddr *)&client_addr, &addr_len);

        if (comm_socket_fd < 0) {
            std::cout<<"Error in Accepting New Connections"<<std::endl;
            continue;
        }

        TCPClient *tCPClient = new TCPClient(client_addr.sin_addr.s_addr, client_addr.sin_port);
        tCPClient->tCPServerController = this->tcp_service_controller;
        tCPClient->comm_fd = comm_socket_fd;
        this->tcp_service_controller->process_new_client(tCPClient);
        std::cout<<"Connection accepted"<<std::endl;
    }
}

static void * tcp_listener(void *arg){
    TCPConnectionAcceptor* tca = static_cast<TCPConnectionAcceptor*>(arg);
    tca->connection_acceptor_thread_internal();
    return NULL;
}

void TCPConnectionAcceptor::start_connection_acceptor_thread()
{
    if(pthread_create(connection_thread, NULL, tcp_listener, static_cast<void*>(this))){
        std::cerr<<"Error while creating a thread"<<std::endl;
        exit(1);
    }
    std::cout<<"Connection acceptor started"<<std::endl;
}

//*********TCPClientDBMgr*********

TCPClientDBMgr::TCPClientDBMgr(TCPServerController* _tcp_service_controller):
tcp_service_controller{_tcp_service_controller}
{}

TCPClientDBMgr::~TCPClientDBMgr()
{}

void TCPClientDBMgr::start_client_db_mgr_init()
{}

void TCPClientDBMgr::add_client_to_db(TCPClient *client)
{
    this->db.push_back(client);
}

//*********TCPClientServiceMgr*********

TCPClientServiceMgr::TCPClientServiceMgr(TCPServerController* _tcp_service_controller):
tcp_service_controller{_tcp_service_controller}
{}

TCPClientServiceMgr::~TCPClientServiceMgr()
{}

void TCPClientServiceMgr::start_client_service_mgr_thread()
{}

void TCPClientServiceMgr::start_listening_client_fd(TCPClient *client)
{

}

//*********TCPServerController*********

TCPServerController::TCPServerController(const char* _ip, uint16_t _port_no, std::string _name):
ip_addr{network_convert_ip_p_to_n(_ip)}, port_no{_port_no}, name{_name},
TCA{new TCPConnectionAcceptor(this)}, TCDB {new TCPClientDBMgr(this)}, TCSM{new TCPClientServiceMgr(this)}
{}


void TCPServerController::process_new_client(TCPClient *client){
    this->TCDB->add_client_to_db(client);
    this->TCSM->start_listening_client_fd(client);
}

TCPServerController::~TCPServerController(){
    delete(TCA);
    delete(TCDB);
    delete(TCSM);
}

void TCPServerController::start(){
    assert(this->TCA);
    //start_connection_acceptor_thread()->tcp_listener()->connectionAcceptorThreadInterna()
    TCA->start_connection_acceptor_thread();
    //this->TCDB->start_client_db_mgr_init();
    //this->TCSM->start_client_service_mgr_thread();
}

void TCPServerController::stop(){

}