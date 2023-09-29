#include "TCPServer.h"


TCPConnectionAcceptor::TCPConnectionAcceptor(TCPServerController* _tcp_service_controller):
tcp_service_controller{_tcp_service_controller}
{}

TCPClientDBMgr::TCPClientDBMgr(TCPServerController* _tcp_service_controller):
tcp_service_controller{_tcp_service_controller}
{}

TCPClientServiceMgr::TCPClientServiceMgr(TCPServerController* _tcp_service_controller):
tcp_service_controller{_tcp_service_controller}
{}

TCPServerController::TCPServerController(const char* _ip, uint16_t _port_no, std::string _name):
ip_addr{network_convert_ip_p_to_n(_ip)},
port_no{_port_no},
name{_name}
{

    TCPConnectionAcceptor *TCA = new TCPConnectionAcceptor(this);
    TCPClientDBMgr *TCDB = new TCPClientDBMgr(this); 
    TCPClientServiceMgr *TCSM = new TCPClientServiceMgr(this);
}


void TCPServerController::start(){

}

void TCPServerController::stop(){

}