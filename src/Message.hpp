#pragma once

#include <string>
#include <map>

class Message {
  public:
    bool hasHeader( std::string headerName ) const;
    std::string getHeaderValue( std::string headerName ) const;
    void setHeaderField( std::string name, const std::string& value );
  protected:
    std::string convertHeaderFieldsToString() const;
    std::string convertHeaderFieldToString( const std::pair< const std::string, std::string >& headerField ) const;
    std::string httpVersion_;
    std::map< std::string, std::string > headerFields_;
    std::string body_;
};