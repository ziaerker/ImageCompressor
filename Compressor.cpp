#include "Compressor.h"
#include <fstream>
#include <string>
#include <iostream>

void CompressRLE(Image& img, const std::string& fileName){
    
    std::ofstream file(fileName);

    if(!file.is_open()){
        std::cerr <<"Error Compressed File could not created."<<std::endl;
        return;
    }
    unsigned short t = img.getType();
    unsigned int w = img.getWidth();
    unsigned int h = img.getHeight();

    file<<w<<" ";
    file<<h;
    //now we have to count one by one
    //for reference we get first pixel and then start the loop

    unsigned char pixel = img.getPixel(0,0); //takes the first pixel
    int counter = 1;

    for(unsigned int i = 0; i<h; i++){
        for(unsigned int j = 0; j<w; j++){

            if(i == 0 && j == 0){
                continue;           //we took first pixel already so we pass it
            }

            unsigned char nextPixel = img.getPixel(i,j);

            if(pixel == nextPixel){
                counter++;
            }
            else{
                file<<" "<<counter<<" "<<(int)pixel<<" ";
                pixel = nextPixel;
                counter = 1;
            }
            
        }
    }
    file<<counter<<" "<<(int)pixel;

    file.close();
    std::cout<<"Compression is completed. "<<fileName<<" created"<<std::endl;
}
Image DecompressRLE(const std::string& fileName){

    Image img;

    std::ifstream file(fileName);

    if(!file.is_open()){
        std::cerr<<"Error: Compressed file could not opened."<<std::endl;
        return img; //if program can not open and decompress the file will return empty object
    }

    unsigned int w;
    unsigned int h;

    file>>w;
    file>>h;

    img.setSize(w,h);

    unsigned int count = 0;
    unsigned int value = 0;

    unsigned int currentRowCursor = 0;
    unsigned int currentColCursor = 0;  //to be able to put the matrix one by one

    while(file>>count>>value){

        for(unsigned int i = 0; i<count; i++){
            img.setPixel(currentColCursor, currentRowCursor, (unsigned char)value);

            currentColCursor++;

            if(currentColCursor == w){
                currentColCursor = 0;
                currentRowCursor++;
            }
        }

    }
    file.close();
    return img;

}


//DO THIS LAST!!!!!!!!
void CompressHuffman();      
Image DecompressHuffman();
