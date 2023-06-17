===============================================================================
	
	PTM - Programmable Tile Machine
	Version 0.2b
	(c) 2023 Developed by Fernando Aires Castello
	
	https://github.com/FernandoAiresCastello/PTM
	
===============================================================================

Welcome to the PTM version 0.2 beta!

This README contains some basic information on how to use the program.

For the PTML command reference, please refer to the following Google Drive link:
https://docs.google.com/spreadsheets/d/1uPhPh0LLgRmL87Uo9hDXGUhOOFIESIYAcZ_nJOlN2VI

This is an explanation of the files in the package you've just downloaded:

- "README.txt" is this file.

- "PTM.exe" is the machine executable, contains the PTML interpreter. If you double-click this file, it will launch the PTM and by default it will look for a program file called "main.ptm" in the same folder. The "main.ptm" file should contain your PTML code. You can also specify the name of a *.ptm file via the command line to this executable, and it will load then run the code. For example, the following will launch the PTM and load the "games/invaders.ptm" program:

	PTM.exe games/invaders.ptm
	
Alternatively, you can simply drag and drop a *.ptm file onto the "PTM.exe" file.

- "PTMTileEdit.exe" is a simple Windows tool for drawing 8x8 tiles. In this application you can use the copy and paste buttons to copy and paste the binary string representing that tile, so that it can be embedded into the PTML code via the CHR command.

- The "examples" folder contains the PTML samples as they appear on the README file of the GitHub repository root.

- The "games" folder contains some simple example games in PTML

- The "palettes" folder contains PTML programs that can be used to quickly setup some common color palettes

- The "tilesets" folder contains PTML programs that can be used to quickly setup some common ASCII character sets

- The "util" folder contains PTML programs implementing some common utilities

- The "test" folder contains PTML programs for testing purposes only

- The *.dll files are the required dependencies for PTM.exe.
