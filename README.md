![PTM Logo](https://github.com/FernandoAiresCastello/PTM/blob/master/Images/logo.fw.png?raw=true)

# PTM - Programmable Tile Machine

## About
	
__PTM (Programmable Tile Machine)__ is a "pseudo-8-bit fantasy computer" that you can program using a built-in programming language called PTML. The system aims to be similar in look-and-feel to some early 8-bit computer systems such as the MSX, ZX Spectrum and Atari 800. Also inspired by the modern game engines Bitsy and PICO-8.

__PTML__ is an interpreted, imperative, semi-structured, loosely typed, low-level programming language, with only two data types: strings and integers. The syntax looks like some early dialects of BASIC and some common assembly languages for 8-bit computers. Familiarity with any of those will probably make it easier to work with PTML, but the language itself is fairly straightforward. In older versions (including the latest release) the PTM executable was the PTML interpreter itself, and code had to be written in plain-text files using an external editor like Notepad. In the latest development version (not yet released), the PTM executable launches an integrated line editor and command-line interface, and the interpreter runs in the same screen as the editor, similar to the Atari 800 BASIC interpreter.

## Downloads

You can download pre-built PTM releases on Itch.io here: https://fernandoairescastello.itch.io/ptm

The latest released version is __v0.2b__.  
The current development version is __v0.4b__.

![PTM v0.4b](https://github.com/FernandoAiresCastello/PTM/blob/master/Images/ptml_example_01.png?raw=true)

__Note:__ Version __v0.3b__ is no longer being actively developed. Version __v0.4b__ is now the current one, it's a completely new project (developed from scratch) and is drastically different from any previous version. PTML for v0.4b is an almost completely different language, although it shares most of the syntax and simplicity of the previous installments.

*Note: development builds can be *very* unstable since they are being actively worked on and change frequently, so use at your own risk!*

## Documentation

- [PTML Command Reference v0.2b](https://docs.google.com/spreadsheets/d/1uPhPh0LLgRmL87Uo9hDXGUhOOFIESIYAcZ_nJOlN2VI/edit?usp=sharing)

## Examples

The following are some examples of PTML programs. These examples target the lastest version of the machine:

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
**Moving Sprites**
```
# Setup tileset
CHR 1, "0011110001111110110110111111111111011011111001110111111000111100"
CHR 2, "0011110001111110111111111111111111111111110110110110011000111100"

# Setup color palette
PAL 0, &h000080
PAL 1, &hffff00
PAL 2, &hf0f0f0

# Create sprites
TILE.NEW 1, 1
TILE.ADD 2, 1
SPR.NEW "smiley"
SPR.POS "smiley", 170, 100
SPR.SHOW "smiley"

# Print instructions
COLOR 2
LOCATE 6, 1
PRINT "Press arrow keys to move sprite"

# Await input and move sprite
loop:
	IF.KEY "RIGHT"
		SPR.MOVE "smiley", 1, 0
	ENDIF
	IF.KEY "LEFT"
		SPR.MOVE "smiley", -1, 0
	ENDIF
	IF.KEY "DOWN"
		SPR.MOVE "smiley", 0, 1
	ENDIF
	IF.KEY "UP"
		SPR.MOVE "smiley", 0, -1
	ENDIF
	IF.KEY "ESC"
		EXIT
	ENDIF
	UPDATE
	GOTO loop
```
You can also check out a few example games in PTML: [Invaders](https://github.com/FernandoAiresCastello/PTM/blob/master/v0.2b/Build/games/invaders.ptm), [Advanced Lawnmower Simulator](https://github.com/FernandoAiresCastello/PTM/blob/master/v0.2b/Build/games/advanced_lawnmower_sim.ptm) and [Pong](https://github.com/FernandoAiresCastello/PTM/blob/master/v0.2b/Build/games/pong.ptm).
