# PTM (Programmable Tile Machine)
PTM is an interpreter and runtime environment for a low-level imperative programming language called PTML. It aims to be similar in style to many BASIC interpreters for early 8-bit computer systems such as the MSX, ZX Spectrum and Atari 800.

It features tile-based graphics in a resolution of 360x200 pixels (divided into 45 columns by 25 rows of tiles) with an indexed color palette (2 colors per tile), simple square wave audio, file I/O, keyboard input, one-dimensional arrays, string manipulation and debugging functions. The environment comes with a default character set with 256 predefined tiles based on ASCII and a default color palette (see screenshots below for a demo). The tileset is fully editable and can be expanded in pages of 256 tiles each, for a total of 65536 possible tiles. The color palette is also fully editable but is limited to 256 colors. The display engine also supports multiple overlapping and movable tile buffers of arbitrary size, with multiple layers and individually scrollable viewports.

The output of this project is a standard Windows desktop executable application called PTM.exe. Upon execution, it looks for a file called "main.ptm" in the same directory. This file must contain PTML source code in plain text which will be interpreted at runtime. See the "Examples" folder for some PTML demo programs.

This project is powered by the following libraries:

- [SDL2](https://www.libsdl.org/)
- [TileGameLib](https://github.com/FernandoAiresCastello/TileGameToolkit/tree/master/TileGameLibC)
- [CppUtils](https://github.com/FernandoAiresCastello/CppUtils)

Inspired by:

- [MSX-BASIC](https://en.wikipedia.org/wiki/MSX)
- [ZX Spectrum](https://en.wikipedia.org/wiki/ZX_Spectrum)
- [Atari 800](https://en.wikipedia.org/wiki/Atari_8-bit_family)
- [PICO-8](https://www.lexaloffle.com/pico-8.php)
- [Bitsy](https://github.com/le-doux/bitsy)

Screenshots:

![PTM default graphics](https://github.com/FernandoAiresCastello/PTM/blob/master/Images/default_gfx.png?raw=true)
