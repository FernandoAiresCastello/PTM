![PTM Logo](https://github.com/FernandoAiresCastello/PTM/blob/master/Images/logo.fw.png?raw=true)

# PTM - Programmable Tile Machine

__PTM (Programmable Tile Machine)__ is a "pseudo-8-bit fantasy computer" that you can program using a built-in programming language called PTML. The system aims to be similar in look-and-feel to some early 8-bit computer systems with low-resolution and tile-based displays, such as the MSX, ZX Spectrum and Atari 800. Also inspired by the modern game engines Bitsy and PICO-8.

__PTML__ is an interpreted, imperative, loosely typed, line-based, low-level programming language, with only two basic data types: strings and integers, with support for fixed-size arrays. The syntax is based on early, unstructured dialects of BASIC and also Assembly languages for 8-bit computers (sometimes resembling Zilog Z80 code).

Here is an example of PTML code, for the "Advanced Lawnmower Simulator" minigame: [LAWNSIM.PTM](https://github.com/FernandoAiresCastello/PTM/blob/master/0.3/Build/USR/LAWNSIM.PTM)

## Machine Specs

**Video**
* Resolution: 360x200 pixels in total *(pixels are not individually addressable)*
* Screen: 41x23 tile buffer, each tile being 8x8 pixels, having an indexed character and two indexed colors (foreground and background)
* Color palette: 256 colors, no alpha transparency, fully editable, with built-in default colors
* Character set: 256 characters, fully editable, with built-in default characters based on ASCII
* Sprites: 256 sprites, each sprite being a single tile, displayed at pixel coordinates over tile buffer

**Audio**
* Single channel, square-wave tone generator
* Simplified MML (music macro language) support

**File System**
* Native support for writing and reading files containing PTML programs (.PTM), color palettes (.PAL), character sets (.CHR), screen tile buffers (.BUF) and arbitrary data records (.DAT).
* Sandboxed file system. The machine executable only has access to files and folders within its own root directory

**Input**
* Keyboard input only

**Software Development**
* Programming language: PTML support only
* Built-in program editor and launcher
* Supports external tools

## Version history

This project is currently in early alpha stage. All released versions are to be considered as experimental, but mostly functional.

| **Version** | **Release date or status** | **Comments** |
|-------------|------------------|--------------|
| **0.3**     | _In development_ | Current implementation, started from scratch. PTML is an entirely different language from earlier versions. Includes a built-in program editor with immediate mode and also an external IDE for editing code and data. |
| **0.2**     | _July 1, 2023_   | Many PTML improvements and new commands. This version also included a few standalone tools (PTM Studio and PTM Tile Editor) besides the main PTM interpreter. |
| **0.1**     | _May 14, 2023_   | First release. Ranked 4th out of 61 entries in the [Tool Jam 3](https://itch.io/jam/the-tool-jam-3/results). |

## Downloads

You can download pre-built PTM releases on Itch.io here: https://fernandoairescastello.itch.io/ptm

The latest released version is __0.2__.  
The current development version is __0.3__ (pictured below).

![PTM Studio 0.4](https://github.com/FernandoAiresCastello/PTM/blob/master/Images/ptm_studio.png?raw=true)
![PTM 0.4](https://github.com/FernandoAiresCastello/PTM/blob/master/Images/ptml_example_03.png?raw=true)

*Note: development builds can be *very* unstable since they are being actively worked on and change frequently, so use at your own risk!*

## Documentation

- [PTML 0.2 Command Reference](https://docs.google.com/spreadsheets/d/1uPhPh0LLgRmL87Uo9hDXGUhOOFIESIYAcZ_nJOlN2VI/edit?usp=sharing)
