cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
# set the project name
project("MPC2000 File Converter")
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
# add the executable
add_executable(snd2wav snd2wav.cpp)
add_executable(wav2snd wav2snd.cpp)
#add_executable(read_snd "read_snd.cpp")
#add_executable(read_wav "read_wav_pcm_16bit.cpp")

add_executable(convert_16bit "converter_wav_16bit.cpp")
#link_directories("${CMAKE_CURRENT_SOURCE_DIR}\\lib\\ libsndfile-1.lib")

target_link_libraries(convert_16bit "${CMAKE_CURRENT_SOURCE_DIR}\\lib\\sndfile.lib")
target_link_libraries(convert_16bit "${CMAKE_CURRENT_SOURCE_DIR}\\lib\\samplerate.lib")

