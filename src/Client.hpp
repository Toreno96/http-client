#pragma once

#include <string>
#include "SFML/System.hpp"
#include "SFML/Network.hpp"
#include "Request.hpp"
#include "Response.hpp"

class Client {
  public:
    typedef int tPort;
    Client() = delete;
    Client( const sf::IpAddress& host, const tPort port = 80 );
    sf::IpAddress getHost() const;
    tPort getPort() const;
    Response sendRequest( const Request& request );
  private:
    sf::IpAddress host_;
    tPort port_;
};