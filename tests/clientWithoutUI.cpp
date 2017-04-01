#include <fstream>
#include <iostream>
#include "SFML/System.hpp"
#include "SFML/Network.hpp"
#include "Client.hpp"
#include "Response.hpp"
#include "Request.hpp"

int main() {
  Client httpClient( sf::IpAddress( "127.0.0.1" ), 81 );
  Request request;
  request.setMethod( Request::Method::Get );
  request.setUri( "/logo.png" );
  request.setHttpVersion( "HTTP/1.0" );
  //request.setHeaderField( "host", "www.sfml-dev.org" );
  Response response = httpClient.sendRequest( request );
  std::cout << response.getHttpVersion() << ' '
            << response.getStatus().getStatusCode()
            << ' ' << response.getStatus().getReasonPhrase() << "|\n";
  std::vector< std::string > headerFields = response.getAllHeaderFields();
  for( auto& headerField : headerFields )
    std::cout << headerField << '\n';
  // std::cout << response.getBody() << "|\n";
  std::cout << "body size: " << response.getBody().size() << "|\n";
  std::ofstream file( "logo.png", std::ios::binary );
  if ( file.is_open() ) {
    std::string body = response.getBody();
    file.write( body.c_str(), body.size() );
  }
}