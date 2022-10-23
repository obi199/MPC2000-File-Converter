//Work in Progress: trying to convert 32 bit Float 96Khz wav to 441Khz

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
/* declare a file pointer */
FILE    *infile, *outfile;
char    *buffer;
long    numbytes;
struct HEADER_WAV headerWAV;
// struct HEADER_SND headerSND;

int main(int argc, char *argv[])
{
cout<< is_big_endian() <<endl;
//open wav file and read headerWAV
if ( argc !=2 )
    {
        cerr << "no filemane declared"<<endl;
        return 1;
    }	
/* open an existing file for reading */
FILE* infile = fopen(argv[1], "r"); //SNARE_~1.SND SNARE_F.SND

/* quit if the file does not exist */
if(infile == NULL)
    return 1;
 
uint32_t size;
fseek(infile, 0, SEEK_END);
size = ftell(infile);
cout << "size=" << size << endl;

fseek(infile, 0, SEEK_SET);
fread(headerWAV.ckID,sizeof(headerWAV.ckID),1,infile);
fread(&headerWAV.cksize,sizeof(headerWAV.cksize),1,infile);
fread(&headerWAV.WAVEID,sizeof(headerWAV.WAVEID),1,infile);
fread(&headerWAV.ckID2,sizeof(headerWAV.ckID2),1,infile);
fread(&headerWAV.cksize2,sizeof(headerWAV.cksize2),1,infile);
fread(&headerWAV.wFormatTag,sizeof(headerWAV.wFormatTag),1,infile);
fread(&headerWAV.nChannels,sizeof(headerWAV.nChannels),1,infile);
fread(&headerWAV.nSamplesPerSec,sizeof(headerWAV.nSamplesPerSec),1,infile);
fread(&headerWAV.nAvgBytesPerSec,sizeof(headerWAV.nAvgBytesPerSec),1,infile);
fread(&headerWAV.nBlockAlign,sizeof(headerWAV.nBlockAlign),1,infile);
fread(&headerWAV.wBitsPerSample,sizeof(headerWAV.wBitsPerSample),1,infile);
int dwSampleLength;
fseek(infile, 36, SEEK_SET);
fread(&headerWAV.ckID3,sizeof(headerWAV.ckID3),1,infile);
fread(&headerWAV.cksize3,sizeof(headerWAV.cksize3),1,infile);
fread(&dwSampleLength, sizeof(dwSampleLength), 1, infile);

fseek(infile, 48, SEEK_SET);
char ckID4[4];
int ckSize4;
fread(&ckID4, sizeof(ckID4), 1, infile);
fread(&ckSize4, sizeof(ckSize4), 1, infile);

fseek(infile, 72, SEEK_SET);
char ckID5[4];
u_int32_t ckSize5;
fread(&ckID5, sizeof(ckID5), 1, infile);
fread(&ckSize5, sizeof(ckSize5), 1, infile);


//long nsamples = (ckSize5) / (headerWAV.nChannels * headerWAV.nBlockAlign);
//long nsamples = 100;

cout << headerWAV.ckID << endl;
cout << "cksize=" << headerWAV.cksize << endl;
cout << headerWAV.WAVEID<<endl;
cout << headerWAV.ckID2<<endl;
cout << headerWAV.cksize2<<endl;
cout << "formatatTag=" << headerWAV.wFormatTag << endl;
cout << "nChannels=" << headerWAV.nChannels << endl;
cout << "nSamplesPerSec=" << headerWAV.nSamplesPerSec << endl;
cout << "nAvgBytesPerSec=" << headerWAV.nAvgBytesPerSec << endl;
cout << "nBlockAlign=" << headerWAV.nBlockAlign << endl;
cout << "wBitsPerSample=" << headerWAV.wBitsPerSample << endl;
cout << "ckiD3="<<headerWAV.ckID3 << endl;
cout << "cksize3="<<headerWAV.cksize3<<endl;
//cout << "num_samples=" << nsamples << endl;
cout << "dwSampleLength=" << dwSampleLength << endl;
cout << "ckID4=" << ckID4 << endl;
cout << "ckSize4=" << ckSize4 << endl;
cout << "ckID5=" << ckID5 << endl;
cout << "ckSize5=" << ckSize5 << endl;


fseek(infile, 80, SEEK_SET);
vector <float> fdata;
for (int i = 0; i < dwSampleLength; i++){
  float smpl; 
  fread((void*)(&smpl),sizeof(smpl),1,infile);
  fdata.push_back(smpl);
//   cout<<smpl<<endl;  

}

double new_nSamples = dwSampleLength / 2.17687074829932;

cout << std::ceil(new_nSamples) << endl;

fclose(infile);

for (int i = 0; i < 10; i += 2)
{
    short x;
    x = fdata[i] * 32768;
    cout << x << endl;
}

return 0;
}
