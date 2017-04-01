// Compile with:
// g++ ..\..\src\Message.cpp ..\..\src\Status.cpp ..\..\src\Response.cpp response.cpp -std=c++14 -Wall -Wextra -Wshadow -Wpedantic -o response.exe

#include <iostream>
#include <string>
#include "../../src/Response.hpp"

int main() {
  std::string receivedStr = "HTTP/1.0 418 I'm a teapot\r\n"
                            //"Accept: text/plain\r\n"
                            //"Accept-Charset: utf-8\r\n"
                            //"Accept-Encoding: gzip, deflate\r\n"
                            "\r\n";
                            //"first line\nsecond line\nthird line";
  Response response( receivedStr );
  std::cout << response.getHttpVersion() << "|\n";
  std::cout << response.getStatus().getStatusCode() << "|\n";
  std::cout << response.getStatus().getReasonPhrase() << "|\n";
  // std::cout << response.getHeaderValue( "Accept" ) << "|\n";
  // std::cout << response.getHeaderValue( "accept" ) << "|\n";
  // std::cout << response.getHeaderValue( "Accept-Charset" ) << "|\n";
  // std::cout << response.getHeaderValue( "accept-charset" ) << "|\n";
  // std::cout << response.getHeaderValue( "Accept-Encoding" ) << "|\n";
  // std::cout << response.getHeaderValue( "accept-encoding" ) << "|\n";
  if( response.hasHeader( "non-existent-header" ) )
    std::cout << response.getHeaderValue( "non-existent-header" ) << "|\n";
  std::cout << response.getBody() << "|\n";
}