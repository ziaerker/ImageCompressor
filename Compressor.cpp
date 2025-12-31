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
void CompressMyAlg(Image& img, const std::string& fileName){

    std::ofstream file(fileName, std::ios::binary);

    if(!file.is_open()){                                //STANDART PROCEDURES
        std::cerr<<"File could not be opened"<<std::endl;
        return;
    }

    unsigned int w = img.getWidth();
    unsigned int h = img.getHeight();

    file.write((char*)&w, sizeof(unsigned int));
    file.write((char*)&h, sizeof(unsigned int));

    unsigned int maxCapacity = w*h; //THIS ALGORITHM MIGHT BE USE MORE THAN THE OTHER ALGORITHMS. TO PREVENT THE CRASHES I AM ALLOCATING A LOT OF MEMORY

    unsigned char* suffixes = new unsigned char[maxCapacity];

    unsigned char initialPixel = img.getPixel(0,0);
    unsigned char activeDomain = initialPixel / 10;//needed just to get started

    unsigned int size = 0;
    for(unsigned int i = 0; i<h; i++){
        for(unsigned int j = 0; j<w; j++){

            unsigned char domain = img.getPixel(i,j) / 10;
            unsigned char suffix = img.getPixel(i,j) % 10;

            if(domain == activeDomain){//this means we have same prefixes note for myself: explain clearly whats prefix used for!!! 
                suffixes[size] = suffix;
                size++;
            }
            else{

                file.write((char*)&activeDomain, sizeof(unsigned char));
                file.write((char*)&size, sizeof(unsigned int));
                for(unsigned int k = 0; k<size; k++){
                    file.write((char*)&suffixes[k], sizeof(unsigned char));
                }

                activeDomain = domain;
                size = 0;

                suffixes[size] = suffix;
                size++;
                

            }
        }
    }

    file.write((char*)&activeDomain, sizeof(unsigned char));
    file.write((char*)&size, sizeof(unsigned int));
    for(unsigned int i = 0; i<size; i++){
        file.write((char*)&suffixes[i], sizeof(unsigned char));
    }
    delete[] suffixes;
    file.close();


}      
Image DecompressMyAlg(const std::string& fileName){

    Image img;

    std::ifstream file(fileName, std::ios::binary);

    if(!file.is_open()){
        std::cerr<<"File could not opened."<<std::endl;
        return img;
    }

    unsigned int w, h;

    file.read((char*)&w, sizeof(unsigned int));
    file.read((char*)&h, sizeof(unsigned int));

    img.setSize(w,h);

    unsigned char activeDomain;
    unsigned int size;
    unsigned char suffix;

    unsigned int row = 0;       //to put the values exact coordinates
    unsigned int col = 0;

    while(file.read((char*)&activeDomain, sizeof(unsigned char))){   //this expression returns a bool so while this argument returns true than keep going if its not then return false

        file.read((char*)&size, sizeof(unsigned int));

        for(unsigned int i = 0; i<size; i++){

            file.read((char*)&suffix, sizeof(unsigned char));

            unsigned int pixelValue = (activeDomain * 10) + suffix;

            img.setPixel(col, row, (unsigned char)pixelValue);
            col++;

            if(col == w){
                col = 0;
                row++;
            }

        }

    }
    file.close();
    std::cout<<"Decompression Completed"<<std::endl;
    return img;

}
