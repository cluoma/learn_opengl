#include <stdint.h>
#include <iostream>
#include <fstream>
#include <string>
#include <SDL.h>
#include <SDL_opengl.h>
#include <GL/gl.h>


int main() {

    std::string filename = "/home/colin/Games/world-of-warcraft/drive_c/Program Files (x86)/World of Warcraft/Data/data/data.069";

    // open file for reading
    std::ifstream istrm(filename, std::ios::binary);
    if (!istrm.is_open())
        std::cout << "failed to open " << filename << '\n';
    else
    {
        char num;
        istrm >> num;
        int i = 0;
        while ( !istrm.eof() && i < 16) { // keep reading until end-of-file
            std::cout << "The next number is " << num << std::endl;
            istrm >> num; // sets EOF flag if no value found
            i++;
        }
    }

    return 0;
}
