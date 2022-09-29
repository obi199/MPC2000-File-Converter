// WAVE file header format

#include <string>
#include <cstring>
using namespace std;
typedef uint32_t u_int32_t;
typedef uint16_t u_int16_t;

struct HEADER_WAV {
	char ckID[4];						        // RIFF string
	u_int32_t cksize	;				        // overall size of file in bytes
	char WAVEID[4];						        // WAVE string
	char ckID2[4];			                    // fmt string with trailing null char
	u_int32_t cksize2;				        // length of the format data
	u_int16_t wFormatTag;					// format type. 1-PCM, 3- IEEE float, 6 - 8bit A law, 7 - 8bit mu law
	u_int16_t nChannels;					// no.of channels
	// unsigned int sample_rate;					// sampling rate (blocks per second)
	u_int32_t nSamplesPerSec ;				// SampleRate * NumChannels * BitsPerSample/8
	u_int32_t nAvgBytesPerSec;				// NumChannels * BitsPerSample/8
    u_int16_t nBlockAlign;                 // byte per sample (ByteSample)
	u_int16_t wBitsPerSample;				// bits per sample
	char ckID3[4];		                        // DATA string 
	u_int32_t cksize3;						// NumSamples * NumChannels * ByteSample
};

