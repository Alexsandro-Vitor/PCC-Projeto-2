set originalpath="%cd%"
cd "%~dp0"
g++ Main.cc -std=c++17 -o ..\bin\pmt.exe
cd %originalpath%