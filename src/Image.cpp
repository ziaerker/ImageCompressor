#include "Image.h" //To be able to reach class members we have to type this.
#include <iostream>
#include <fstream>
#include <string>

Image::Image(){

    width = 0;
    height = 0;
    pixels = nullptr;

}

Image::~Image(){

    if(pixels != nullptr){          //checks for pointer points something otherwise we do not need to delete.

        for(unsigned short i = 0; i<height; i++){
            delete[] pixels[i];
        }
        delete[] pixels;
    }

}

Image::Image(const Image& other){

    //It would work without this operator but I wrote it still

    width = other.width;
    height = other.height;

    

}

Image& Image::operator=(const Image& other){



}
