//converts 16 Bit SND 44100hz to 16bit WAV File Format

#include "include/wav.h"
#include "include/snd.h"
#include "byte_utils.cpp"
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <stdint.h>
#include <cstring>
#include <fstream>
#include <filesystem>

using namespace std;
FILE    *infile, *outfile;
char    *buffer;
long    numbytes;
struct HEADER_WAV headerWAV;
struct HEADER_SND headerSND;

static string snd2wav(const char* fname)
{
FILE* infile = fopen(fname, "r");
/* quit if the file does not exist */
if(infile == NULL)
    return "Error";
uint32_t size;
fseek(infile, 0, SEEK_END);
size = ftell(infile);
fseek(infile, 0, SEEK_SET);
const size_t bufSize = size ;
fclose(infile);

char* buf = new char[bufSize];
const char* ptr;
ptr = fname;
ifstream sndFile (ptr, ios::in | ios::binary);
if (!sndFile.is_open())
       {
        cerr << "File Open Error"<<endl;
        exit(1);
       } 
sndFile.read(buf, bufSize);
sndFile.close();
//###create header###
strcpy(headerWAV.ckID,"RIFF");
headerWAV.cksize = size;
strcpy(headerWAV.WAVEID,"WAVE");
strcpy(headerWAV.ckID2,"fmt ");
headerWAV.cksize2 = 16;
headerWAV.wFormatTag = 1;
headerWAV.nChannels = buf[21]+1;
headerWAV.nSamplesPerSec = bytes2unsignedShort(buf[40],buf[41]);
headerWAV.nAvgBytesPerSec = headerWAV.nSamplesPerSec*2*headerWAV.nChannels ;
headerWAV.wBitsPerSample = 16;
headerWAV.nBlockAlign = headerWAV.wBitsPerSample*headerWAV.nChannels / 8;
strcpy(headerWAV.ckID3,"data");
int num_samples = (size - 42) / headerWAV.nBlockAlign;
headerWAV.cksize3 = 2 * headerWAV.nChannels * num_samples;

//cout<<headerWAV.WAVEID<<"  "<< sizeof(headerWAV.WAVEID)<<endl;
//cout<<headerWAV.ckID2<<endl;
//cout<< "wFormatTag="<<(int)headerWAV.wFormatTag << endl;
//cout<< "Channels: " << (int)headerWAV.nChannels << endl;
//cout<< (int)headerWAV.nSamplesPerSec<<endl;
//cout<< (int)headerWAV.nAvgBytesPerSec<<" "<< sizeof(headerWAV.nAvgBytesPerSec)<< endl;
//cout<<"nBlockAlign=" <<headerWAV.nBlockAlign<<endl;
//cout<< (int)headerWAV.wBitsPerSample<<endl;
//cout<<headerWAV.ckID3<<endl;
//cout<<"cksize3="<<(int)headerWAV.cksize3<<endl;
//cout << "HeaderSize=" << size - (int)headerWAV.cksize3 << endl;

//read sample data into vector####
vector <short> ldata; 
vector <short> rdata;
for (int i = 42; i < size; i+=2) // i+=2
	{
	uint16_t smpl1 = bytes2Short(buf[i], buf[i+1]);
    ldata.push_back(smpl1);
    if (headerWAV.nChannels==2)
        {
        uint16_t smpl2 = bytes2Short(buf[i], buf[i+1]);
        rdata.push_back(smpl2);
        }
    }
//create wav file with same name
string filename = ptr;
// Remove extension if present.
const size_t period_idx = filename.rfind('.');
if (std::string::npos != period_idx)
{
    filename.erase(period_idx);
}

filename=filename.append(".wav");

const char* ofileNameSND = filename.c_str();
//write to file
FILE* outfile = fopen(ofileNameSND, "wb");
if (outfile == NULL)
    return "Error";
fseek(outfile, 0, SEEK_SET);
fwrite(&headerWAV.ckID,sizeof(headerWAV.ckID),1,outfile);
fwrite(&headerWAV.cksize,sizeof(headerWAV.cksize),1,outfile);
fwrite(&headerWAV.WAVEID,sizeof(headerWAV.WAVEID),1,outfile);
fwrite(&headerWAV.ckID2,sizeof(headerWAV.ckID2),1,outfile);
fwrite(&headerWAV.cksize2,sizeof(headerWAV.cksize2),1,outfile);
fwrite(&headerWAV.wFormatTag,sizeof(headerWAV.wFormatTag),1,outfile);
fwrite(&headerWAV.nChannels,sizeof(headerWAV.nChannels),1,outfile);
fwrite(&headerWAV.nSamplesPerSec,sizeof(headerWAV.nSamplesPerSec),1,outfile);
fwrite(&headerWAV.nAvgBytesPerSec,sizeof(headerWAV.nAvgBytesPerSec),1,outfile);
fwrite(&headerWAV.nBlockAlign,sizeof(headerWAV.nBlockAlign),1,outfile);
fwrite(&headerWAV.wBitsPerSample,sizeof(headerWAV.wBitsPerSample),1,outfile);
fwrite(&headerWAV.ckID3,sizeof(headerWAV.ckID3),1,outfile);
fwrite(&headerWAV.cksize3,sizeof(headerWAV.cksize3),1,outfile);

//if mono..
int length = ldata.size();
//if stereo..
if (headerWAV.nChannels == 2) length /= 2;

//write Data to File
int j = 0;
for (int i = 0; i < length; i++)
    {
     short &samplebuffer = ldata[i];
     fwrite(&samplebuffer,sizeof(samplebuffer),1,outfile); 

    if (headerWAV.nChannels == 2)
         {
         short& samplebuffer2 = rdata[j + ldata.size()/2];
         fwrite(&samplebuffer2, sizeof(samplebuffer2), 1, outfile);
         j++;
         }
     }

fclose(outfile);
delete[] buf;
std::cout << "File converted to: " << filename << endl;
return filename;
}


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
