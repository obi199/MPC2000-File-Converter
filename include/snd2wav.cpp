//converts 16 Bit SND 44100hz to 16bit WAV File Format
#include "converter.cpp"
#include <iostream>
#include <cstdio>
#include <string>
#include <stdint.h>
#include <cstring>
#include <fstream>
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
        string newpath = "wav";
        string filename;

        std::filesystem::path p = std::filesystem::current_path();
        std::filesystem::create_directories(newpath);
        for (auto const& dir_entry : std::filesystem::directory_iterator{ p })
        {
            if (dir_entry.is_regular_file() && dir_entry.path().extension() == std::string(".SND"))
            {
                filename = dir_entry.path().filename().string();
                const char* fname = filename.c_str();
                string fname2 = snd2wav(fname);
                if (fname2 != "Error") std::filesystem::rename(p / fname2, p / newpath / fname2);
            }
        }
    }

    else
    {
        const char* fname = argv[1];
        auto const& dir_entry = std::filesystem::directory_entry{ fname };
        if (dir_entry.is_regular_file() && dir_entry.path().extension() == std::string(".SND")) snd2wav(fname);
        else std::cout << "\nError: File not existing or not a SND file\n";
    }
    return 0;
}
