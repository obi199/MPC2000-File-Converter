#include "converter.h"
//#include "convert_any_wav2snd.cpp"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <stdint.h>
#include <cstring>
#include <cctype>
#include <filesystem>
using namespace std;

int main(int argc, char* argv[])
{
    //open wav file and read headerWAV
    cout << "Copyright (C) 2022 obi199" << endl;

    if (argc != 3)
    {
        cerr << "Run in folder with files! \nError: no parameters declared. Here is the command list: \n16bitwav2snd (filename) or (-all)\nanywav2snd (filename) or (-all)\n" << endl;
        return 1;
    }

    string param = std::string(argv[1]);
    string nfile = std::string(argv[2]);

    if (param == "16bitwav2snd")
    {   
       
        convert16Bitwav2snd(nfile);
    }

    if (param == "anywav2snd")
    {
        convert_any_wav2snd(nfile);
    }

    else
    {
        std::cout << "Run in folder with files!\nWrong parameter. Here are the commands: \n16bitwav2snd (filename) or (-all)\n anywav2snd (filename) or (-all)\n";
    }
    return 0;
}