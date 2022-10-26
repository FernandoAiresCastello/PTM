# PTM (Programmable Tile Machine)
PTM is an interpreter and runtime environment for a low-level imperative programming language called PTML. It aims to be similar in style to many BASIC interpreters for early 8-bit computer systems such as the MSX, ZX Spectrum and Atari 800. See PTML command list below for an overview.

It features tile-based graphics in a resolution of 360x200 pixels (divided into 45 columns by 25 rows of tiles) with an indexed color palette (2 colors per tile), simple square wave audio, file I/O, keyboard input, one-dimensional arrays, string manipulation and debugging functions. The environment comes with a default character set with 256 predefined tiles based on ASCII and a default color palette (see screenshots below for a demo). The tileset is fully editable and can be expanded in pages of 256 tiles each, for a total of 65536 possible tiles. The color palette is also fully editable but is limited to 256 colors. The display engine also supports multiple overlapping and movable tile buffers of arbitrary size, with multiple layers and individually scrollable viewports. Tiles can contain multiple frames of animation and the system uses a separate thread to automatically cycle through all frames for all tiles on the screen.

The output of this project is a standard Windows desktop executable application called PTM.exe. Upon execution, it looks for a file called "main.ptm" in the same directory. This file must contain PTML source code in plain text which will be interpreted at runtime. See the "Examples" folder for some PTML demo programs.

PTM is powered by the following libraries:

- [SDL2](https://www.libsdl.org/)
- [TileGameLib](https://github.com/FernandoAiresCastello/TileGameToolkit/tree/master/TileGameLibC)
- [CppUtils](https://github.com/FernandoAiresCastello/CppUtils)

And is inspired by:

- [MSX-BASIC](https://en.wikipedia.org/wiki/MSX)
- [ZX Spectrum](https://en.wikipedia.org/wiki/ZX_Spectrum)
- [Atari 800](https://en.wikipedia.org/wiki/Atari_8-bit_family)
- [PICO-8](https://www.lexaloffle.com/pico-8.php)
- [Bitsy](https://github.com/le-doux/bitsy)

### Screenshots:

![PTM default graphics](https://github.com/FernandoAiresCastello/PTM/blob/master/Images/default_gfx.png?raw=true)

"Advanced Lawnmower Simulator" game included in the examples

![Advanced Lawnmower Simulator](https://github.com/FernandoAiresCastello/PTM/blob/master/Images/adv_lawn_sim.jpg?raw=true)

### List of PTML commands (may be outdated):

Variables and Arrays

- VAR - create a variable
- DEF - define a constant
- ARR.NEW - create an array
- ARR.PUSH - add element to array
- ARR.LEN - get array length
- ARR.SET - set array element
- ARR.ERASE - remove array element
- ARR.CLR - remove all array elements
- ARR.COPY - copy array
- ARR.FOR - start array loop

System

- NOP - do nothing (used for testing)
- INCL - include a PTML source file
- EXIT - exit and close window
- RESET - restart machine
- TITLE - set window title
- CYCLES - get current cycle
- HALT - end program but keep window open
- PAUSE - pause execution

Branching

- GOTO - branch to label
- CALL - call label
- RET - return from label

Loops

- FOR - start a loop
- NEXT - end a loop
- BRK - break from loop
- CONT - skip loop iteration

Conditional Flow

- IF.EQ - if equals
- IF.NEQ - if not equals
- IF.GT - if greater than
- IF.GTE - if greater or equal to
- IF.LT - if lesser than
- IF.LTE - if lesser or equal to
- IF.STR.EQ - if strings equal
- IF.STR.NEQ - if strings not equal
- ENDIF - terminate if block

Math

- RND - get random number
- INC - increment number
- DEC - decrement number
- ADD - add to number
- SUB - subtract from number
- MUL - multiply number

Graphics

- BUF.NEW - create new tile buffer
- BUF.SEL - select current buffer
- BUF.SHOW - show current buffer
- BUF.HIDE - hide current buffer
- BUF.VIEW - set viewport
- BUF.SCRL - scroll viewport
- BUF.W - get buffer width in columns
- BUF.H - get buffer height in rows
- TILE.NEW - begin new tile
- TILE.ADD - add character to tile
- TILE.CH - set character
- TILE.INK - set foreground color
- TILE.PAPER - set background color
- TILE.COLOR - set fore/back colors
- TILE.PARSE - parse tile from string
- TILE.STORE - store tile in memory
- TILE.LOAD - load tile from memory
- TILE.PROP - set property
- TILE.PGET - get property
- LAYER - select buffer layer
- LOCATE - set cursor column and row
- CSR.X - set cursor column
- CSR.Y - set cursor row
- CSR.MOV - move cursor
- CSR.R - move cursor right
- CSR.L - move cursor left
- CSR.U - move cursor up
- CSR.D - move cursor down
- CSR.UR - move cursor up & right
- CSR.UL - move cursor up & left
- CSR.DR - move cursor down & right
- CSR.DL - move cursor down & left
- PUT - put tile at cursor position
- GET - get tile at cursor position
- DEL - delete tile at cursor position
- PUT.R - put tile then move right
- PUT.L - put tile then move left
- PUT.U - put tile then move up
- PUT.D - put tile then move down
- PUT.UR - put tile then move up & right
- PUT.UL - put tile then move up & left
- PUT.DR - put tile then move down & right
- PUT.DL - put tile then move down & left
- RECT - fill a rectangle with tiles
- FILL - fill the entire buffer
- CLS - delete all tiles in all layers
- CLL - delete all tiles in a single layer
- CLR - delete all tiles inside rectangle
- MOV - move tile
- MOVB - move block of tiles
- DRAW - draw tiles on a path
- PRINT - print text
- PRINT.ADD - add tiles to text
- PRINTL - print text then new line
- PUTC - print a text character
- INK - set text foreground color
- PAPER - set text background color
- COLOR - set text fore/back color
- VSYNC - refresh screen
- BGCOL - set window background color
- TRON - enable tile transparency
- TROFF - disable tile transparency

Tileset Management

- CHR - set tile pattern
- CHRS - set tile pattern
- CHR.LEN - get tileset size
- CHR.GETBS - get tile as binary string
- CHR.SETBS - parse tile from binary string
- CHR.NEWPG - create new tileset page

Palette Management

- PAL - set color RGB
- PAL.SETR - set red component
- PAL.SETG - set green component
- PAL.SETB - set blue component
- PAL.GET - get color RGB
- PAL.GETR - get red component
- PAL.GETG - get green component
- PAL.GETB - get blue component
- PAL.LEN - get palette size
- PAL.CLR - clear palette

Keyboard Input

- INPUT - read text input from keyboard
- INKEY - get key pressed
- XON - enable exit with ESC key
- XOFF - disable exit with ESC key

Sound

- PLAY - play music string
- LPLAY - loop music string
- SOUND - play sound
- VOL - set audio volume
- QUIET - stop all sounds

File I/O

- CLOAD - read file into string
- BLOAD - read file into byte array
- CSAVE - write string to file
- BSAVE - write byte array to file

String Functions

- STR.FMT - get formatted string
- STR.SUBST - get substring
- STR.LEN - get string length
- STR.REPT - get repeated string
- STR.CAT - get concatenated strings
- STR.SPLIT - split string into array
- STR.TRIM - remove leading & trailing space
- STR.UCASE - get uppercase string
- STR.LCASE - get lowercase string
- STR.REPL - replace substrings
- STR.AT - get character at index
- STR.IX - get index of character
- STR.START - check if string starts with
- STR.END - check if string ends with
- STR.HAS - check if string contains

Debugging Support

- DBG.BRK - for PTM developers only
- DBG.DUMP - write machine state to text file
- DBG.PERF - enable performance monitor
- DBG.MSG - show message box
