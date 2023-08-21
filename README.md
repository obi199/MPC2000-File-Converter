# MPC2000-File-Converter

Command Line Tool that converts any wave file (Mono/Stereo) to SND (MPC 2000) file. <br/>
To convert wave files to 16bit 44100hz wave use "mpc2000converter" with arguments 16bitwav2snd or anywav2snd. Go to the path with files and use either the filename as argument or -all for all files in folder. It adds 16bit_441Mhz to the newly created filenames and copies them in folder "16bit". <br/> 
For the wav conversion you need to install libsndfile and libsamplerate libs: https://github.com/libsndfile. <br/>
<br/>
Compile with Cmake
Tested in Windows 11 C++17.



