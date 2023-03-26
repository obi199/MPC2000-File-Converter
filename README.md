# MPC2000-File-Converter

Command Line Tool that converts any wave file (Mono/Stereo) to SND (MPC 2000) file. <br/>
To convert wave files to 16bit 44100hz wave use "convert_wav_16bit". Go to the path with files and use either the filename as argument or -f  for all files in folder. It adds 16bit_441Mhz to the newly created filenames and copies them in folder "16bit". <br/> 
For the 16bit wav conversion you need to install libsndfile and libsamplerate libs: https://github.com/libsndfile. <br/>
For SND conversion use: "wav2snd pathToFile" or "snd2wav pathToFile" or for all files in folder user "-f" as argument. Tested with MPC 2000. <br/> 
Files can be compiled with Cmake:  wav2snd.cpp, snd2wav.cpp,  converter_wav_16bit.cpp source files. <br/>
Tested in Windows 10 c++17.



