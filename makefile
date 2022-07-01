Default:
	g++ -fdiagnostics-color=always -std=c++17 -o3 main.cpp -o ./TextToC.o

WIN64:
	g++ -fdiagnostics-color=always -std=c++17 -o3 main.cpp -o ./TextToC.exe

MACOS:
	g++-11 -fdiagnostics-color=always -std=c++17 -o3 main.cpp -o ./TextToC