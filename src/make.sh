thispath="$(dirname "$0")"
cd "$thispath"
g++ Main.cc -std=c++17 -o ../bin/pmt.exe
cd ~-
echo "Compilação terminada"