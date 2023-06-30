
=== PTM Tools ===

Note: All the tools available in this folder are *very* early access. Expect bugs and limited documentation.

=== PTM Studio ===

In its current version, this is a sort of IDE that can be used to create, edit and manage palettes, tilesets and tilebuffers. Those can all be saved in a single PTM Studio project file (.ptms) and exported at any time to separate data files in a format that the PTM understands natively.

Palette files exported can be loaded in a PTML program using the PAL.LOAD command.
Tileset files exported can be loaded in a PTML program using the CHR.LOAD command.
Tilebuffer files exported can be loaded in a PTML program using the BUF.LOAD command.

=== PTM Tile Editor ===

In its current version, this is a very simple 8x8 tile editor. It allows you to copy and paste the binary strings that represent the pixel pattern. Those binary strings can be directly included in a PTML program via the CHR command in order to define a tile in the tileset. Useful for when you don't need all the bells and whistles of PTM Studio and just need a quick and easy way to edit a single tile pattern.
