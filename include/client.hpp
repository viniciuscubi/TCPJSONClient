#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <zmq.hpp>

class Client{

    private:
        std::string ip;
        zmq::context_t context{1}; // initialize the zmq context with a single IO thread
        zmq::socket_t socket{context, zmq::socket_type::req}; // construct a REQ (request) socket and connect to interface

    public:
        Client(const std::string addr);
        ~Client();

        int send(std::string message);
        std::string receive();
        int sendByte(bool message);

};

#endif