#include "Image.h" //To be able to reach class members we have to type this.
#include <iostream>
#include <fstream>
#include <string>

Image::Image(){

    width = 0; //cols number
    height = 0; //rows number
    type = 0; //P2 OR P5
    maxVal = 255; //I saw it 99% of the PGMs are have value of 255 so i assuma all of them max value 255
    pixels = nullptr;

}

Image::~Image(){

    if(pixels != nullptr){          //checks for pointer points something otherwise we do not need to delete.

        for(unsigned int i = 0; i<height; i++){
            delete[] pixels[i];
        }
        delete[] pixels;
    }

}

Image::Image(const Image& other){

    //It would work without this operator but I wrote it still

    width = other.width;
    height = other.height;
    type = other.type;
    maxVal = other.maxVal;

    /*we are creating new object instead of copying one to another. 
    So we do not need to use delete before the allocate memmory*/

    pixels = new unsigned char*[height];
    for(unsigned int i = 0; i<height; i++){    //allocate memmory
        pixels[i] = new unsigned char[width];
    }

    for(unsigned int i = 0; i<height; i++){
        for(unsigned int j = 0; j<width; j++){   //copy elements one by one.
            pixels[i][j] = other.pixels[i][j];
        }
    }

}

Image& Image::operator=(const Image& other){

    if(this == &other){
        return *this;       //if these are the same return it's address if not continue
    }

    for(unsigned int i = 0; i<height; i++){
        delete[] pixels[i];                     //delete the previous one and define the new variables
    }
    delete[] pixels;

    width = other.width;
    height = other.height;  //we can set the variables easly except the pixels because we have to allocate memmory and copy it one by one

    pixels = new unsigned char*[height];
    for(unsigned int i = 0; i<height; i++){    //allocate memmory
        pixels[i] = new unsigned char[width];
    }

    for(unsigned int i = 0; i<height; i++){
        for(unsigned int j = 0; j<width; j++){   //copy elements one by one.
            pixels[i][j] = other.pixels[i][j];
        }
    }

    return *this;
}

bool Image::readPGM(const std::string& fileName){//DO NOT FORGET TO CLOSE THE FILES!!!!

    std::ifstream PGMphoto(fileName, std::ios::binary);

    if(!PGMphoto.is_open()){
        std::cout<<"File could not opened."<<std::endl; //return false if file could not opened
        return false;
    }
    char magicNumber;
    
    PGMphoto>>magicNumber;      //trash variable iw will not use it.
    PGMphoto>>type;
    PGMphoto>>width;            //we can read the information with >> operator for p2 and p5 beacuse these informations are type of char
    PGMphoto>>height;
    PGMphoto>>maxVal;           //it seems i do not use this variable but still saving to a variable.

    pixels = new unsigned char*[height];
    for(unsigned int i = 0; i<height; i++){
        pixels[i] = new unsigned char[width];
    }

    if(type == 2){//ASCII

        unsigned int temp;

        for(unsigned int i = 0; i<height; i++){
            for(unsigned int j = 0; j<width; j++){
                PGMphoto>>temp;
                pixels[i][j] = (unsigned char)temp;//i did like this first take the ascii value and than save it to the matrix in unsigned char form.
            }
        }
        PGMphoto.close();
        return true;

    }                                       //but we can not say it for the pixel informations. P2 holds the pixel in ascii form but p5 holds it in binary form. So we have to use different type of reading techniques.
    else if(type == 5){//BINARY             //we can use >> operator for p2 but we cannot use for p5 instead we have to use .read().

        PGMphoto.ignore(1);

        for(unsigned int i = 0; i<height; i++){
            for(unsigned int j = 0; j<width; j++){
                PGMphoto.read((char*)&pixels[i][j], sizeof(unsigned char));
            }
        }
        PGMphoto.close();
        return true;
    }
    return false;

}
void Image::saveAsPGM(const std::string& fileName){//DO NOT FORGET TO CLOSE THE FILES!!!!

    std::ofstream save(fileName, std::ios::binary);

    if(!save.is_open()){
        std::cerr<<"File could not created."<<std::endl;        //catch the error in menu DO NOT FORGET!!!!!!
        return;
    }

    save<<"P"<<type<<"\n";
    save<<width<<" "<<height<<"\n";
    save<<maxVal<<"\n";

    if(type == 2){

        for(unsigned int i = 0; i<height; i++){
            for(unsigned int j = 0; j<width; j++){//there are different type of pgms (P2 OR P5) and we can save these binary 
                save<<(int)pixels[i][j]<<" ";
            }
            save<<"\n";
        }
        save.close();
    }
    else if(type == 5){

        for(unsigned int i = 0; i<height; i++){
            for(unsigned int j = 0; j<width; j++){
                save.write((char*)&pixels[i][j], sizeof(unsigned char));
            }
        }
        save.close();

    }
}
unsigned short Image::getType(){
    return type;
}
unsigned int Image::getWidth(){//basic getters
    return width;
}
unsigned int Image::getHeight(){
    return height;
}
unsigned char Image::getPixel(unsigned int r, unsigned int c){
    if(c>=0 && c<width && r>=0 && r<height){
        return pixels[r][c];
    }
    return 0;
}

void Image::setSize(unsigned int w, unsigned int h){//i use it once but it was necessary

    if(pixels != nullptr){
        for(unsigned int i = 0; i<height; i++){
            delete[] pixels[i];
        }
        delete[] pixels;
    }

    width = w;
    height = h;

    pixels = new unsigned char*[height];
    for(unsigned int i = 0; i<height; i++){
        pixels[i] = new unsigned char[width];
    }
}
void Image::setPixel(unsigned int w, unsigned int h, unsigned char value){//sets the values to the pixels

    pixels[h][w] = value;

}
void Image::setType(unsigned short t){
    type = t;
}

