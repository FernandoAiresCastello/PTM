## v0.1b

- Initial beta release

## v0.2b 
*Note 1: This version is currently under development, this list will be updated as changes are introduced.*  
*Note 2: Programs made for v0.1b will not work properly in this version due to breaking changes in the language.*  
*Note 3: There are too many changes since v0.1b, some minor changes may be missing from this changelog.*  

- Some commands now have a different syntax or purpose
	- CHR now defines a tileset entry with a single 64-character binary string
	- TILE.NEW and TILE.ADD no longer require the background color parameter (now it is optional; omitting it makes the tile transparent)
	- Commands that require parameters for rectangle corners (e.g. RECT, FILL) now take x1, y1, x2, y2 instead of x, y, width, height
- Some commands have been removed:
	- NOP, CHRS, DRAW, TRON, TROFF
- Some commands have been renamed:
	- VSYNC became UPDATE
	- CYCLES became FRAMES
	- CLL became BUF.CLL
	- CLR became DELR
	- DBG.BRK became DEBUG
	- DBG.MSG became MSGBOX
	- STR.IX became STR.FIND
	- STR.START became STR.PFX
	- STR.END became STR.SFX
	- FILE.CHK became FCHK
	- MML commands now have the prefix MML (e.g. PLAY became MML.PLAY, etc)
- Implemented sprites (SPR.*)
- Implemented loading and playing external WAV sound files (SND.*)
- Implemented assertions for debugging purposes (ASSERT)
- Tile animation speed is now configurable (ANIM)
- Tile transparency is no longer a global setting. Now, tiles are made transparent upon creation by omitting the background color parameter
- Implemented BUF.TOGL to toggle visibility of a tilebuffer
- Changes to tilebuffer viewports:
	- Support for smooth scrolling (BUF.SCRL)
	- Position and size are now pixel-based instead of tile-based (BUF.VIEW)
	- Each tilebuffer viewport now has their own background color (BUF.BCOL)
- Implemented reading lines of text file into array of strings (LLOAD)
- Implemented new conditional blocks IF.TRUE and IF.FALSE
- Implemented STR.JOIN to join array of strings into single string
- Implemented PTM command to indicate intended version for running the program
