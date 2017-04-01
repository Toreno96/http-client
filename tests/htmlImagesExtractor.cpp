#include <iostream>
#include <string>
#include "../../src/HtmlImagesExtractor.hpp"

int main() {
  const std::string htmlContent(
      "<img src=\"image1.jpg\" alt=\"alternative text1\" /> "
      "<img src=\"image2.png\" alt=\"alternative text2\" /> "
      "<img src=\"image2.png\" alt=\"alternative text2\" /> "
      "<img src=\"image3.gif\" alt=\"alternative text3\" />\n"
      "<img src=\"image4.png\" alt=\"alternative text2\" />\n"
      "<img src=\"image4.png\" alt=\"alternative text2\" />\n" );

  HtmlImagesExtractor htmlImagesExtractor( htmlContent );
  auto images = htmlImagesExtractor.extractImages();
  for( const auto& image : images )
    std::cout << image << '\n';
}