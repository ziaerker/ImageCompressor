#ifndef COMPRESSOR_H
#define COMPRESSOR_H
#include "Image.h"

void CompressRLE(Image& img, const std::string& fileName);  //I looked for the lossles compression techniques and i found the rle compression i will apply this technique for the project

Image DecompressRLE(const std::string& fileName);


//DO THIS LAST!!!!!!!!
void CompressMyAlg(Image& img, const std::string& fileName);      
Image DecompressMyAlg(const std::string& fileName);


#endif