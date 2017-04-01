#include <algorithm>
#include "Response.hpp"
#include "Constants.hpp"

// Everywhere below, if not mentioned otherwise, std::istringstream::get method
// is used to remove trailing line feed character

// Parsing reason phrase and header value are divided into two steps, because
// of the whitespaces following them.
//
// After parsing, I could have made and use special function to trim such
// whitespaces, but I decided that faster and probably more efficient solution
// will be to take them into account immediately during parsing via
// std::istringstream

Response::Response( const std::string& receivedData ) {
  if( receivedData.empty() ) {
    throw std::invalid_argument( "Response::Response( const std::string& ) "
                                 "cannot be called with the argument being an "
                                 "empty string" );
  }
  parseReceivedData( receivedData );
}

std::string Response::getHttpVersion() const {
  return httpVersion_;
}
Status Response::getStatus() const {
  return status_;
}
std::vector< std::string > Response::getAllHeaderFields() const {
  std::vector< std::string > headerFields;
  for( auto& headerField : headerFields_ )
    headerFields.push_back( convertHeaderFieldToString( headerField ) );
  return headerFields;
}
std::string Response::getBody() const {
  return body_;
}

void Response::parseReceivedData( std::string receivedData ) {
  std::istringstream receivedDataStream( receivedData );
  parseStatusLine( receivedDataStream );
  parseHeaderFields( receivedDataStream );
  parseBody( receivedDataStream );
}
void Response::parseStatusLine( std::istringstream& receivedDataStream ) {
  receivedDataStream >> httpVersion_;
  std::string statusCode, reasonPhraseFirstPart, reasonPhraseSecondPart;
  receivedDataStream >> statusCode;
  receivedDataStream >> reasonPhraseFirstPart;
  getline( receivedDataStream, reasonPhraseSecondPart, cr );
  status_ = Status( std::stoi( statusCode ), reasonPhraseFirstPart + reasonPhraseSecondPart );
  receivedDataStream.get();
}
void Response::parseHeaderFields( std::istringstream& receivedDataStream ) {
  std::string line;
  while( std::getline( receivedDataStream, line, cr ) && !( line.empty() ) ) {
    parseHeaderField( line );
    receivedDataStream.get();
  }
  // Once again, because loop above doesn't handle trailing line feed
  // character from the last, empty line
  receivedDataStream.get();
}
void Response::parseHeaderField( const std::string& headerField ) {
  std::istringstream lineStream( headerField );
  std::string name, valueFirstPart, valueSecondPart;
  lineStream >> name;
  // Remove trailing colon
  name.pop_back();
  lineStream >> valueFirstPart;
  getline( lineStream, valueSecondPart );
  setHeaderField( name, valueFirstPart + valueSecondPart );
}
void Response::parseBody( std::istringstream& receivedDataStream ) {
  body_ = std::string( std::istreambuf_iterator< char >( receivedDataStream ),
                       std::istreambuf_iterator< char >() );
}