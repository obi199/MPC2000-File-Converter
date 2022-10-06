//reads 16 Bit snd to stream
#include<iostream>
#include<cstdio>//
#include<string>
#include <vector>
#include "byte_utils.cpp"
#include "snd.h"
#include <fstream>
#include <cstdlib>
using namespace std;
/* declare a file pointer */
FILE    *infile;
char    *buf;
long    numbytes;
struct HEADER_SND headerSND;



int main(int argc, char *argv[])
{
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
 
long size;


// result.Parse(buf);
fseek(infile, 0, SEEK_END);
size = ftell(infile);
fseek(infile, 0, SEEK_SET);
fclose(infile);
const size_t bufSize = size;
cout <<"bufsize = "<< bufSize << endl;

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
cout << "sizeOfBuffer=" << sizeof(buf) << endl;
headerSND.chk1 = buf[0];
headerSND.chk2 = buf[1];
getName(headerSND.name,buf,2,18);
headerSND.pad = buf[18];
headerSND.level = buf[19];
headerSND.tune = buf[20];
headerSND.channels = buf[21]; 	
headerSND.start = bytes_2_u_int32(buf[22],buf[23],buf[24],buf[25]);
headerSND.loopend = bytes_2_u_int32(buf[26],buf[27],buf[28],buf[29]);
headerSND.end = bytes_2_u_int32(buf[30],buf[31],buf[32],buf[33]); 
headerSND.looplength = bytes_2_u_int32(buf[34],buf[35],buf[36],buf[37]); 
headerSND.loopmode = (unsigned char)buf[38]; 
headerSND.beatsinloop = (unsigned char)buf[39];
headerSND.sample_frequency = bytes2unsignedShort(buf[40],buf[41]); 

cout<<(int)headerSND.chk1<<endl;
cout<<(int)headerSND.chk2 <<endl;
string name = "";
	
	for (int i = 2; i < 18; i++) {
		if (buf[i] == 0x00) {
			break;
		}
		name.push_back(buf[i]);
	}
	
cout<<"Name="<<name<<endl;
cout<<"space="<<headerSND.pad<<endl;
cout<<"Level="<<(int)headerSND.level<<endl;
cout<<"Tune="<<(int)headerSND.tune<<endl;
cout<<"Channels="<< (int)headerSND.channels<<endl;
cout<<"Start="<< (int)headerSND.start<<endl;
cout<<"loopend="<< (int)headerSND.loopend<<endl;
cout<<"end="<< (int)headerSND.end<<endl;
cout<<"looplength="<< (int)headerSND.looplength<<endl;
cout<<"loopmode="<< (int)headerSND.loopmode<<endl;
cout<<"beatsinloop="<<(int)headerSND.beatsinloop<<endl;

cout<<"Frequency="<<headerSND.sample_frequency<<"	"<<"sizeOf "<< sizeof(headerSND.sample_frequency)<<endl;

vector <short> data;
for (int i = 42; i < size ; i+=2) // i+=2
	{
	uint16_t smpl = bytes2Short(buf[i], buf[i + 1]);
	// x = smpl/ 32768.0;
	data.push_back(smpl);
	}

cout <<"datasize = "<< data.size() << endl;

// signed short smpl = bytes2Short2(buf[42], buf[43]);
//for (int i = 0; i < data.size(); i++) {// i+=2
//	cout << data[i] << endl;

delete [] buf;

return 0; 
}


// # 42 byte header:
// # Length   Format              Description
// # ----------------------------------------------------------------------
// # 0       2                         1,4
// # 2-17    16     ASCII               Filename (without extension, space padded)
// # 18      1                         0
// # 19      1     unsigned char       Level 0...200 (default 100)
// # 20      1     unsigned char       Tune -120...+120
// # 21      1     unsigned char       Channels: 0=Mono 1=Stereo
// # 22-25   4     unsigned long       Start
// # 26-29   4     unsigned long       Loop End
// # 30-33   4     unsigned long       	End
// # 34-37   4     unsigned long       Loop Length
// # 38      1     unsigned char       Loop Mode: 0=Off 1=On
// # 39      1     unsigned char       Beats in loop 1...16 (default 1)
// // # 40-41   2     unsigned short      Sampling frequency (default 44100)

