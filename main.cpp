#include "converter.h"

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
    int numFiles = 0;

    if (argc != 3)
    {
        cerr << "Run in folder with files! \nError: no parameters declared. Here is the command list: \n16bitwav2snd (filename) or (-all)\nanywav2snd (filename) or (-all)\nwav16bit\nConvertSnd2Wav (filename) or (-all)" << endl;
        return 1;
    }
    string param = std::string(argv[1]);
    string nfile = std::string(argv[2]);

    if (param == "16bitwav2snd")
    {   
        numFiles = convert16Bitwav2snd(nfile);
    }
    else if (param == "anywav2snd")
    {
        numFiles = convert_any_wav2snd(nfile);
    }
    else if (param == "wav16bit")
    {
        numFiles = convertwav16bit(nfile);
    }
    else if (param == "snd2wav")
    {
        numFiles = ConvertSnd2Wav(nfile);
    }
    else
    {
        std::cout << "Error: Run in folder with files! Commands: \n16bitwav2snd (filename) or (-all)\nanywav2snd (filename) or (-all)\nConvertSnd2Wav (filename) or (-all)";
    }
    cout << numFiles << " Files converted" << endl;

    return 0;
}