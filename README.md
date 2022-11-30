# PTM (Programmable Tile Machine)
PTM is an interpreter and runtime environment for an imperative semi-structured programming language called PTML. The runtime aims to be similar in look-and-feel to many BASIC interpreters for early 8-bit computer systems such as the MSX, ZX Spectrum and Atari 800, although the language itself bears more resemblance to a macro-assembler for the Zilog Z80 microprocessor than to BASIC.

The project is developed in old-fashioned C++ and compiled using Microsoft Visual Studio 2019. The target output is a standard Windows desktop executable application called PTM.exe. Upon execution, it looks for a file called "main.ptm" in the same directory. This file must contain PTML source code in plain text which will be interpreted at runtime. See the "Examples" folder for some PTML demo programs.

## Features

- Strictly tile-based display engine
  - Tiles are the most basic unit for drawing anything on the screen
  - Screen resolution of 360x200 pixels, divided into 45 columns by 25 rows of tiles
  - Automatic animation of tile sequences in an independent thread
    
- Tiles
  - 8x8 pixel squares
  - Support for multiple animation frames (tile sequences)
  - Each tile frame contains an index into the global tileset
  - Each tile frame contains two color indexes (foreground and background) into the global palette
  - Can be "transparent" (meaning the background color is not drawn)
  - Can contain arbitrary data in the form of property-value mappings

- Color palette
  - Can store up to 256 colors
  - Fully editable
  - RGB format (0xRRGGBB)
  - Includes 2 default colors (black and white)
  
- Tileset (aka character set)
  - Fully editable
  - Binary format (8 bytes for each tile)
  - Includes 256 default characters partially based on ASCII (see screenshot below for a demo)
  - Expandable, up to 256 pages of 256 tiles each, for a total of 65536 possible tiles
  
- Tile buffers
  - Support for multiple buffers of arbitrary size and position
  - Includes a default buffer covering the entire screen at startup
  - Multiple layers
  - Scrollable viewport
  - Hide or show buffers individually
  - Functions for moving tiles and tile blocks around

- Asynchronous sound playback (single-channel, square wave only)
- File I/O
- Keyboard input
- Variables and constants
- Two basic data types: integers and strings (weakly typed)
- Arrays and basic array functions
- Common string manipulation functions
- Debugging support functions

## External dependencies

- [SDL 2](https://www.libsdl.org/)
- [TileGameLib](https://github.com/FernandoAiresCastello/TileGameToolkit/tree/master/TileGameLibC)
- [CppUtils](https://github.com/FernandoAiresCastello/CppUtils)

## Inspired by

- [MSX-BASIC](https://en.wikipedia.org/wiki/MSX)
- [Zilog Z80 Assembler](https://en.wikipedia.org/wiki/Zilog_Z80)
- [ZX Spectrum](https://en.wikipedia.org/wiki/ZX_Spectrum)
- [Atari 800](https://en.wikipedia.org/wiki/Atari_8-bit_family)
- [ZZT](https://en.wikipedia.org/wiki/ZZT)
- [PICO-8](https://www.lexaloffle.com/pico-8.php)
- [Bitsy](https://github.com/le-doux/bitsy)

## Screenshots

*Default graphics demo (left: color palette; right: tileset)*

![PTM default graphics](https://raw.githubusercontent.com/FernandoAiresCastello/PTM/master/Images/default_gfx.png)

*Example game "Advanced Lawnmower Simulator"*

![Advanced Lawnmower Simulator](https://raw.githubusercontent.com/FernandoAiresCastello/PTM/master/Images/advanced_lawnmower_simulator.png)

*Example game "Invaders"*

![Invaders](https://raw.githubusercontent.com/FernandoAiresCastello/PTM/master/Images/invaders.png)

## List of PTML commands (may be outdated)

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

- NOP - do nothing (used for internal testing)
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
- SKIP - skip rest of loop iteration

Conditional Flow

- IF.EQ - if equals
- IF.NEQ - if not equals
- IF.GT - if greater than
- IF.GTE - if greater or equal to
- IF.LT - if lesser than
- IF.LTE - if lesser or equal to
- IF.KEY - if named key is pressed
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
- BUF.COLS - get buffer width in columns
- BUF.ROWS - get buffer height in rows
- TILE.NEW - begin new tile
- TILE.ADD - add character to tile
- TILE.SETC - set character
- TILE.SETF - set foreground color
- TILE.SETB - set background color
- TILE.COLOR - set fore/back colors
- TILE.GETC - get character
- TILE.GETF - get foreground color
- TILE.GETB - get background color
- TILE.PARSE - parse tile from string
- TILE.STORE - store tile in memory
- TILE.LOAD - load tile from memory
- TILE.SETP - set property
- TILE.GETP - get property
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
- PRINT.ADD - add tile frames to text
- PRINTL - print text then new line
- PRINTR - print raw text (ignore escape sequences)
- PUTC - print a text character
- INK - set text foreground color
- PAPER - set text background color
- COLOR - set text fore/back color
- VSYNC - refresh screen
- BGCOL - set window background color
- TRON - enable tile transparency
- TROFF - disable tile transparency
- WINDOW - override default buffer and window size

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
- INKEY - get name of key pressed
- KCODE - get numerical code of key pressed

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
- FILE.CHK - check if file exists

String Functions

- STR.FMT - get formatted string
- STR.SUB - get substring
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
