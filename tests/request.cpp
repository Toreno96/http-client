// Compile with:
// g++ ..\..\src\Message.cpp ..\..\src\Request.cpp request.cpp -std=c++14 -Wall -Wextra -Wshadow -Wpedantic -o request.exe

#include <iostream>
#include <string>
#include "../../src/Request.hpp"

int main() {
  Request request;
  request.setMethod( Request::Method::Get );
  request.setUri( "/path/to/file.html" );
  request.setHttpVersion( "HTTP/1.0" );
  std::cout << request.convertToString() << "|\n";

  request.setHeaderField( "Accept", "text/plain" );
  std::cout << request.convertToString() << "|\n";

  request.setHeaderField( "Accept-Charset", "cp1250" );
  request.setHeaderField( "Accept-Charset", "utf-8" );
  request.setHeaderField( "Accept-Encoding", "gzip, deflate" );
  std::cout << request.convertToString() << "|\n";

  request.setBody( "first line" );
  std::cout << request.convertToString() << "|\n";
  
  request.setBody( "first line\nsecond line\nthird line" );
  std::cout << request.convertToString() << "|\n";
}