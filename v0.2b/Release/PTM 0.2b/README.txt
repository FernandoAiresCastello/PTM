#=============================================================================#
#                                                                             #
#       PTM - Programmable Tile Machine                                       #
#                                                                             #
#       Version 0.2b                                                          #
#                                                                             #
#       (c) 2023 Developed by Fernando Aires Castello                         #
#                                                                             #
#=============================================================================#


Welcome to the PTM version 0.2 beta! 
Release date: July 1st, 2023
Note: This is an early beta release, expect bugs and limited documentation.


#===========#
#   Links   #
#===========#

You can find all released versions of PTM on Itch.io:

	https://fernandoairescastello.itch.io/ptm

Please follow the project on GitHub if you like it. There you can also download nightly (very unstable) development builds for the next upcoming version:

	https://github.com/FernandoAiresCastello/PTM
	

#===========#
#   About   #
#===========#

PTM (Programmable Tile Machine) is a "pseudo-8-bit fantasy computer" that you can program using a built-in programming language called PTML. The system aims to be similar in look-and-feel to some early 8-bit computer systems such as the MSX, ZX Spectrum and Atari 800. Also inspired by the modern game engines Bitsy and PICO-8.

PTML is an interpreted, imperative, semi-structured, loosely typed, low-level programming language, with only two data types: strings and integers (with support for dynamic arrays of those types). All you need for programming in it is a plain-text editor like Notepad. The syntax looks like some early dialects of BASIC and common assembly languages for 8-bit computers. Familiarity with any of those will probably make it easier to work with PTML, but the language itself is fairly straightforward.


#======================#
#   Package Contents   #
#======================#

The following is a brief explanation of the files and directories contained in this package:

PTM.exe is the machine executable itself. It contains the PTML interpreter. If you double-click this file, it will launch the PTM and by default it will look for a program file called "main.ptm" in the same folder.

The default main.ptm file included in this release simply includes an utility program called "PTM Launcher", which will display an interactive menu for selecting and running another program. You can safely replace the contents of main.ptm with your own code, or create different PTML source files and include them directly in main.ptm using the INCL command.

If you want the machine to boot up using some program file other than main.ptm, you can specify the file path via the command line to PTM.exe and it will load then run the code. For example, the following command line will launch the PTM and run the "games/invaders.ptm" program included in this package:

    PTM.exe "games/invaders.ptm"
    
Alternatively, you can simply drag and drop any .ptm file onto PTM.exe to run it.

All the .dll files need to be always present in the same folder as the PTM.exe file for it to run properly.

Directories:

	- The "docs" folder contains the offline documentation files for this version of the PTM.
	- The "examples" folder contains the PTML samples as they appear on the README file of the GitHub repository root.
	- The "games" folder contains some simple example games in PTML.
	- The "palettes" folder contains palette files for some common color palettes that can be loaded using the PAL.LOAD command.
	- The "tilesets" folder contains tileset files for some common tilesets that can be loaded using the CHR.LOAD command.
	- The "util" folder contains PTML programs implementing some common utilities.


#===============#
#   Changelog   #
#===============#

v0.2b (July 1st, 2023)

	- Too many changes since v0.1b to keep track of. This version breaks compatibility with most v0.1b programs since several core features have changed. Some of the main changes include: support for sprites, smooth scrolling, loading and playing WAV sound files, saving and loading palette, tileset and tilebuffer files, mouse support, handling of record files, support for clipboard access and querying of system date and time.

v0.1b (May 15th, 2023)

	- Initial beta release.
