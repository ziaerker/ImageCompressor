This project compress the pgm images and decompress with RLE algorithm and Zia algorithm(I gave it a name.) which is not efficent, not clever idea. Just wanted to try something, did not think on that. But I believe I made a great implementation on RLE algorithm. I learned so much information and got experiences from researches that i did while doing this project.

Zia algorithm as an example we have a line of pixels

160 161 162 163 165 168 169 169 169 170 171 172 173 173 175

If image has a higher resolution the pixels are get more close magnitudes. So zia algorithm leaves last digit of the pixels and save rest of it as domain. After this operation program counts next numbers which has same domain until the different domain. In this example we will have output like this.

[16] [9] [0 1 2 3 5 8 9 9 9] [17] [6] [0 1 2 3 3 5]

Program does not put brackets. I put them to visiulaze the output. First one domain next one number of the pixels that has same domain and the last one is suffixes.


//If you want to make the comments more understandable, review the code in this order:
Image.h > Image.cpp > Compressor.h > Compressor.cpp >  Menu.h > Menu.cpp > main.cpp


//referance links//

about the namespace usage: https://stackoverflow.com/questions/1452721/ [1]
rule of three: https://www.youtube.com/watch?v=OJ7z996wpVk [2]
makefile: https://www.youtube.com/watch?v=_r7i5X0rXJk 
