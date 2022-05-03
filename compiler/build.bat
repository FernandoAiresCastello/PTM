set "PATH=%cd%/mingw/bin"
%cd%/mingw/bin/gcc api.c main.c -o "%cd%/../output/ptm.exe" -lmingw32 -lSDL2main -lSDL2 -mwindows
