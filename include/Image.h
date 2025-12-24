#ifndef IMAGE_H  //CHECKS FOR Image.h DEFINED SOMEWHERE ELSE IF NOT DEFINED THEN GO NEXT LINE
#define IMAGE_H  //DEFINE Image.h

#include <string> //TO BE ABLE TO GET INPUT AND OUTPUT FILE NAMES

/* I am not using namespace std; I added a link for that.(in readme file).[1]
I guess using it or not using it will not change anything at all. But my main purpose for this project to simulate sector level coding*/

class Image{

//no need for private if you do not write public or protected, everything is in private

    unsigned short width;
    unsigned short height;
    unsigned char** pixels;

public:

    Image(); //Constructor
    ~Image(); //Deconstructor
    Image(const Image& other); //Copy Constructor                   /*Rule of three (if you have a pointer in your attirbutes then you have to type rule of three.
    Image& operator=(const Image& other); //Assignment Operator      (Added reference to readme)[2]*/

    bool readPGM(const std::string& fileName);          //I chose bool instead of void because I wanted to make sure file opening process is successfull.
    void saveAsPGM(const std::string& fileName);
};

#endif //END OF THE DEFINITION