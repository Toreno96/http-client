#pragma once

#include <sstream>
#include <string>
#include <vector>
#include "Message.hpp"
#include "Status.hpp"

class Response : private Message {
  public:
    Response( const std::string& receivedData );
    std::string getHttpVersion() const;
    Status getStatus() const;
    std::string getBody() const;
    std::vector< std::string > getAllHeaderFields() const;
    using Message::hasHeader;
    using Message::getHeaderValue;
  private:
    void parseReceivedData( std::string receivedData );
    void parseStatusLine( std::istringstream& receivedDataStream );
    void parseHeaderFields( std::istringstream& receivedDataStream );
    void parseHeaderField( const std::string& headerField );
    void parseBody( std::istringstream& receivedDataStream );
    Status status_;
};