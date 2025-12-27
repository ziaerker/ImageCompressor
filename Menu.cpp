#include <iostream>
#include "Compressor.h"
#include "Image.h"
#include "Menu.h"
#include <string>

void Menu(){

    Image menuImg;
    std::string choice = "";
    std::cout<<"Image Compressor!"<<std::endl;
    std::cout<<"1) Compress a PGM with RLE Metod"<<std::endl;
    std::cout<<"2) Decompress a .zee file to .PGM"<<std::endl;
    std::cout<<"You have to write exactly Compress to compress a file and Decompress to decompress a file"<<std::endl;
    std::cin>>choice;

    if(choice == "Compress"){
        std::string fileName = "";
        std::cout<<"Write the exact name of the file including extension(for example 'test.pgm')"<<std::endl;
        std::cin>>fileName;
        if(menuImg.readPGM(fileName)){//open the file before we change the extension

            fileName = fileName.erase(fileName.length() - 4);
            fileName += ".zee";
            CompressRLE(menuImg, fileName);

        }
        else{
            std::cerr<<"Error: .zee file could not be created."<<std::endl;
        }
        
    }
    else if(choice == "Decompress"){
        

        unsigned int choice2;
        std::string zeeFile = "";
        std::cout<<"Write name of your .zee file exactly"<<std::endl;
        std::cin>>zeeFile;
        Image decompressed = DecompressRLE(zeeFile);
        std::cout<<"Which type you want to convert your .zee file"<<std::endl;
        std::cout<<"You can simply write 2 for P2, 5 for P5 type."<<std::endl;
        std::cin>>choice2;

        if(choice2 == 5){
            decompressed.setType(5);
        }
        else{
            decompressed.setType(2);
        }

        std::string output = zeeFile;
        output = output.erase(output.length() - 7);
        output += "_out.pgm";

        decompressed.saveAsPGM(output);

    }
    else{
        std::cerr<<"Invalid input!"<<std::endl;
        return;
    }

}
