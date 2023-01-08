//converts 16 Bit wav 44100hz to SND

#include "include/wav.h"
#include "include/snd.h"
#include "byte_utils.cpp"
#include <iostream>
#include <fstream>
#include <cstdio>//
#include <string>
#include <vector>
#include <stdint.h>
#include <cstring>
#include <cctype>
#include <filesystem>
using namespace std;
FILE    *infile, *outfile;
char    *buffer;
long    numbytes;
struct HEADER_WAV headerWAV;
struct HEADER_SND headerSND;

static string wav2snd (const char* fname)
{
//open wav file and read headerWAV
//cout << "Copyright (C) 2022 obi199" << endl;
//if ( argc !=2 )
//    {
//        cerr << "no filemane declared"<<endl;
//        return 1;
//    }	
/* open an file for reading */
//FILE* infile = fopen(argv[1], "r"); 
FILE* infile = fopen(fname, "r");
/* quit if the file does not exist */
if(infile == NULL)
    return "Error";
uint32_t size;
fseek(infile, 0, SEEK_END);
size = ftell(infile);
fseek(infile, 0, SEEK_SET);
const size_t bufSize = size;
char* buf = new char[bufSize];
fclose(infile);

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


// headerWAV.ckID = getText(buf, 0, 4);
headerWAV.cksize = bytes_2_u_int32(buf[4], buf[5], buf[6],buf[7]);
// headerWAV.WAVEID = getText(buf, 8, 12);
// headerWAV.ckID2 = getText(buf, 12, 16);
// headerWAV.cksize2 = bytes2Long(buf[16], buf[17], buf[18],buf[19]);
headerWAV.wFormatTag = bytes2unsignedShort(buf[20], buf[21]);
headerWAV.nChannels = bytes2unsignedShort(buf[22], buf[23]);
headerWAV.nSamplesPerSec = bytes_2_u_int32(buf[24], buf[25], buf[26], buf[27]);
headerWAV.nAvgBytesPerSec = bytes_2_u_int32(buf[28], buf[29], buf[30], buf[31]);
headerWAV.nBlockAlign = bytes2unsignedShort(buf[32], buf[33]);
headerWAV.wBitsPerSample = bytes2unsignedShort(buf[34], buf[35]);
// headerWAV.ckID3 = getText(buf, 36, 40);
headerWAV.cksize3 = bytes_2_u_int32(buf[40], buf[41], buf[42],buf[43]);
unsigned short samplerate = bytes2unsignedShort(buf[24], buf[25]);

//// cout<<"ckID="<<headerWAV.ckID<<endl;
// cout<<"cksize="<<headerWAV.cksize<<endl;
//// cout<<"WAVEID="<<headerWAV.WAVEID<<endl;
//// cout<<"ckID2="<<headerWAV.ckID2<<endl;
//// cout<<"cksize2="<<headerWAV.cksize2<<endl;
//cout<<"wFormatTag="<<headerWAV.wFormatTag<<endl;
//cout<<"nChannels="<<headerWAV.nChannels<<endl;
//cout<<"nSamplesPerSec="<<headerWAV.nSamplesPerSec<<endl;
//cout<<"nAvgBytesPerSec="<<headerWAV.nAvgBytesPerSec<<endl;
//cout<<"nBlockAlign="<<headerWAV.nBlockAlign<<endl;
//cout<<"wBitsPerSample="<<headerWAV.wBitsPerSample<<endl;
//cout<<"ckID3="<<headerWAV.ckID3<<endl;
//cout<<"cksize3="<<headerWAV.cksize3<<endl;

//read sample data into vector
if (headerWAV.wFormatTag != 1)
        {
        cerr << "Error: not a pcm type"<<endl;
        return "Error";
        }

long num_samples = (8 * headerWAV.cksize3) / (headerWAV.nChannels * headerWAV.wBitsPerSample);
//int num_samples = (size - 44) / headerWAV.nBlockAlign;

vector <short> ldata;
vector <short> rdata;
for (int i = 44; i < size; i += 2) // i+=2
{
    uint16_t smpl = bytes2Short(buf[i], buf[i + 1]);
    ldata.push_back(smpl);
    if (headerWAV.nChannels == 2)
    {
        uint16_t smpl2 = bytes2Short(buf[i], buf[i + 1]);
        rdata.push_back(smpl2);
    }
}

//create SND Filename
string filename = ptr;
string opath;
// Remove directory if present + extract path
const size_t last_slash_idx = filename.find_last_of("\\/");
if (std::string::npos != last_slash_idx)
{   
    opath = filename.substr(0, last_slash_idx + 1);
    filename.erase(0, last_slash_idx + 1);
}
// Remove extension if present.
const size_t period_idx = filename.rfind('.');
if (std::string::npos != period_idx)
{
    filename.erase(period_idx);
}
//remove spaces
filename = remove_spaces(filename);

if (filename.length() > 8) filename = filename.substr(0, 8);

const char* sfilename = filename.c_str();
//create SND Header
headerSND.chk1 = 1;
headerSND.chk2 = 4;
strcpy(headerSND.name , sfilename);
headerSND.pad = ' ';
headerSND.level = 100;
headerSND.tune = 0;
headerSND.channels = static_cast <unsigned char>(headerWAV.nChannels - 1); 	
headerSND.start = 0;
headerSND.loopend = num_samples;
headerSND.end = num_samples;
headerSND.looplength = 0; 
headerSND.loopmode = 0; 
headerSND.beatsinloop = 1;
headerSND.sample_frequency = samplerate; 

filename.append(".SND");
filename = opath + filename;
const char* ofileNameSND = filename.c_str();
FILE* outfile = fopen(ofileNameSND, "wb");
if (outfile == NULL)
    return "Error";
fseek(outfile, 0, SEEK_SET);
fwrite(&headerSND.chk1,sizeof(headerSND.chk1),1,outfile);
fwrite(&headerSND.chk2,sizeof(headerSND.chk2),1,outfile);
fwrite(&headerSND.name,sizeof(headerSND.name),1,outfile);
fwrite(&headerSND.pad,sizeof(headerSND.pad),1,outfile);
fwrite(&headerSND.level,sizeof(headerSND.level),1,outfile);
fwrite(&headerSND.tune,sizeof(headerSND.tune),1,outfile);
fwrite(&headerSND.channels,sizeof(headerSND.channels),1,outfile);
fwrite(&headerSND.start,sizeof(headerSND.start),1,outfile);
fwrite(&headerSND.loopend,sizeof(headerSND.loopend),1,outfile);
fwrite(&headerSND.end,sizeof(headerSND.end),1,outfile);
fwrite(&headerSND.looplength,sizeof(headerSND.looplength),1,outfile);
fwrite(&headerSND.loopmode,sizeof(headerSND.loopmode),1,outfile);
fwrite(&headerSND.beatsinloop,sizeof(headerSND.beatsinloop),1,outfile);
fwrite(&headerSND.sample_frequency,sizeof(headerSND.sample_frequency),1,outfile);

int length = ldata.size();

//if mono..
if (headerWAV.nChannels == 1)
{
    for (int i = 0; i < length; i++) {
        short& samplebuffer = ldata[i];
        fwrite(&samplebuffer, sizeof(samplebuffer), 1, outfile);
    }
}
//if stereo..
if (headerWAV.nChannels == 2){
    for (int i = 0; i < length; i+=2){
    short& samplebuffer = ldata[i];
    fwrite(&samplebuffer, sizeof(samplebuffer), 1, outfile);
    }

    for (int i = 1 ; i < length; i+=2){
    short& samplebuffer2 = rdata[i];
    fwrite(&samplebuffer2, sizeof(samplebuffer2), 1, outfile);
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
                if (fname2 != "error") std::filesystem::rename(p / fname2, p / newpath / fname2);
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
