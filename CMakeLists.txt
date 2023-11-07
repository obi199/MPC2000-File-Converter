cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
# set the project name
project("MPC2000 File Converter")
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

add_subdirectory(include) 
# add the executable
add_executable(mpc2000converter main.cpp)

#add_executable(wav16bit converter_wav_16bit.cpp)

target_link_libraries(mpc2000converter myLib "${CMAKE_CURRENT_SOURCE_DIR}\\lib\\sndfile.lib" "${CMAKE_CURRENT_SOURCE_DIR}\\lib\\samplerate.lib")
target_include_directories(mpc2000converter PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}\\include\\")

#target_link_libraries(wav16bit myLib "${CMAKE_CURRENT_SOURCE_DIR}\\lib\\sndfile.lib" "${CMAKE_CURRENT_SOURCE_DIR}\\lib\\samplerate.lib")
#target_include_directories(wav16bit PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}\\include\\")