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

    /*we are creating new object instead of copying one to another. 
    So we do not need to use delete before the allocate memmory*/

    pixels = new unsigned char*[width];
    for(unsigned short i = 0; i<width; i++){    //allocate memmory
        pixels[i] = new unsigned char[height];
    }

    for(unsigned short i = 0; i<width; i++){
        for(unsigned short j = 0; j<height; j++){   //copy elements one by one.
            pixels[i][j] = other.pixels[i][j];
        }
    }

}

Image& Image::operator=(const Image& other){

    if(this == &other){
        return *this;       //if these are same return it's address
    }

}
