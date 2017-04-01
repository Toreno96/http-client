#include <array>
#include "Client.hpp"

Client::Client( const sf::IpAddress& host, const tPort port ) : host_( host ), port_( port ) {}
sf::IpAddress Client::getHost() const {
  return host_;
}
Client::tPort Client::getPort() const {
  return port_;
}
Response Client::sendRequest( const Request& request ) {
  std::string requestAsString = request.convertToString();
  sf::TcpSocket tcpSocket;
  if( tcpSocket.connect( host_, port_ ) == sf::TcpSocket::Status::Done ) {
    if( tcpSocket.send( requestAsString.data(), requestAsString.size() ) == sf::TcpSocket::Status::Done ) {
      const std::size_t bufferSize = 1024;
      char buffer[ bufferSize ];
      std::size_t receivedBytes = 0;
      std::string receivedString;
      while( tcpSocket.receive( buffer, bufferSize, receivedBytes ) == sf::TcpSocket::Status::Done )
        receivedString.append( buffer, receivedBytes );
      tcpSocket.disconnect();
      return Response( receivedString );
    }
    else {
      tcpSocket.disconnect();
      // TO-DO
      // Potencjalna pochodna wyjątku std::logic_error
      // Nazwa: sendingRequestUnsuccessful?
      throw std::logic_error( "Client was not able to send request successfully" );
    }
  }
  else {
    // TO-DO
    // Potencjalna pochodna wyjątku std::logic_error
    // Nazwa: connecting[Tcp]SocketUnsuccessful?
    throw std::logic_error( "Client was not able to connect socket successfully" );
  }
}