//
// async_tcp_echo_server.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2008 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

#define BUFFER "HTTP/1.1 200 OK\r\nContent-Length: 5\r\nConnection: close\r\nContent-Type: text/html\r\n\r\nHello"
#define BUFFER_SIZE 87

using boost::asio::ip::tcp;

class Session
{
    public:
        Session(boost::asio::io_service& io_service)
            : socket_(io_service)
        {
        }

        tcp::socket& socket()
        {
            return socket_;
        }

        void Start()
        {
            socket_.async_read_some(boost::asio::buffer(data_, kMaxLength),
                    boost::bind(&Session::Read, this,
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
        }

        void Read(const boost::system::error_code& error,
                size_t bytes_transferred)
        {
            if (!error) {
                boost::asio::async_write(socket_,
                        boost::asio::buffer(BUFFER, BUFFER_SIZE),
                        boost::bind(&Session::Write, this,
                            boost::asio::placeholders::error));
            } else {
                delete this;
            }
        }

        void Write(const boost::system::error_code& error)
        {
            delete this;
        }

    private:
        tcp::socket socket_;
        enum { kMaxLength = 1024 };
        char data_[kMaxLength];
};

class Server
{
    public:
        Server(boost::asio::io_service& io_service, short port)
            : io_service_(io_service),
            acceptor_(io_service, tcp::endpoint(tcp::v4(), port))
    {
        Session* new_session = new Session(io_service_);
        acceptor_.async_accept(new_session->socket(),
                boost::bind(&Server::Accept, this, new_session,
                    boost::asio::placeholders::error));
    }

    void Accept(Session* new_session,
            const boost::system::error_code& error)
    {
        if (!error) {
            new_session->Start();
            new_session = new Session(io_service_);
            acceptor_.async_accept(new_session->socket(),
                    boost::bind(&Server::Accept, this, new_session,
                        boost::asio::placeholders::error));
        } else {
            delete new_session;
        }
    }

    private:
        boost::asio::io_service& io_service_;
        tcp::acceptor acceptor_;
};

int main(int argc, char* argv[])
{
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: async_tcp_echo_server <port>\n";
            return 1;
        }

        boost::asio::io_service io_service;

        using namespace std; // For atoi.
        Server s(io_service, atoi(argv[1]));

        io_service.run();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
