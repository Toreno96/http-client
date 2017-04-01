#include <algorithm>
#include "Message.hpp"
#include "Constants.hpp"

bool Message::hasHeader( std::string headerName ) const {
  std::transform( headerName.begin(), headerName.end(), headerName.begin(), ::tolower );
  return headerFields_.find( headerName ) != headerFields_.end();
}
std::string Message::getHeaderValue( std::string headerName ) const {
  try {
    std::transform( headerName.begin(), headerName.end(), headerName.begin(), ::tolower );
    return headerFields_.at( headerName );
  }
  catch( const std::out_of_range& exception ) {
    // TO-DO
    // Zastąpić pochodną wyjątku std::out_of_range
    throw;
  }
}
void Message::setHeaderField( std::string name, const std::string& value ) {
  std::transform( name.begin(), name.end(), name.begin(), ::tolower );
  headerFields_[ name ] = value;
}

std::string Message::convertHeaderFieldsToString() const {
  std::string headerFieldsAsString;
  for( auto& headerField : headerFields_ )
    headerFieldsAsString += convertHeaderFieldToString( headerField ) + crlf;
  return headerFieldsAsString;
}
std::string Message::convertHeaderFieldToString(
    const std::pair< const std::string, std::string >& headerField ) const {
  return headerField.first + ": " + headerField.second;
}