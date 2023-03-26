//converts 16 Bit SND 44100hz to 16bit WAV File Format

#include "include/sndfile.hh"
#include "include/samplerate.h"
#include "include/wav.h"
#include "include/snd.h"
#include "byte_utils.cpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdio>
#include <string>
#include <vector>
#include <stdint.h>
#include <cstring>
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


static string wav2snd(const char* fname)
{

    FILE* infile = fopen(fname, "r");
    /* quit if the file does not exist */
    if (infile == NULL)
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
    ifstream sndFile(ptr, ios::in | ios::binary);
    if (!sndFile.is_open())
    {
        cerr << "File Open Error" << endl;
        exit(1);
    }
    sndFile.read(buf, bufSize);
    sndFile.close();


    // headerWAV.ckID = getText(buf, 0, 4);
    headerWAV.cksize = bytes_2_u_int32(buf[4], buf[5], buf[6], buf[7]);
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
    headerWAV.cksize3 = bytes_2_u_int32(buf[40], buf[41], buf[42], buf[43]);
    unsigned short samplerate = bytes2unsignedShort(buf[24], buf[25]);

    //read sample data into vector
    if (headerWAV.wFormatTag != 1)
    {
        cerr << "Error: not a pcm type" << endl;
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
    strcpy(headerSND.name, sfilename);
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
    fwrite(&headerSND.chk1, sizeof(headerSND.chk1), 1, outfile);
    fwrite(&headerSND.chk2, sizeof(headerSND.chk2), 1, outfile);
    fwrite(&headerSND.name, sizeof(headerSND.name), 1, outfile);
    fwrite(&headerSND.pad, sizeof(headerSND.pad), 1, outfile);
    fwrite(&headerSND.level, sizeof(headerSND.level), 1, outfile);
    fwrite(&headerSND.tune, sizeof(headerSND.tune), 1, outfile);
    fwrite(&headerSND.channels, sizeof(headerSND.channels), 1, outfile);
    fwrite(&headerSND.start, sizeof(headerSND.start), 1, outfile);
    fwrite(&headerSND.loopend, sizeof(headerSND.loopend), 1, outfile);
    fwrite(&headerSND.end, sizeof(headerSND.end), 1, outfile);
    fwrite(&headerSND.looplength, sizeof(headerSND.looplength), 1, outfile);
    fwrite(&headerSND.loopmode, sizeof(headerSND.loopmode), 1, outfile);
    fwrite(&headerSND.beatsinloop, sizeof(headerSND.beatsinloop), 1, outfile);
    fwrite(&headerSND.sample_frequency, sizeof(headerSND.sample_frequency), 1, outfile);

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
    if (headerWAV.nChannels == 2) {
        for (int i = 0; i < length; i += 2) {
            short& samplebuffer = ldata[i];
            fwrite(&samplebuffer, sizeof(samplebuffer), 1, outfile);
        }

        for (int i = 1; i < length; i += 2) {
            short& samplebuffer2 = rdata[i];
            fwrite(&samplebuffer2, sizeof(samplebuffer2), 1, outfile);
        }
    }

    fclose(outfile);
    delete[] buf;
    std::cout << "File converted to: " << filename << endl;
    return filename;

}


static string read_write_wav(const char* fname)
{
    SndfileHandle file, file2;
    SRC_DATA src_data;

    file = SndfileHandle(fname, SFM_READ);

    printf("Opened file '%s'\n", fname);
    printf("    Sample rate : %d\n", file.samplerate());
    printf("    Channels    : %d\n", file.channels());
    //std::cout<< " frames " <<(int)file.frames() << endl;
    int numFrames = file.frames();
    int numChannels = file.channels();
    int numByte = file.frames();
    int frames = numChannels * numByte;
    float* buffer = new float[frames];
    float* buffer_out = new float[frames];

    if (numChannels < 1)	return "error";

    file.read(buffer, numFrames * numChannels);

    double ratio = (double)44100 / (double)file.samplerate();
    int oframes = frames * ratio;
    src_data.data_in = buffer;
    src_data.input_frames = frames;
    src_data.data_out = buffer_out;
    src_data.output_frames = oframes;
    src_data.src_ratio = ratio;

    //convert with libsamplerate
    int error = src_simple(&src_data, SRC_SINC_BEST_QUALITY, numChannels);
    if (error != 0) {
        std::cerr << "Error occured: " << src_strerror(error) << endl;
        return "error";
    }

    int channels = numChannels;
    int format = SF_FORMAT_WAV | SF_FORMAT_PCM_16; //SF_FORMAT_FLOAT SF_FORMAT_PCM_16
    int srate = 44100;

    string newFilename = fname;
    const char* fname2 = fname;
    newFilename = newFilename.substr(0, newFilename.length() - 4);
    newFilename = newFilename.append("_16bit.wav");
    fname2 = newFilename.c_str();
    file2 = SndfileHandle(fname2, SFM_WRITE, format, channels, srate);

    file2.write(buffer_out, oframes * numChannels); //numFrames*numChannels
    //printf("converted file '%s'\n", fname2);
    delete[] buffer_out;
    delete[] buffer;

    return fname2;
}
