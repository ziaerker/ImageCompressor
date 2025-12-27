#ifndef IMAGE_H  //CHECKS FOR Image.h DEFINED SOMEWHERE ELSE IF NOT DEFINED THEN GO NEXT LINE
#define IMAGE_H  //DEFINE Image.h

#include <string> //TO BE USE IT IN FUNCTION ARGUMENTS

/* I am not using namespace std; I added a link for that.(in readme file).[1]
I guess using it or not using it will not change anything at all. But my main purpose for this project to simulate sector level coding*/

class Image{

//no need for private if you do not write public or protected, everything is in private

    unsigned int width;
    unsigned int height;
    unsigned char** pixels;
    unsigned short type;
    unsigned short maxVal;

public:

    Image(); //Constructor
    ~Image(); //Deconstructor
    Image(const Image& other); //Copy Constructor                   /*Rule of three (if you have a pointer in your attirbutes then you have to type rule of three.
    Image& operator=(const Image& other); //Assignment Operator      (Added reference to readme)[2]*/

    bool readPGM(const std::string& fileName);          //Will read the pgm file and copy it to Image object and will give us the status of process
    void saveAsPGM(const std::string& fileName);

    //Getters
    unsigned short getType();
    unsigned int getWidth();
    unsigned int getHeight();
    unsigned char getPixel(unsigned int r, unsigned int c); //r and c stand for rows and columns

    //Setters
    void setSize(unsigned int w, unsigned int h);
    void setPixel(unsigned int w, unsigned int h, unsigned char value);
    void setType(unsigned short t);
};



#endif //END OF THE DEFINITION