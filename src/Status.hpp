#pragma once

#include <string>

class Status {
  public:
    typedef int tStatusCode;
    Status(); // Required by Response ctor
    Status( const tStatusCode statusCode, const std::string& reasonPhrase );
    tStatusCode getStatusCode() const;
    std::string getReasonPhrase() const;
  private:
    tStatusCode statusCode_;
    std::string reasonPhrase_;
};