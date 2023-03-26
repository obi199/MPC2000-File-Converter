//reads 16 Bit wav to stream
#include "include/wav.h"
#include "include/snd.h"
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
FILE* infile, * outfile;
char* buffer;
long    numbytes;
struct HEADER_WAV headerWAV;
// struct HEADER_SND headerSND;

int main(int argc, char* argv[])
{
    cout << is_big_endian() << endl;
    //open wav file and read headerWAV
    if (argc != 2)
    {
        cerr << "no filemane declared" << endl;
        return 1;
    }
    /* open an existing file for reading */
    FILE* infile = fopen(argv[1], "r"); //SNARE_~1.SND SNARE_F.SND

    /* quit if the file does not exist */
    if (infile == NULL)
        return 1;

    uint32_t size;
    // result.Parse(buf);
    fseek(infile, 0, SEEK_END);
    size = ftell(infile);
    fseek(infile, 0, SEEK_SET);
    fread(headerWAV.ckID, sizeof(headerWAV.ckID), 1, infile);
    fread(&headerWAV.cksize, sizeof(headerWAV.cksize), 1, infile);
    fread(&headerWAV.WAVEID, sizeof(headerWAV.WAVEID), 1, infile);
    fread(&headerWAV.ckID2, sizeof(headerWAV.ckID2), 1, infile);
    fread(&headerWAV.cksize2, sizeof(headerWAV.cksize2), 1, infile);
    fread(&headerWAV.wFormatTag, sizeof(headerWAV.wFormatTag), 1, infile);
    fread(&headerWAV.nChannels, sizeof(headerWAV.nChannels), 1, infile);
    fread(&headerWAV.nSamplesPerSec, sizeof(headerWAV.nSamplesPerSec), 1, infile);
    fread(&headerWAV.nAvgBytesPerSec, sizeof(headerWAV.nAvgBytesPerSec), 1, infile);
    fread(&headerWAV.nBlockAlign, sizeof(headerWAV.nBlockAlign), 1, infile);
    fread(&headerWAV.wBitsPerSample, sizeof(headerWAV.wBitsPerSample), 1, infile);
    fread(&headerWAV.ckID3, sizeof(headerWAV.ckID3), 1, infile);
    fread(&headerWAV.cksize3, sizeof(headerWAV.cksize3), 1, infile);
    long nsamples = (headerWAV.cksize3) / (headerWAV.nChannels * headerWAV.nBlockAlign);

    cout << "size=" << size << endl;
    cout << headerWAV.ckID << endl;
    cout << headerWAV.cksize << endl;
    cout << headerWAV.WAVEID << endl;
    cout << headerWAV.ckID2 << endl;
    cout << headerWAV.cksize2 << endl;
    cout << headerWAV.wFormatTag << endl;
    cout << headerWAV.nChannels << endl;
    cout << headerWAV.nSamplesPerSec << endl;
    cout << headerWAV.nAvgBytesPerSec << endl;
    cout << headerWAV.nBlockAlign << endl;
    cout << headerWAV.wBitsPerSample << endl;
    cout << headerWAV.ckID3 << endl;
    cout << headerWAV.cksize3 << endl;
    cout <<"num_samples="<< nsamples << endl;


    fseek(infile, 44, SEEK_SET);
    vector <short> data;
    for (int i = 0; i < nsamples; i++) {
        short smpl = 0;
        fread((void*)(&smpl), sizeof(smpl), 1, infile);
        data.push_back(smpl);
        //   cout<<smpl<<endl;  
    }


    for (int i = 0; i <= 100; i++)
        cout << data[i] << endl;

    return 0;
}
