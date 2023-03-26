//converts 16 Bit wav 44100hz to SND

#include "converter.cpp"
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

    if (argc != 2)
    {
        cerr << "no filemane declared" << endl;
        return 1;
    }

    if (argv[1] == std::string("-f"))
    {
        string newpath = "snd";
        string filename;

        std::filesystem::path p = std::filesystem::current_path();
        std::filesystem::create_directories(newpath);
        for (auto const& dir_entry : std::filesystem::directory_iterator{ p })
        {
            if (dir_entry.is_regular_file() && dir_entry.path().extension() == std::string(".wav"))
            {
                filename = dir_entry.path().filename().string();
                const char* fname = filename.c_str();
                string fname2 = wav2snd(fname);
                if (fname2 != "Error") std::filesystem::rename(p / fname2, p / newpath / fname2);
            }
        }
    }

    else
    {
        const char* fname = argv[1];
        auto const& dir_entry = std::filesystem::directory_entry{ fname };
        if (dir_entry.is_regular_file() && dir_entry.path().extension() == std::string(".wav")) wav2snd(fname);
        else std::cout << "\nError: File not existing or not a wave file\n";
    }
    return 0;
}
