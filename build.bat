set "PATH=%cd%/mingw/bin"
%cd%/mingw/bin/gcc -static-libgcc api.c main.c -o "output/ptm.exe" -lmingw32 -lSDL2main -lSDL2 -mwindows
