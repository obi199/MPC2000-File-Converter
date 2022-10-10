//converts 16 Bit SND 44100hz to 16bit WAV File Format

#include "wav.h"
#include "snd.h"
#include "byte_utils.cpp"
#include <iostream>
#include <cstdio>//
#include <string>
#include <vector>
#include <stdint.h>
#include <cstring>
#include <fstream>

using namespace std;
FILE    *infile, *outfile;
char    *buffer;
long    numbytes;
struct HEADER_WAV headerWAV;
struct HEADER_SND headerSND;

int main(int argc, char *argv[])
{
cout << "Copyright (C) 2022 obi199" << endl;

//open wav file and read headerWAV
if ( argc !=2 )
    {
        cerr << "no filemane declared"<<endl;
        return 1;
    }	
/* open an existing file for reading */
FILE* infile = fopen(argv[1], "r"); 

if(infile == NULL)
    return 1;
uint32_t size;
fseek(infile, 0, SEEK_END);
size = ftell(infile);
fseek(infile, 0, SEEK_SET);
const size_t bufSize = size ;

fclose(infile);
char* buf = new char[bufSize];

char* ptr;
ptr = argv[1];
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
    return 1;
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
return 0; 
}

