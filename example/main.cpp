#include <iostream>
#include <cstdio> // std::sscanf
#include <boost/asio/io_service.hpp>
#include <awake/socket.hpp>

void done(const boost::system::error_code& error)
{
    std::cout << __FUNCTION__ << "(" << error << ")" << std::endl;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " <mac>" << std::endl;
        return 1;
    }
    boost::asio::io_service io;
    awake::udp::socket awaker(io);
    boost::array<unsigned int, 6> address;
    if (std::sscanf(argv[1], "%02x:%02x:%02x:%02x:%02x:%02x",
                    &address[0], &address[1], &address[2], &address[3], &address[4], &address[5]) == 6)
    {
        awaker.async_awake(address, done);
        io.run();
    }
    return 0;
}
