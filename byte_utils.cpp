#include <string>
#include <vector>
using namespace std;
typedef uint32_t u_int32_t;
typedef uint16_t u_int16_t;

unsigned long bytes2Long(char byte1, char byte2, char byte3, char byte4)
{
	unsigned int combined = 0; // clear it out
	combined = (byte4<<24) | (byte3<<16) | (byte2<<8) | (byte1);
	return combined;
	
}

unsigned short bytes2unsignedShort(char byte1, char byte2)
{
	unsigned short combined = 0;
	combined = (byte2 << 8) | (byte1) ;
	return combined;
	
}

u_int32_t bytes_2_u_int32(char byte1, char byte2, char byte3, char byte4)
{
	u_int32_t combined = 0; // clear it out
	combined = (byte4<<24) | (byte3<<16)  | ((byte2<<8) &  0xff00) | (byte1 & 0xff );
	// combined = (byte4<<24) | (byte3<<16)  | (byte2<<8) | (byte1);
	// combined = (byte1) | ((byte2>>8) & 0x00ff) | ((byte3>>16)& 0x0000ff00) | ((byte4 >>24)& 0x000000ff);
	return combined;
	
}

// char* short2bytes(short s)
// {
// 	char c[2];
// 	c[1] = (s>>8) & 0xFF;
// 	c[0] = (s) & 0xFF;
// 	return c[2];
	
// }


// vector<char> short2bytes2(unsigned short n) {
// // 	//little endian
// 	auto res = vector<char>(2);
// 	res[1] = (n >> 8);
// 	res[0] = n & 0xFF;
// 	return res;
// }

u_int16_t bytes2Short(char byte1, char byte2)
{
	 u_int16_t combined = 0;
	 combined = (byte1 & 0xff | ((int)byte2 << 8) & 0xff00 );
	 return combined;
	
}

string getText(char buf[], int begin, int end)
{
	string text = "";
		
		for (int i = begin; i < end; i++)
		{
			if (buf[i] == 0x00) {
				break;
			}
			text.push_back(buf[i]);
		}
	return text;	
}


void getName(char* name, char* buf, int begin, int end)
{
	int y=0;
		for (int i = begin; i < end; i++)
		{
			
			if (buf[i] == 0x00) {
				break;
			}
			name[y] = buf[i];
			// cout<<name[y]<<endl;
			y++;
		}
}


bool is_big_endian(void)
{
    union {
        uint32_t i;
        char c[4];
    } bint = {0x01020304};

    return bint.c[0] == 1;
}

string remove_spaces(string str1)
{
	
	str1.erase(std::remove_if(str1.begin(),
		str1.end(),
		[](unsigned char x) {return std::isspace(x); }),
		str1.end());
	
	return str1;
}