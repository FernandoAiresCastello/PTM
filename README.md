![PTM Logo](https://github.com/FernandoAiresCastello/PTM/blob/master/Images/logo.fw.png?raw=true)

# PTM - Programmable Tile Machine

## About
	
__PTM (Programmable Tile Machine)__ is a "pseudo-8-bit fantasy computer" that you can program using a built-in programming language called PTML. The system aims to be similar in look-and-feel to some early 8-bit computer systems such as the MSX, ZX Spectrum and Atari 800. Also inspired by the modern game engines Bitsy and PICO-8.

__PTML__ is an interpreted, imperative, semi-structured, loosely typed, low-level programming language, with only two data types: strings and integers (with support for dynamic arrays of those types). All you need for programming in it is a plain-text editor like Notepad. The syntax looks like some early dialects of BASIC and some common Assembly languages for 8-bit computers. Familiarity with any of those will probably make it easier to work with PTML, but the language itself is fairly straightforward (see some code samples below).

## Downloads

The latest released version is __v0.1b.__  
You can download pre-built PTM releases on Itch.io, on this page: https://fernandoairescastello.itch.io/ptm

The latest development build for version __v0.2b__ is available [here](https://github.com/FernandoAiresCastello/PTM/tree/master/v0.2b/Build).  
Note that development builds can be *very* unstable since they are being actively worked on and change frequently, so use at your own risk!

## Documentation

- [PTML Command Reference v0.1b](https://docs.google.com/spreadsheets/d/1YwwevUD65kUNky194NmnlzqBe67nMvq3Hs2m6oJnqa8/edit?usp=sharing)
- [PTML Command Reference v0.2b (work in progress)](https://docs.google.com/spreadsheets/d/1uPhPh0LLgRmL87Uo9hDXGUhOOFIESIYAcZ_nJOlN2VI/edit?usp=sharing)

## Examples

Here are some examples of PTML programs:

**Hello World!**
```
PRINT "Hello World!"
```
**Personalized Hello**
```
LOCATE 1, 1
PRINT "Please, type your name:\n"
INPUT name, 20
LOCATE 1, 4
PRINTF "Hello, {%name}!"
```
**Blinking Smiley**
```
# Setup tileset
CHR 1, "0011110001111110110110111111111111011011111001110111111000111100"
CHR 2, "0011110001111110111111111111111111111111110110110110011000111100"

# Setup color palette
PAL 0, &h000080
PAL 1, &hffff00

# Calculate center position of default tilebuffer
BUF.COLS default, cols
BUF.ROWS default, rows
DIV center_x, cols, 2
DIV center_y, rows, 2

# Setup tile for smiley
TILE.NEW 1, 1
TILE.ADD 2, 1

# Put smiley at center of default tilebuffer
LOCATE center_x, center_y
PUT
```
