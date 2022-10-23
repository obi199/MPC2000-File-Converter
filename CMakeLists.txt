cmake_minimum_required(VERSION 3.10)

# set the project name
project("MPC2000 File Converter")

# add the executable
add_executable(snd2wav snd2wav.cpp)
add_executable(wav2snd wav2snd.cpp)
add_executable(read_snd "read_snd.cpp")
add_executable(convert_wav_float "convert_wav_float.cpp")
add_executable(read_wav "read_wav_pcm_16bit.cpp")