#include "TCPServer.h"

#include<unistd.h>
#include<cassert>

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

void TCPConnectionAcceptor::connectionAcceptorThreadInternal(){
    int opt = 1;
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(this->tcp_service_controller->port_no);
    server_addr.sin_addr.s_addr = htonl(this->tcp_service_controller->ip_addr);

    if (setsockopt(this->server_fd, SOL_SOCKET,
                   SO_REUSEADDR, (char*) &opt, sizeof(opt))<0) {
        std::cerr<<"setsockopt Failed at configuting the address errno: "<< errno <<std::endl;
        exit(1);
    }

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
        std::cout<<"Connection accepted"<<std::endl;
    }
}

static void * tcp_listener(void *arg){
    TCPConnectionAcceptor* tca = static_cast<TCPConnectionAcceptor*>(arg);
    tca->connectionAcceptorThreadInternal();
    return NULL;
}

void TCPConnectionAcceptor::startConnectionAcceptorThread()
{
    if(pthread_create(connection_thread, NULL, tcp_listener, static_cast<void*>(this))){
        std::cerr<<"Error while creating a thread"<<std::endl;
        exit(1);
    }
    std::cout<<"Connection acceptor started"<<std::endl;
}

TCPClientDBMgr::TCPClientDBMgr(TCPServerController* _tcp_service_controller):
tcp_service_controller{_tcp_service_controller}
{}

TCPClientDBMgr::~TCPClientDBMgr(){

}

void TCPClientDBMgr::startClientDBMgrInit(){
    
}

TCPClientServiceMgr::TCPClientServiceMgr(TCPServerController* _tcp_service_controller):
tcp_service_controller{_tcp_service_controller}
{}

TCPClientServiceMgr::~TCPClientServiceMgr()
{}

void TCPClientServiceMgr::startClientServiceMgrThread(){

}

TCPServerController::TCPServerController(const char* _ip, uint16_t _port_no, std::string _name):
ip_addr{network_convert_ip_p_to_n(_ip)},
port_no{_port_no},
name{_name}
{

    TCA = new TCPConnectionAcceptor(this);
    //TCPClientDBMgr *TCDB = new TCPClientDBMgr(this); 
    //TCPClientServiceMgr *TCSM = new TCPClientServiceMgr(this);
}

TCPServerController::~TCPServerController(){
    delete(TCA);
    //delete(TCDB);
    //delete(TCSM);
}

void TCPServerController::start(){
    assert(this->TCA);
    //assert(this->TCSM);
    //assert(this->TCDB);
    TCA->startConnectionAcceptorThread();
    //this->TCDB->startClientDBMgrInit();
    //this->TCSM->startClientServiceMgrThread();
}

void TCPServerController::stop(){

}