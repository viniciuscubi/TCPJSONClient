#include "../include/client.hpp"

Client::Client(const std::string addr){
    ip = addr;
    this->socket.connect(ip);
}

Client::~Client(){
    this->socket.disconnect(ip);
}

int Client::send(std::string message){
    this->socket.send(zmq::buffer(message), zmq::send_flags::none);
    return 0;
}

std::string Client::receive(){
    zmq::message_t request;
    this->socket.recv(request, zmq::recv_flags::none);
    return request.to_string();
}


int Client::sendByte(bool message){
    std::string msg;

    if(message){
        msg = "1";
    }else{
        msg = "0";
    }

    this->socket.send(zmq::buffer(msg), zmq::send_flags::none);
    return 0;
}