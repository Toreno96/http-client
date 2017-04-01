#include "Request.hpp"
#include "Constants.hpp"

Request::Method Request::getMethod() const {
  return method_;
}
std::string Request::getUri() const {
  return uri_;
}
void Request::setMethod( const Method& method ) {
  method_ = method;
}
void Request::setUri( const std::string& uri ) {
  uri_ = uri;
}
void Request::setHttpVersion( const std::string& httpVersion ) {
  httpVersion_ = httpVersion;
}
void Request::setBody( const std::string& body ) {
  body_ = body;
}

std::string Request::convertToString() const {
  std::string requestAsString = convertFirstLineToString() +
                                convertHeaderFieldsToString() +
                                crlf +
                                body_;
  return requestAsString;
}
std::string Request::convertFirstLineToString() const {
  return convertMethodToString() + ' ' + uri_ + ' ' + httpVersion_ + crlf;
}
std::string Request::convertMethodToString() const {
  std::string methodAsString;
  switch( method_ ) {
    case Method::Get:
      methodAsString = "GET";
      break;
    case Method::Post:
      methodAsString = "POST";
      break;
  }
  return methodAsString;
}