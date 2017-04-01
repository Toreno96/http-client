#include <fstream>
#include <iostream>
#include "SFML/System.hpp"
#include "SFML/Network.hpp"
#include "Client.hpp"
#include "HtmlImagesExtractor.hpp"
#include "Response.hpp"
#include "Request.hpp"
#include "RudeUi.hpp"

int main() {
  std::string host = RudeUi::Read::FromUser::host();
  Client::tPort port = RudeUi::Read::FromUser::port();
  Client client( sf::IpAddress( host ), port );
  
  try {
    do {
      std::cout << '\n';
      try {
        Request request = RudeUi::Read::FromUser::request();
        
        std::cout << "\nAttempt to send request started...\n";
        Response response = client.sendRequest( request );

        std::cout << "\nReceived response:\n";
        RudeUi::Write::ToUser::responseWithoutBody( response );
        
        std::cout << '\n';
        if( response.getStatus().getStatusCode() == 200 ) {
          RudeUi::Write::ToFile::responseBody( client.getHost(), request, response );
          std::cout << "Download successful";
          if( response.getHeaderValue( "Content-Type" ) == "text/html" ) {
            std::cout << "\n\nDownloading additional images that this html is using...\n";
            HtmlImagesExtractor htmlImagesExtractor( response.getBody() );
            auto imagesToDownload = RudeUi::Helper::correctImagesRelativePaths(
                request.getUri(), htmlImagesExtractor.extractImages() );
            std::size_t imagesCount = imagesToDownload.size(),
                        imagesSuccessfullyDownloaded = imagesToDownload.size();
            for( auto& image : imagesToDownload ) {
              request.setUri( image );
              try{
                response = client.sendRequest( request );
              }
              catch( const std::logic_error& exception ) {
                --imagesSuccessfullyDownloaded;
              }
              if( response.getStatus().getStatusCode() == 200 )
                RudeUi::Write::ToFile::responseBody( client.getHost(), request, response );
              else
                --imagesSuccessfullyDownloaded;
            }
            std::cout << "Downloaded " << imagesSuccessfullyDownloaded
                      << '/' << imagesCount << " images successfully";
          }
        }
        else
          std::cout << "Download unsuccessful";
      }
      catch( const std::logic_error& exception ) {
        std::cerr << "Error: " << exception.what() << '\n';
      }
      std::cout << "\n\n";
    } while( RudeUi::Read::FromUser::doSendAnotherRequest() );
  }
  catch( const std::invalid_argument& exception ) {
    std::cerr << "Error: " << exception.what() << '\n'
              << "Exiting...\n";
  }
}