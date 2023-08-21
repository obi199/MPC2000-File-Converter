//snd.cpp
//reads a snd file and display content

#include<iostream>
#include <iomanip>
#include <fstream>
#include <stdio.h>
using namespace std;
//Datensatz
struct sndFile{unsigned char i[1];unsigned char j[1]; char name[16] ; char c[1]; unsigned char level[1]; unsigned char tune[1];};

char data[1];

int main(int argc, char *argv[])
{
    if ( argc !=2 )
    {
        cerr << "no filemane declared";
        return 1;
    }


  // struct sndFile* snd_p;
  // snd_p meta = (snd)malloc(sizeof(sndFile));   // header_p points to a header struct that contains the wave file metadata field
  sndFile* snd;
  FILE * inFile = fopen(argv[1],"rb");
  
char isValid[3];
for(int i=0; i<4; i++)
{
  fscanf(inFile,"%c",&isValid[i]);
  cout<<isValid[i]<<endl;
}
// isValid='\0';


}

//   Length   Format              Description
//    ----------------------------------------------------------------------
//       2                         1,4
//      16     ASCII               Filename (without extension, space padded)
//       1                         0
//       1     unsigned char       Level 0...200 (default 100)
//       1     unsigned char       Tune -120...+120
//       1     unsigned char       Channels: 0=Mono 1=Stereo
//       4     unsigned long       Start
//       4     unsigned long       Loop End
//       4     unsigned long       End
//       4     unsigned long       Loop Length
//       1     unsigned char       Loop Mode: 0=Off 1=On
//       1     unsigned char       Beats in loop 1...16 (default 1)
//       2     unsigned short      Sampling frequency (default 44100)