//reads 16 Bit wav to stream
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

// result.Parse(buf);
fseek(infile, 0, SEEK_END);
size = ftell(infile);
fseek(infile, 0, SEEK_SET);

//fgets(buf, bufSize, infile);
fclose(infile);
const size_t bufSize = size;
char* buf = new char[bufSize];

char* ptr;
ptr = argv[1];
ifstream sndFile(ptr, ios::in | ios::binary);
if (!sndFile.is_open())
{
    cerr << "Fehler beim Öffnen der Datei" << endl;
    exit(1);
}
sndFile.read(buf, bufSize);
sndFile.close();

cout<<size<<endl;
cout<<"Size data "<< size-44<<endl;

getName(headerWAV.ckID,buf,0,4);
// headerWAV.ckID = getText(buf, 0, 4);
headerWAV.cksize = bytes_2_u_int32(buf[4], buf[5], buf[6],buf[7]);
getName(headerWAV.WAVEID ,buf, 8, 12);
getName(headerWAV.ckID2,buf, 12, 16);
headerWAV.cksize2 = bytes_2_u_int32(buf[16], buf[17], buf[18],buf[19]);
headerWAV.wFormatTag = bytes2unsignedShort(buf[20], buf[21]);
headerWAV.nChannels = bytes2unsignedShort(buf[22], buf[23]);
headerWAV.nSamplesPerSec = bytes_2_u_int32(buf[24], buf[25],buf[26], buf[27]); //buf[26], buf[27]);
headerWAV.nAvgBytesPerSec = bytes_2_u_int32(buf[28], buf[29],buf[30], buf[31]);//(buf[28], buf[29],buf[30], buf[31]);
headerWAV.nBlockAlign = bytes2unsignedShort(buf[32], buf[33]);
headerWAV.wBitsPerSample = bytes2unsignedShort(buf[34], buf[35]);
getName(headerWAV.ckID3,buf, 36, 40);
headerWAV.cksize3 = bytes_2_u_int32(buf[40], buf[41], buf[42],buf[43]);

string ckid1 = getText(headerWAV.ckID, 8, 12);
cout<<ckid1<<endl;
cout<<sizeof(headerWAV)<<endl;
cout<<"ckID="<<headerWAV.ckID<<"  "<<sizeof(headerWAV.ckID)<<endl;
cout<<"cksize="<<headerWAV.cksize<<endl;
cout<<"WAVEID="<<headerWAV.WAVEID<<"  "<<sizeof(headerWAV.WAVEID)<<endl;
cout<<"ckID2="<<headerWAV.ckID2<<endl;
cout<<"cksize2="<<headerWAV.cksize2<<endl;
cout<<"wFormatTag="<<headerWAV.wFormatTag<<endl;
cout<<"nChannels="<<headerWAV.nChannels<<endl;
cout<<"nSamplesPerSec="<<headerWAV.nSamplesPerSec<<endl;
cout<<"nAvgBytesPerSec="<<headerWAV.nAvgBytesPerSec<<endl;
cout<<"nBlockAlign="<<headerWAV.nBlockAlign<<endl;
cout<<"wBitsPerSample="<<headerWAV.wBitsPerSample<<endl;
cout<<"ckID3="<<headerWAV.ckID3<<endl;
cout<<"cksize3="<<headerWAV.cksize3<<endl;
cout<<"HeaderSize="<<size - headerWAV.cksize3<<endl;
if (headerWAV.wFormatTag != 1)
    {
    cerr << "Error: not a pcm type"<<endl;
    return 1;
    }

vector <short> data; 
for (int i = 44; i < size; i+=2) // i+=2
	{
    uint16_t smpl = bytes2Short(buf[i], buf[i + 1]);
	data.push_back(smpl);
	}

cout << data.size()<<endl;
for (int i = 0; i <= 10 ; i++)
	cout << data[i] << endl;

delete[] buf;
return 0;
}
