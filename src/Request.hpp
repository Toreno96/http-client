#pragma once

#include <string>
#include "Message.hpp"

class Request : public Message {
  public:
    enum class Method { Get, Post };
    Request::Method getMethod() const;
    std::string getUri() const;
    void setMethod( const Method& method );
    void setUri( const std::string& uri );
    void setHttpVersion( const std::string& httpVersion );
    void setBody( const std::string& body );
    std::string convertToString() const;
  private:
    std::string convertFirstLineToString() const;
    std::string convertMethodToString() const;
    Method method_;
    std::string uri_;
};