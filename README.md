# MPC2000-File-Converter

Command Line Tool that converts 16bit 44100 Hz wave file (Mono/Stereo) to 16bit SND (MPC 2000) file or back. <br/>
To convert any wave files to 16bit 44100hz use "convert_16bit". Go to path and use filename as argument or -f  for all files in folder. It adds 16bit_441Mhz to the newly created filenames. <br/> 
For the 16bit wav conversion u need to install libsndfile and libsamplerate Libraries: https://github.com/libsndfile. <br/>
For SND conversion type: "wav2snd pathToFile" "snd2wav pathToFile". Tested with MPC 2000. <br/> 
Files can be compiled with Cmake:  wav2snd.cpp, snd2wav.cpp,  convert_16bit.cpp source files. <br/>



