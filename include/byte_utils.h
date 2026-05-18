#ifndef BYTE_UTILS_H
#define BYTE_UTILS_H

#include <string>
using namespace std;

unsigned long bytes2Long(unsigned char, unsigned char, unsigned char, unsigned char);
unsigned short bytes2unsignedShort(unsigned char, unsigned char);
u_int32_t bytes_2_u_int32(unsigned char, unsigned char, unsigned char, unsigned char);
u_int16_t bytes2Short(unsigned char, unsigned char);
string getText(char*, int, int);
void getName(char*, char*, int, int);
bool is_big_endian(void);
string remove_spaces(string);

#endif // BYTE_UTILS_H
