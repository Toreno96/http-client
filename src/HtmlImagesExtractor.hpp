#pragma once

#include <regex>
#include <set>
#include <string>

// Class for extracting images' filenames (with relative paths) from html
// files. It's not very advanced, because it can only extract images placed via
// <img> tag. It assumes, that URLs used by given html file are URL-encoded.
class HtmlImagesExtractor {
  public:
    typedef std::set< std::string > tImagesSet;
    HtmlImagesExtractor() = delete;
    HtmlImagesExtractor( const std::string& htmlContent );
    tImagesSet extractImages() const;
  private:
    typedef std::set< std::string > tImgTagsSet;
    tImgTagsSet extractImgTags() const;
    std::string trimQuotesFromImageFilename( std::string filename ) const;
    const static std::regex imgTagRegex_;
    const static std::regex imageFilenameRegex_;
    std::string htmlContent_;
};