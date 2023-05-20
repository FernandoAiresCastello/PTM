## v0.1b

- Initial beta release

## v0.2b 
*This version is currently under development, this list will be updated as changes are introduced.*

- Some commands now have a different syntax or purpose
	- CLS now fills the window background with a color and does not affect any tilebuffer
	- CHR now defines a tileset entry with a single 64-character binary string
- Some commands have been removed:
	- NOP, CHRS
- Some commands have been renamed:
	- VSYNC became UPDATE
	- CYCLES became FRAMES
	- DBG.BRK became DEBUG
	- DBG.MSG became MSGBOX
- Implemented sprites (SPR.*)
- Implemented loading and playing external WAV sound files (SND.*)
- Implemented assertions for debugging purposes (ASSERT)
- Changes to tilebuffer viewports:
	- Support for smooth scrolling (BUF.SCRL)
	- Position and size are now pixel-based instead of tile-based (BUF.VIEW)
	- Each tilebuffer viewport now has their own background color (BUF.BCOL)
- Tile animation speed is now configurable (ANIM)
- Implemented reading lines of text file into array of strings (LLOAD)
