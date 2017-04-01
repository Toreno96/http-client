#include "Status.hpp"

Status::Status() : Status( tStatusCode(), std::string() ) {}
Status::Status( const tStatusCode statusCode, const std::string& reasonPhrase ) :
    statusCode_( statusCode ), reasonPhrase_( reasonPhrase ) {}

Status::tStatusCode Status::getStatusCode() const {
  return statusCode_;
}
std::string Status::getReasonPhrase() const {
  return reasonPhrase_;
}