# PTM - Programmable Tile Machine (version 0.1b)

## Please note

This was the very first beta version released on Itch.io as part of the [Tool Jam 3](https://itch.io/jam/the-tool-jam-3). It is no longer possible to compile this version of the source code due to extensive breaking changes in some of its dependencies (mostly TileGameLib) so it has been abandoned in favor of version 0.2b which has been rebuilt in a separate project (see https://github.com/FernandoAiresCastello/PTM/tree/master/v0.2b).

## About
	
PTM (Programmable Tile Machine) is a "pseudo-8-bit fantasy computer" that you can program using an imperative, semi-structured, low-level programming language called PTML. The system aims to be similar in look-and-feel to some early 8-bit computer systems such as the MSX, ZX Spectrum and Atari 800. Also inspired by the modern game engines Bitsy and PICO-8.

## How to write programs for the PTM

To write programs in PTML you just need a plain-text editor like Notepad or any other. The machine expects PTML program files to have the extension ".ptm" by default.

## How to run programs

The file "PTM.exe" is the machine executable itself. If you simply double-click this file, it specifically looks for a file called "main.ptm" in the same directory. This file must contain PTML source code in plain text which will be interpreted at runtime. Alternatively, you can pass the name of a PTML program file as an argument to this executable via the command prompt and it will load then run the specified program. Another way to load and run programs is to drag-and-drop the program file onto PTM.exe.

The file "PTM-Launcher.exe" is a simple tool that shows a window with a list of all ".ptm" files in the same directory. Simply double-click a file to start the machine with the selected program.

## PTM & PTML specifications
	
Strictly tile-based display engine

	- Tiles are the most basic unit for drawing anything on the screen
	- Screen resolution of 360x200 pixels, divided into 45 columns by 25 rows of tiles
	- Automatic animation of tile sequences in an independent thread

Tiles

	- 8x8 pixel squares
	- Support for automatic animations with multiple animation frames (tile sequences)
	- Each tile frame contains an index into the global tileset
	- Each tile frame contains two color indexes (foreground and background) into the global palette
	- Each tile can be "transparent" (meaning the background color is not drawn)
	- Each tile can contain arbitrary data in the form of property-value mappings

Color palette

	- Can store up to 256 colors
	- Fully editable
	- RGB format (0xRRGGBB)
	- By default only includes 2 basic colors (black and white)

Tileset (aka character set)

	- Fully editable
	- Binary format (8 bytes for each tile)
	- By default includes 256 characters partially based on ASCII
	- Expandable, up to 256 pages of 256 tiles each, for a total of 65536 possible tiles

Tile buffers

	- Support for multiple buffers of arbitrary size and position
	- Includes a default buffer covering the entire screen at startup
	- Multiple layers
	- Scrollable viewport
	- Hide or show buffers individually
	- Functions for moving tiles and tile blocks around
	
Other features

	- Asynchronous sound playback in single-channel, square wave only, MML-style (Music Macro Language)
	- Read/write files
	- Detect keyboard input
	- Support for simple variables and constants
	- Two data types only: integers and strings (weakly typed)
	- Arrays and basic array functions
	- Common string manipulation functions
	- Debugging support

## PTML commands

NOP
Stay idle for 1 machine cycle

INCL filename
Include another PTML file (only valid into the "main.ptm" program file)

EXIT
Terminate program and close window

HALT
Terminate program but keep window open

RESET
Restart machine and program

TITLE "text"
Set the text that appears as the window title

CYCLES x
Store in the variable x the number of cycles elapsed since the machine started

GOTO label
Transfer execution to code starting from label

IF.GOTO x, y, label
Transfer execution to code starting from label only if x equals y

CALL label
Transfer execution to subroutine starting from label

IF.CALL x, y, label
Transfer execution to subroutine starting from label only if x equals y

RET
Return from subroutine

PAUSE x
Pause program execution for x cycles

FOR x, first, last
FOR x, first, last, step
Begin a loop using variable x, starting at first value until last value. The "step" is optional and indicates whether to "skip" value by that amount (step defaults to 1 if not specified)

NEXT
Mark the end of a loop iteration

BRK
Exit a loop prematurely

SKIP
Skip the current loop iteration

IF.EQ x, y
Begin a conditional block that will only be executed if x equals y

IF.NEQ x, y
Begin a conditional block that will only be executed if x is not equal to y

IF.GT x, y
Begin a conditional block that will only be executed if x is greater than y

IF.GTE x, y
Begin a conditional block that will only be executed if x is greater than or equal to y

IF.LT x, y
Begin a conditional block that will only be executed if x is lesser than y

IF.LTE x, y
Begin a conditional block that will only be executed if x is lesser than or equal to y

IF.KEY keyname
Begin a conditional block that will only be executed if the specified key is pressed

ENDIF
Mark the end of a conditional block

VAR name, value
Define or redefine a variable

DEF name, value
Define a constant

ARR.NEW name
ARR.NEW name, initial_size
Create a new array with an optional initial size

ARR.PUSH name, value
Add a value to an array

ARR.SET name[index], value
Set value in the array at the specified index

ARR.LEN name, x
Store in x the length of the specified array

ARR.ERASE name, index
Remove from the array the item at the specified index. This reduces the size of the array

ARR.CLR name
Remove all items from the array

ARR.COPY src, dest
Make array dest equal to array src

ARR.FOR name, iteration_var
Begin a loop over the specified array. The variable iteration_var will store the value at the current index of the array. The end of the loop iteration must be marked with the "NEXT" command

RND x, min, max
Store in x a random number between min and max, inclusive

INC x
Increment variable x by 1

DEC x
Decrement variable x by 1

ADD result, x, y
Add x to y and store result

SUB result, x, y
Subtract x from y and store result

MUL result, x, y
Multiply x by y and store result

DIV result, x, y
Divide x by y and store quotient

DIVR remainder, x, y
Divide x by y and store remainder

POW result, base, power
Perform exponentiation and store result

SQRT result, x
Calculate square root of x and store result

TILE.NEW
Clear all frames from the working tile (start with an "empty" tile)

TILE.NEW tile_index, fore_color_index, back_color_index
Define the working tile with a single frame. The tile frame will contain the specified tile index (from the tileset), foreground and background color indices (from the color palette)

TILE.ADD tile_index, fore_color_index, back_color_index
Append a new animation frame to the working tile. The new frame will contain the specified tile index (from the tileset), foreground and background color indices (from the color palette)

TILE.SETC frame_index, tile_index
Set the tile index of the specified frame in the working tile

TILE.SETF frame_index, color_index
Set the foreground color index of the specified frame in the working tile

TILE.SETB frame_index, color_index
Set the background color index of the specified frame in the working tile

TILE.COLOR frame_index, fore_color_index, back_color_index
Set the foreground and background color indices of the specified frame in the working tile

TILE.GETC x, frame_index
Store in x the tile index of the specified frame in the working tile

TILE.GETF x, frame_index
Store in x the foreground color index of the specified frame in the working tile

TILE.GETB x, frame_index
Store in x the background color index of the specified frame in the working tile

TILE.PARSE format
Define the working tile using a special format string. The syntax is: 
"tile_index,foreground_color_index,background_color_index;"
Repeat for each animation frame in the tile

TILE.STORE x
Store in x the working tile

TILE.LOAD x
Load working tile from x

TILE.SETP property, value
Set property with the specified value in the working tile

TILE.GETP x, property
Store in x the value of the specified property from the working tile

LAYER index
Select the specified index in the current tilebuffer

LOCATE column, row
Set the tilebuffer cursor at the specified column and row

CSR.X column
Set the tilebuffer cursor at the specified column

CSR.Y row
Set the tilebuffer cursor at the specified row

CSR.GETX variable
Store in variable the column where the tilebuffer cursor is currently located

CSR.GETY variable
Store in variable the row where the tilebuffer cursor is currently located

CSR.MOV horizontal_distance, vertical_distance
Move the tilebuffer cursor by the specified distance

CSR.R
CSR.R distance
Move the tilebuffer cursor to the right by the specified distance, or by 1 if not specified

CSR.L
CSR.L distance
Move the tilebuffer cursor to the left by the specified distance, or by 1 if not specified

CSR.U
CSR.U distance
Move the tilebuffer cursor up by the specified distance, or by 1 if not specified

CSR.D
CSR.D distance
Move the tilebuffer cursor down by the specified distance, or by 1 if not specified

CSR.UR
CSR.UR distance
Move the tilebuffer cursor up and right by the specified distance, or by 1 if not specified

CSR.UL
CSR.UL distance
Move the tilebuffer cursor up and left by the specified distance, or by 1 if not specified

CSR.DR
CSR.DR distance
Move the tilebuffer cursor down and right by the specified distance, or by 1 if not specified

CSR.DL
CSR.DL distance
Move the tilebuffer cursor down and left by the specified distance, or by 1 if not specified

BUF.NEW name, cols, rows, layers
Create a new tilebuffer with the specified name and dimensions

BUF.SEL name
Select the specified tilebuffer

BUF.SHOW
Make the selected tilebuffer visible

BUF.HIDE
Make the selected tilebuffer invisible

BUF.VIEW column, row, width, height
Set position and size of the viewport of the selected tilebuffer

BUF.SCRL horizontal_distance, vertical_distance
Scroll the viewport of the selected tilebuffer

BUF.COLS x
Store in x the width (in tile columns) of the selected tilebuffer

BUF.ROWS x
Store in x the height (in tile rows) of the selected tilebuffer

PUT
Put a copy of the working tile at the current cursor position in the selected tilebuffer

GET
Get a copy of the tile at the current cursor position in the selected tilebuffer and set it as the working tile

DEL
Delete the tile at the current cursor position in the selected tilebuffer

PUT.R
PUT.R distance
Same as the PUT command, but also moves the cursor right by the specified distance

PUT.L
PUT.L distance
Same as the PUT command, but also moves the cursor left by the specified distance

PUT.U
PUT.U distance
Same as the PUT command, but also moves the cursor up by the specified distance

PUT.D
PUT.D distance
Same as the PUT command, but also moves the cursor down by the specified distance

PUT.UR
PUT.UR distance
Same as the PUT command, but also moves the cursor up and right by the specified distance

PUT.UL
PUT.UL distance
Same as the PUT command, but also moves the cursor up and left by the specified distance

PUT.DR
PUT.DR distance
Same as the PUT command, but also moves the cursor down and right by the specified distance

PUT.DL
PUT.DL distance
Same as the PUT command, but also moves the cursor down and left by the specified distance

RECT column, row, width, height
Fill a rectangle in the selected tilebuffer with copies of the working tile

FILL
Fill the entire selected layer of the selected tilebuffer with copies of the working tile

CLS
Delete all tiles from all layers in the selected tilebuffer

CLL
Delete all tiles in the selected layer in the selected tilebuffer

CLR column, row, width, height
Delete all tiles within the specified rectangle in the selected layer of the selected tilebuffer

MOV horizontal_distance, vertical_distance
Move tile at the current cursor position in the selected tilebuffer by the specified distance

MOVB column, row, width, height, horizontal_distance, vertical_distance
Move entire rectangle of tiles in the selected tilebuffer by the specified distance

DRAW format
Put tiles in the selected tilebuffer according to the specified format

PRINT format
Print text using the specified format

PRINT.ADD format
Print text using the specified format, preserving the existing text at the same position

PRINTL
Same as the PRINT command, but moves cursor to the next line after printing

PRINTR text
Almost the same as the PRINT command, but does not recognize any escape sequences

PUTC tile_index, foreground_color_index, background_color_index
Put the specified single frame tile at the current cursor position in the selected tilebuffer

FCOL color_index
Set foreground color of text

BCOL color_index
Set background color of text

COLOR foreground_color_index, background_color_index
Set foreground and background colors of text

VSYNC
Update the screen

WCOL color_index
Set window background color

TRON
Enable tile transparency

TROFF
Disable tile transparency

CHR tile_index, pixel_row_index, byte
Define pixel pattern of a row in the tile at the specified index in the tileset. The pixel_row_index must be between 0 and 7. The byte value should be a number between 0 and 255

CHRS tile_index, row_0_byte, row_1_byte, row_2_byte, row_3_byte, row_4_byte, row_5_byte, row_6_byte, row_7_byte
Define pixel pattern in the tile at the specified index in the tileset. The byte values should be a number between 0 and 255

CHR.LEN x
Store in x the length of the tileset (i.e. the total number of tiles)

CHR.GETBS x, tile_index
Store in x the binary string representing the pixel pattern of the tile in the specified tileset index. In the resulting string, 1 means pixel with foreground color and 0 means pixel with background color

CHR.SETBS
Define the pixel pattern of the tile in the specified tileset index using a binary string. In this binary string, 1 means pixel with foreground color and 0 means pixel with background color

CHR.NEWPG
Add a new blank page of tiles to the tileset. Each page contains 256 tiles. The maximum number of pages supported is 256, resulting in a total maximum of 65536 tiles

PAL color_index, rgb
Set RGB value of the color at the specified index in the color palette

PAL.GET x, color_index
Store in x the RGB value of the color at the specified index in the color palette

PAL.LEN x
Store in x the length of the color palette (i.e. the total number of colors)

PAL.CLR
Clear the entire color palette

PAL.GETR x, color_index
Store in x the value of the red component of the color at the specified index in the color palette

PAL.GETG x, color_index
Store in x the value of the green component of the color at the specified index in the color palette

PAL.GETB x, color_index
Store in x the value of the blue component of the color at the specified index in the color palette

PAL.SETR color_index, red_value
Set the value of the red component of the color at the specified index in the color palette

PAL.SETG color_index, red_value
Set the value of the green component of the color at the specified index in the color palette

PAL.SETB color_index, red_value
Set the value of the blue component of the color at the specified index in the color palette

INPUT x, max_length
Read text input from user. This will show a blinking cursor on the screen at the current tilebuffer cursor position and wait for keyboard input from the user, with the specified max_length (maximum number of characters). Once the ENTER key is pressed, the string that was read is stored in x. If the ESCAPE key is pressed, an empty string is stored in x.

INKEY x
Store in x the name of the keyboard key currently being pressed

KCODE x
Store in x the code of the keyboard key currently being pressed

PLAY mml_string
Play music using a simplified version of MML (Music Macro Language)

LPLAY mml_string
Same as the PLAY command, but repeat indefinitely in a loop

SOUND frequency, length
Play a "beep" sound in the specified frequency for the specified length of time

VOL volume
Set the volume for playing music and sound

QUIET
Stop all currently playing music and sound

CLOAD file_path, x
Open the file at file_path, read the entire contents as text and store it as a string in x

BLOAD file_path, array_name
Open the file at file_path, read the entire contents as binary data and store it in the specified array

CSAVE file_path, x
Write string in x to the file at file_path

BSAVE file_path, array_name
Write the array as binary data to the file at file_path

FILE.CHK file_path, x
Store in x whether the specified file exists. 1 means file exists, 0 means file not found.

STR.FMT x, format, number
Convert the number to a string using the specified format

STR.SUB x, y, begin, end
Store in x the substring in y that begins and ends at the specified character indices

STR.LEN x, y
Store in x the length of the string y

STR.REPT x, times, y
Repeat the string y by the specified number of times and store it in x

STR.CAT x, y, z
Concatenate the strings y and z, and store the result in x

STR.SPLIT array_name, string, delimiter
Split the string into an array of strings using the specified delimiter

STR.TRIM x, y
Store in x the string y with leading and trailing spaces removed

STR.UCASE x, y
Store in x the uppercase version of the string y

STR.LCASE
Store in x the lowercase version of the string y

STR.REPL x, y, str_1, str_2
Store in x the string y with all occurrences of str_1 replaced by str_2

STR.AT x, y, index
Store in x the character at the specified index of the string y

STR.IX x, y, z
Search for the first occurrence of character z in the string y and stores the index in x

STR.START x, y, z
Store in x whether the string y starts with prefix z. 1 means yes, 0 means no

STR.END x, y, z
Store in x whether the string y ends with suffix z. 1 means yes, 0 means no

STR.HAS x, y, z
Store in x whether the string y contains the substring z. 1 means yes, 0 means no

DATA item_1, item_2, item_3, ...
Store the specified values in the static data block

READ x
Read into x the value of the item at the current pointer position in the static data block, then advances the pointer to the next item

RESTORE
Reset the pointer position in the static data block to item 0 (i.e. return to the start of the block)

DBG.BRK
Reserved for internal use only. Used to trigger a breakpoint during development

DBG.DUMP
Save debugging info to the file "PTM.dbg"

DBG.PERF
Enable the performance monitor

DBG.MSG text
Show a modal informational message box containing the specified text, for debugging purposes. This interrupts program execution until the OK button in the message box is pressed
