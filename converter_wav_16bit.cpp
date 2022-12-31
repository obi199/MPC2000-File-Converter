//converts any .wav file or all files in cuurent folder to 16bit 44100 MHZ
//uses libsndfile and libsamplerate libraries: https://github.com/libsndfile
//

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <filesystem>
#include "include/sndfile.hh"
#include "include/samplerate.h"

using namespace std;

static string read_write_file (const char * fname)
{
	SndfileHandle file, file2;
	SRC_DATA src_data;

	file = SndfileHandle (fname, SFM_READ) ;
	
	printf ("Opened file '%s'\n", fname) ;
	printf ("    Sample rate : %d\n", file.samplerate ()) ;
	printf ("    Channels    : %d\n", file.channels ()) ;
    //std::cout<< " frames " <<(int)file.frames() << endl;
	int numFrames = file.frames();
	int numChannels = file.channels ();
	int numByte = file.frames();
	int frames = numChannels * numByte;
	float* buffer = new float [frames];
	float* buffer_out = new float[frames];

	if (numChannels < 1)	return "error";

	file.read (buffer, numFrames*numChannels);

	double ratio = (double)44100 / (double)file.samplerate();
	src_data.data_in = buffer;
	src_data.input_frames = frames;
	src_data.data_out = buffer_out;
	src_data.output_frames = frames;
	src_data.src_ratio = ratio;

	//convert with libsamplerate
	int error = src_simple(&src_data, SRC_SINC_BEST_QUALITY, numChannels);
	if (error != 0) {
		std::cerr << "Error occured: "  <<src_strerror(error) << endl;
		return "error";
	}

	int channels = numChannels;
	int format = SF_FORMAT_WAV | SF_FORMAT_PCM_16; //SF_FORMAT_FLOAT SF_FORMAT_PCM_16
	int srate = 44100 ;

	string newFilename = fname;
	const char* fname2 = fname; 
	newFilename = newFilename.substr(0, newFilename.length() - 4);
	newFilename = newFilename.append("_16bit_441Mhz.wav");
	fname2 = newFilename.c_str();
	file2 = SndfileHandle (fname2, SFM_WRITE, format, channels, srate) ;
	
	file2.write (buffer_out, numFrames * numChannels) ; //numFrames*numChannels
	printf("converted file '%s'\n", fname2);
	delete[] buffer_out;
	delete[] buffer;

	return fname2;
} 

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
		string newpath = "16bit";
		std::filesystem::path p = std::filesystem::current_path();
		std::filesystem::create_directories(newpath);
		for (auto const& dir_entry : std::filesystem::directory_iterator{ p })
		{
			if (dir_entry.is_regular_file() && dir_entry.path().extension() == std::string(".wav"))
			{
				filename = dir_entry.path().filename().string();
				const char* fname = filename.c_str();
				string fname2 = read_write_file(fname);
				if(fname2 != "error") std::filesystem::rename(p / fname2, p / newpath / fname2);
			}
		}
	}
	else 
		{
		const char* fname = argv[1];
		auto const& dir_entry = std::filesystem::directory_entry{ fname };
		if (dir_entry.is_regular_file() && dir_entry.path().extension() == std::string(".wav")) read_write_file(fname);
		else std::cout << "\nError: File not existing or not a wave file\n";
		}
	return 0;
} 


