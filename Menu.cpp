#include <iostream>
#include "Compressor.h"
#include "Image.h"
#include "Menu.h"
#include <string>

void Menu(){

    Image menuImg;
    std::string choice = "";
    std::cout<<"Image Compressor!"<<std::endl;
    std::cout<<"1) Compress a PGM with RLE Method or My Compression Algorithm"<<std::endl;
    std::cout<<"2) Decompress a .zee or .Zia file to .PGM"<<std::endl;
    std::cout<<"You have to write exactly Compress to compress a file and Decompress to decompress a file"<<std::endl;
    std::cin>>choice;

    if(choice == "Compress"){
        std::string choice2 = "";
        std::cout<<"Which compression type do you want to apply to your image. Write down RLE to compress with RLE technic, or type Zia to compress with my own compression technic."<<std::endl;
        std::cin>>choice2;

        if(choice2 == "RLE"){

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
        else if(choice2 == "Zia"){
            std::string fileNameZ = "";
            std::cout<<"Write the exact name of the file including extension(for example 'test.pgm')"<<std::endl;
            std::cin>>fileNameZ;
            if(menuImg.readPGM(fileNameZ)){//open the file before we change the extension

                fileNameZ = fileNameZ.erase(fileNameZ.length() - 4);
                fileNameZ += ".Zia";
                CompressMyAlg(menuImg, fileNameZ);

            }
            else{
                std::cerr<<"Error: .Ziya file could not be created."<<std::endl;
            }
        }
        else{
            std::cerr<<"Error: Invalid input."<<std::endl;
        }
        
    }
    else if(choice == "Decompress"){
        std::string decompresFile = "";
        std::cout<<"Write down your file"<<std::endl;
        std::cin>>decompresFile;
        std::string extension = decompresFile.substr(decompresFile.length() - 4);
        
        if(extension == ".zee"){

            Image decompressedRLE = DecompressRLE(decompresFile);
            unsigned int choice2;

            std::cout<<"Which type you want to convert your .zee file"<<std::endl;
            std::cout<<"You can simply write 2 for P2, 5 for P5 type."<<std::endl;
            std::cin>>choice2;

            if(choice2 == 5){
                decompressedRLE.setType(5);
            }
            else{
                decompressedRLE.setType(2);
            }

            std::string output = decompresFile;
            output = output.erase(output.length() - 4);
            output += "_out_zee.pgm";

            decompressedRLE.saveAsPGM(output);
        }
        else if(extension == ".Zia"){

            Image decompressedZia = DecompressMyAlg(decompresFile);
            unsigned int choice3;

            std::cout<<"Which type you want to convert your .Zia file"<<std::endl;
            std::cout<<"You can simply write 2 for P2, 5 for P5 type."<<std::endl;
            std::cin>>choice3;

            if(choice3 == 5){
                decompressedZia.setType(5);
            }
            else{
                decompressedZia.setType(2);
            }

            std::string output = decompresFile;
            output = output.erase(output.length() - 4);
            output += "_out_Zia.pgm";

            decompressedZia.saveAsPGM(output);            

        }
        else{
            std::cerr<<"Invalid File Name input!"<<std::endl;
            return;
        }

    }
    else{
        std::cerr<<"Invalid input!"<<std::endl;
        return;
    }

}