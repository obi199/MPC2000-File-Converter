// SND file header format

#include <string>
#include <stdint.h>
using namespace std;
typedef uint32_t u_int32_t;
typedef uint16_t u_int16_t;

struct HEADER_SND {
	unsigned char chk1;						// check values 1,4
	unsigned char chk2;
	char name[16];
	unsigned char pad;
	unsigned char level;
	unsigned char tune;
	unsigned char channels; 	
	u_int32_t start;
	u_int32_t loopend;
	u_int32_t end; 
	u_int32_t looplength; 
	unsigned char loopmode; 
	unsigned char beatsinloop;
	u_int16_t sample_frequency; 	//Sampling frequency (default 44100)
						
};

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