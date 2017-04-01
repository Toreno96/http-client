#include "Client.hpp"
#include "HtmlImagesExtractor.hpp"
#include "Request.hpp"
#include "Response.hpp"

namespace RudeUi {

namespace Enum {

enum class NextOperation { SendAnotherRequest, Exit };

} // namespace Enum

namespace Read {

namespace FromUser {

Request request();
std::string host();
Client::tPort port();
Request::Method method();
std::string uri();
std::string httpVersion();
void headerFields( Request& request );
bool headerField( Request& request );
std::string filenameContainingBody();
bool doSendAnotherRequest();

} // namespace FromUser

namespace FromFile {

std::string body( const std::string& filename );

} // namespace FromFile

} // namespace Read

namespace Write {

namespace ToUser {

void responseWithoutBody( const Response& response );

} // namespace ToUser

namespace ToFile {

void responseBody( const sf::IpAddress& hostIpAddress, const Request& request,
                   const Response& response );
void text( const std::string& filename, const std::string& data );
void binary( const std::string& filename, const std::string& data );

} // namespace ToFile

} // namespace Write

namespace Helper {

bool isContentTypeText( const std::string& contentTypeHeaderValue );
std::string determineDownloadDirectory( const sf::IpAddress& hostIpAddress,
                                        const Request& request );
void createRequiredDirectories( const std::string& filepath );
HtmlImagesExtractor::tImagesSet correctImagesRelativePaths(
    const std::string& htmlUri,
    HtmlImagesExtractor::tImagesSet images );

} // namespace Helper

} // namespace RudeUi