# MPC2000-File-Converter

Command Line Tool that converts wave files (Mono/Stereo) to SND (MPC 2000) files. <br/>
To convert wave files to 16bit 44100hz wave use "mpc2000converter" with arguments: <br/>
16bitwav2snd (convert 16bit wav to 16bit 44khz snd)<br/>
anywav2snd (convert any wav to 16bit 44khz snd)<br/>
wav16bit (convert any wav to 16bit 44khz wav)<br/>
snd2wav (convert SND to 16bit 44khz wav)<br/>
Go to the path with files and use either the filename as parameter or "-all" for all files in folder. It adds 16bit_441Mhz to the newly created filenames and copies them in folder "16bit". <br/> 
For the wav conversion you need to install libsndfile and libsamplerate libs: https://github.com/libsndfile. <br/>
<br/>
example: <br/>
mpc2000converter snd2wav -all <br/>
Compile with Cmake...<br/>
Tested in Windows 11 C++17.



