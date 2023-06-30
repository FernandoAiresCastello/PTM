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
Please note: This is an early beta release, expect bugs and limited documentation.
You can follow the project on GitHub if you like it: https://github.com/FernandoAiresCastello/PTM

The following is a brief explanation of the files in the package you've just downloaded:

PTM.exe is the machine executable itself. It contains the PTML interpreter. If you double-click this file, it will launch the PTM and by default it will look for a program file called "main.ptm" in the same folder.

The default main.ptm file included in this release simply includes an utility program called "PTM Launcher" (located under util/launcher.ptm), which will display an interactive menu for selecting and running a program.

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
