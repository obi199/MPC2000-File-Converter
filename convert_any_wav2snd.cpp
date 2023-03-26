//converts any .wav file or all files in cuurent folder to 16bit 44100 MHZ SND Files
// use -f argument for all file in folder
//uses libsndfile and libsamplerate libraries: https://github.com/libsndfile
//

#include "converter.cpp"
#include <iostream>
#include <cstdio>
#include <cstring>
#include <filesystem>

using namespace std;

int main(int argc, char *argv[])
{
	string filename; 

	if (argc != 2)
	{
		std::cerr << "no argument declared: Use filename or -f to convert all files in folder" << endl;
		return 1;
	}
	
	if (argv[1] == std::string("-f"))
	{	
		string newpath = "SND";
		std::filesystem::path p = std::filesystem::current_path();
		std::filesystem::create_directories(newpath);
		for (auto const& dir_entry : std::filesystem::directory_iterator{ p })
		{
			if (dir_entry.is_regular_file() && dir_entry.path().extension() == std::string(".wav"))
			{
				try
				{
				filename = dir_entry.path().filename().string();
				const char* fname = filename.c_str();
				string cWav = read_write_wav(fname);
				const char* newWavFile = cWav.c_str();
				string fname2 = wav2snd(newWavFile);
				if (fname2 != "error") std::filesystem::rename(p / fname2, p / newpath / fname2);
				std::filesystem::remove(cWav);
				}
				catch (...)
				{
					cerr << "unexpected error with " << filename << "\n";
				}
				
			}
		}
	}
	else 
		{
		const char* fname = argv[1];
		auto const& dir_entry = std::filesystem::directory_entry{ fname };
		if (dir_entry.is_regular_file() && dir_entry.path().extension() == std::string(".wav")) {
			string aFilename = read_write_wav(fname);
			const char*  newWavFile = aFilename.c_str();
			wav2snd(newWavFile);

		}
		else std::cout << "\nError: File not existing or not a wave file\n";
		}
	return 0;
} 

extern "C" void __cdecl abort(void)
{
	volatile int a = 0;
	a = 1 / a;
}


