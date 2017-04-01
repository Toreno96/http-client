#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include "boost/filesystem.hpp"
#include "RudeUi.hpp"

namespace RudeUi {

namespace Read {

namespace FromUser {

Request request() {
  Request request;
  //request.setMethod( RudeUi::Read::FromUser::method() );
  request.setMethod( Request::Method::Get );
  request.setUri( RudeUi::Read::FromUser::uri() );
  //request.setHttpVersion( RudeUi::Read::FromUser::httpVersion() );
  request.setHttpVersion( "HTTP/1.0" );
  RudeUi::Read::FromUser::headerFields( request );
  if( !( request.hasHeader( "User-Agent" ) ) )
    request.setHeaderField( "User-Agent", "HTTP Client by Daniel S." );
  if( request.getMethod() == Request::Method::Post ) {
  // TO-DO ////////////////////////////////////////////////////////////////////
    std::string filename = RudeUi::Read::FromUser::filenameContainingBody();
    // zapytanie o to, czy jest to plik binarny czy tekstowy? TO-DO
    std::string body = RudeUi::Read::FromFile::body( filename );
    request.setBody( body );
  /////////////////////////////////////////////////////////////////////////////
  }
  return request;
}
std::string host() {
  std::cout << "Enter host name (ex. \"www.example.com\") or IP address (ex. \"255.255.255.255\"):\n"
            << "> ";
  std::string host;
  std::cin >> host;
  return host;
}
Client::tPort port() {
  std::cout << "Enter port:\n"
            << "> ";
  int port;
  std::cin >> port;
  return port;
}
Request::Method method() {
  std::cout << "Choose method:\n"
            << "1. GET\n"
            << "2. POST\n"
            << "> ";
  int choice;
  std::cin >> choice;
  switch( choice ) {
    case 1:
      return Request::Method::Get;
    case 2:
      return Request::Method::Post;
    default:
      throw std::invalid_argument( "Invalid choice" );
  }
}
std::string uri() {
  std::cout << "Enter URI (ex. \"/images/logo.png\"):\n"
            << "> ";
  std::string uri;
  std::cin >> uri;
  return uri;
}
std::string httpVersion() {
  const std::string onePointZero = "HTTP/1.0";
  std::cout << "Choose HTTP version:\n"
            << "1. " + onePointZero + "\n"
            << "> ";
  int choice;
  std::cin >> choice;
  switch( choice ) {
    case 1:
      return onePointZero;
    default:
      throw std::invalid_argument( "Invalid choice" );
  }
}
void headerFields( Request& request ) {
  std::cout << "Enter header field (ex. \"Accept: text/html\"; \"end\" stops entering):\n";
  std::cin.ignore( std::numeric_limits< std::streamsize >::max(), '\n' );
  while( headerField( request ) );
}
bool headerField( Request& request ) {
  std::string headerField;
  std::cout << "> ";
  std::getline( std::cin, headerField );
  if( headerField != "end" ) {
    std::istringstream headerFieldStream( headerField );
    std::string headerName, headerValueFirstPart, headerValueSecondPart;
    headerFieldStream >> headerName;
    headerName.pop_back(); // Remove trailing colon character
    headerFieldStream >> headerValueFirstPart;
    std::getline( headerFieldStream, headerValueSecondPart );
    request.setHeaderField( headerName, headerValueFirstPart + headerValueSecondPart );
    return true;
  }
  else
    return false;
}
std::string filenameContainingBody() {
  std::cout << "Enter name of file with message body:\n"
            << "> ";
  std::string filename;
  std::getline( std::cin, filename );
  return filename;
}
bool doSendAnotherRequest() {
  std::cout << "Choose, if you want to send another request:\n"
            << "1. Yes\n"
            << "2. No\n"
            << "> ";
  int choice;
  std::cin >> choice;
  switch( choice ) {
    case 1:
      return true;
    case 2:
      return false;
    default:
      throw std::invalid_argument( "Invalid choice" );
  }
}

} // namespace FromUser

namespace FromFile {

std::string body( const std::string& filename ) {
  throw std::runtime_error( "Not implemented yet" );
  std::ifstream file( filename, std::ios::binary );
  if( file.is_open() ) {}
}

} // namespace FromFile

} // namespace Read

namespace Write {

namespace ToUser {

void responseWithoutBody( const Response& response ) {
  std::cout << response.getHttpVersion() << ' '
            << response.getStatus().getStatusCode() << ' '
            << response.getStatus().getReasonPhrase() << '\n';
  for( auto& headerField : response.getAllHeaderFields() )
    std::cout << headerField << '\n';
}

} // namespace ToUser

namespace ToFile {

void responseBody( const sf::IpAddress& hostIpAddress, const Request& request,
                   const Response& response ) {
  std::string downloadPath = Helper::determineDownloadDirectory( hostIpAddress, request );
  std::string uri = request.getUri();
  if( uri == "/" )
    uri += "index.html";
  downloadPath += uri;
  Helper::createRequiredDirectories( downloadPath );
  if( Helper::isContentTypeText( response.getHeaderValue( "Content-Type" ) ) )
    text( downloadPath, response.getBody() );
  else
    binary( downloadPath, response.getBody() );
}
void text( const std::string& filename, const std::string& data ) {
  std::ofstream file( filename );
  if( file.is_open() )
    file << data;
}
void binary( const std::string& filename, const std::string& data ) {
  std::ofstream file( filename, std::ios::binary );
  if( file.is_open() ) {
    std::istringstream dataStream( data );
    file << dataStream.rdbuf();
  }
}

} // namespace ToFile

} // namespace Write

namespace Helper {

bool isContentTypeText( const std::string& contentTypeHeaderValue ) {
  auto slashPosition = contentTypeHeaderValue.find( '/' );
  if( slashPosition != std::string::npos ) {
    if( contentTypeHeaderValue.substr( 0, slashPosition ) == "text" )
      return true;
    else
      return false;
  }
  else
    throw std::invalid_argument( "Invalid value of Content-Type header" );
}
std::string determineDownloadDirectory( const sf::IpAddress& hostIpAddress,
                                        const Request& request ) {
  std::string downloadDirectory = "downloads/" + hostIpAddress.toString();
  if( request.hasHeader( "Host" ) )
    downloadDirectory += '/' + request.getHeaderValue( "Host" );
  return downloadDirectory;
}
void createRequiredDirectories( const std::string& filepath ) {
  boost::filesystem::path directoriesToCreate(
      boost::filesystem::path( filepath ).parent_path() );
  if( !( directoriesToCreate.string().empty() ) )
    boost::filesystem::create_directories( directoriesToCreate );
}
HtmlImagesExtractor::tImagesSet correctImagesRelativePaths(
    const std::string& htmlUri,
    HtmlImagesExtractor::tImagesSet images ) {
  std::string missingPathFragment;
  if( htmlUri != "/" )
    missingPathFragment = boost::filesystem::path( htmlUri ).parent_path().string();
  if( missingPathFragment != "/" )
    missingPathFragment += '/';
  for( auto itNext = images.begin(), itEnd = images.end(); itNext != itEnd; ) {
    if( *( ( *itNext ).begin() ) != '/' ) {
      std::string imageWithCorrectedPath = missingPathFragment + *( itNext );
      itNext = images.erase( itNext );
      images.insert( imageWithCorrectedPath );
    }
    else
      ++itNext;
  }
  return images;
}

} // namespace Helper

} // namespace RudeUi