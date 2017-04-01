#include "HtmlImagesExtractor.hpp"

HtmlImagesExtractor::HtmlImagesExtractor( const std::string& htmlContent ) : htmlContent_( htmlContent ) {}
HtmlImagesExtractor::tImagesSet HtmlImagesExtractor::extractImages() const {
  tImgTagsSet imgTags = extractImgTags();
  tImagesSet images;
  for( const auto& imgTag : imgTags ) {
    std::smatch match;
    if( std::regex_search( imgTag, match, imageFilenameRegex_ ) ) {
      std::string image = trimQuotesFromImageFilename( match.str() );
      // if( *( image.begin() ) != '/' )
      //   image = '/' + image;
      images.insert( image );
    }
  }
  return images;
}
HtmlImagesExtractor::tImgTagsSet HtmlImagesExtractor::extractImgTags() const {
  tImgTagsSet imgTags;
  if( std::regex_search( htmlContent_, imgTagRegex_ ) ) {
    std::sregex_iterator regItBegin( htmlContent_.begin(), htmlContent_.end(),
        imgTagRegex_ );
    std::sregex_iterator regItEnd;
    for( auto regItNext = regItBegin; regItNext != regItEnd; ++regItNext )
      imgTags.insert( std::smatch( *regItNext ).str() );
  }
  return imgTags;
}
std::string HtmlImagesExtractor::trimQuotesFromImageFilename( std::string filename ) const {
  filename.erase( filename.begin() );
  filename.pop_back();
  return filename;
}

const std::regex HtmlImagesExtractor::imgTagRegex_( "<img.+?\\/>" );
const std::regex HtmlImagesExtractor::imageFilenameRegex_(
    "\"([A-Za-z0-9-._~#\\[\\]@!$&'()+,;=/]|%[0-9A-Fa-f]{2})+\\.([Jj][Pp][Gg]|[Pp][Nn][Gg]|[Gg][Ii][Ff])\"" );