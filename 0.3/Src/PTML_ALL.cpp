#include "PTML_shared_headers.h"
#include "PTML_ALL.h"
#include "PTML_PROGRAM.h"
#include "PTML_VARS.h"
#include "PTML_CTFLOW.h"
#include "PTML_MATH.h"
#include "PTML_GRAPHICS.h"
#include "PTML_FILESYSTEM.h"
#include "PTML_INPUT.h"
#include "PTML_SOUND.h"

t_function_ptr PTML::get_cmd_pointer(const t_string& cmd)
{
	// === PROGRAM MANAGEMENT ===
	CMD("LIST", LIST); // List current program
	CMD("NEW", NEW); // Delete current program
	CMD("RENUM", RENUM); // Renumber current program
	CMD("PROG", PROG); // Print filename of last loaded or saved program

	// === SYSTEM CONTROL ===
	CMD("RUN", RUN); // Execute current program, or load another program from disk and then execute it
	CMD("END", END); // End execution of current program, returning to the main editor
	CMD("HALT", HALT); // Stop execution of current program and does nothing else
	CMD("EXIT", EXIT); // Exit to host operating system
	CMD("RESET", RESET); // Restart machine
	CMD("PAUSE", PAUSE); // Pause program execution for the specified number of frames
	CMD("BREAK", BREAK); // Enable or disable program termination by user using the ESC key

	// === MEMORY ===
	CMD("SET", SET); // Set value to variable
	CMD("DIM", ARR_DIM); // Create a new array
	CMD("LEN", ARR_LEN); // Get length of array
	CMD("SWAP", SWAP); // Swap value between two variables
	CMD("MEMCLR", MEMCLR); // Delete all variables and arrays

	// === MATH ===
	CMD("INC", INC); // Increment numeric variable value by 1
	CMD("DEC", DEC); // Decrement numeric variable value by 1
	CMD("ADD", ADD); // Add two numeric values
	CMD("SUB", SUB); // Subtract two numeric values
	CMD("MUL", MUL); // Multiply two numeric values
	CMD("DIV", DIV); // Divide two numeric values
	CMD("DIVR", DIVR); // Divide two numeric values and get the remainder
	CMD("POW", POW); // Calculate the power of a numeric value
	CMD("SQRT", SQRT); // Calculate square root of a numeric value
	CMD("RND", RND); // Get a random numeric value

	// === JUMPS ===
	CMD("GOTO", GOTO); // Go to label
	CMD("GOTO.E", GOTO_IFE); // Go to label if equal
	CMD("GOTO.NE", GOTO_IFNE); // Go to label if not equal
	CMD("GOTO.G", GOTO_IFG); // Go to label if greater than
	CMD("GOTO.GE", GOTO_IFGE); // Go to label if greater than or equal
	CMD("GOTO.L", GOTO_IFL); // Go to label if lesser than
	CMD("GOTO.LE", GOTO_IFLE); // Go to label if lesser than or equal
	CMD("GOTO.K", GOTO_IFKEY); // Go to label if key is pressed
	CMD("GOTO.NK", GOTO_IFNKEY); // Go to label if key is not pressed

	// === SUBROUTINES ===
	CMD("CALL", CALL); // Call subroutine at label
	CMD("CALL.E", CALL_IFE); // Call subroutine at label if equal
	CMD("CALL.NE", CALL_IFNE); // Call subroutine at label if not equal
	CMD("CALL.G", CALL_IFG); // Call subroutine at label if greater than
	CMD("CALL.GE", CALL_IFGE); // Call subroutine at label if greater than or equal
	CMD("CALL.L", CALL_IFL); // Call subroutine at label if lesser than
	CMD("CALL.LE", CALL_IFLE); // Call subroutine at label if lesser than or equal
	CMD("CALL.K", CALL_IFKEY); // Call subroutine at label if key is pressed
	CMD("CALL.NK", CALL_IFNKEY); // Call subroutine at label if key is not pressed
	CMD("RET", RET); // Return from subroutine

	// === FILE SYSTEM ===
	CMD("FILES", FILES); // List files on disk
	CMD("SAVE", SAVE); // Save file to disk
	CMD("LOAD", LOAD); // Load file from disk
	CMD("RENAME", RENAME); // Rename file
	CMD("KILL", KILL); // Delete file
	CMD("OPEN", OPEN); // Open record file for read or write
	CMD("CLOSE", CLOSE); // Close record file
	CMD("WRITE", WRITE); // Write to record file
	CMD("READ", READ); // Read from record file
	CMD("EOF", FEOF); // Check whether end of record file has been reached

	// === KEYBOARD INPUT ===
	CMD("INPUT", INPUT); // Wait for user to type a string and press the ENTER key, then return the typed string
	CMD("INKEY", INKEY); // Get last pressed key
	CMD("FLUSH", KB_FLUSH); // Clear keyboard buffer

	// === GRAPHICS ===
	CMD("PAL", PAL); // Set RGB value for color at palette index
	CMD("CHR", CHR); // Set pixel pattern for character at charset index

	// === SCREEN ===
	CMD("REFRESH", REFRESH); // Force update the screen
	CMD("AUTOREF", AUTOREF); // Enable or disable the automatic update of the screen
	CMD("FULLSCR", FULLSCR); // Enable, disable or toggle full-screen mode
	CMD("CLS", CLS); // Clear the screen

	// === CURSOR ===
	CMD("CURSOR", CURSOR); // Make cursor visible or invisible
	CMD("LOCATE", LOCATE); // Move cursor to position
	CMD("GETX", CSR_GETX); // Get cursor X position
	CMD("GETY", CSR_GETY); // Get cursor Y position
	
	// === TEXT OUTPUT ===
	CMD("PRINT", PRINT); // Print string on screen at current cursor position
	CMD("PRINTL", PRINTL); // Print string on screen at current cursor position, then move cursor to next line
	CMD("PRINTF", PRINTF); // Print formatted string on screen at current cursor position

	// === COLOR REGISTER ===
	CMD("COLOR", COLOR); // Change foreground/background colors of tiles and/or color of the screen border
	CMD("INK", COLOR_SETF); // Change foreground color of tiles
	CMD("PAPER", COLOR_SETB); // Change background color of tiles
	CMD("BORDER", COLOR_SETBR); // Change color of the screen border
	CMD("MODE", COLOR_MODE); // Change color mode (0 = monochrome; 1 = multicolor)
	
	// === TILE REGISTER ===
	CMD("NEWTILE", TILE_NEW); // Clear tile register
	CMD("TILE", TILE_ADD); // Add tile to tile register
	CMD("CSET", TILE_SETC); // Set character index of tile register
	CMD("CGET", TILE_GETC); // Get character index of tile register
	CMD("FSET", TILE_SETF); // Set foreground color of tile register
	CMD("FGET", TILE_GETF); // Get foreground color of tile register
	CMD("BSET", TILE_SETB); // Set background color of tile register
	CMD("BGET", TILE_GETB); // Get background color of tile register
	CMD("PSET", TILE_SETP); // Set property in tile register
	CMD("PGET", TILE_GETP); // Get property from tile register

	// === SPRITES ===
	CMD("SPRITE", SET_SPRITE); // Create or update sprite with tile equal to tile register, optionally at specified position
	CMD("MOVE", MOVE_SPRITE); // Move sprite to specified position
	CMD("SHOW", SHOW_SPRITE); // Show or hide sprite
	CMD("SGET", GET_SPRITE); // Copy sprite tile to tile register
	
	// === TILE BUFFER ===
	CMD("GET", GET); // Get tile from screen buffer at current cursor position and store in tile register
	CMD("PUT", PUT); // Copy tile from tile register to screen buffer at current cursor position
	CMD("DEL", DEL); // Delete tile from screen buffer at current cursor position
	CMD("RECT", RECT); // Fill a rectangle in the screen buffer with copies of tile from tile register
	CMD("FILL", FILL); // Fill the entire screen buffer with copies of tile from tile register

	// === SOUND ===
	CMD("BEEP", BEEP); // Emit a beeping sound with the specified duration and frequency
	CMD("PLAY", PLAY); // Play a sequence of notes, only once
	CMD("LPLAY", LPLAY); // Play a sequence of notes, looping indefinitely

	// === STRING HANDLING ===
	CMD("CONCAT", STR_CONCAT); // Concatenate two strings into one
	CMD("UPPER", STR_UPPER); // Convert all characters in string to uppercase
	CMD("LOWER", STR_LOWER); // Convert all characters in string to lowercase
	CMD("FIND", STR_FIND); // Find index of specified substring inside the given string
	CMD("SUBSTR", STR_SUBSTR); // Extract a substring from the given string
	CMD("STRLEN", STR_LEN); // Get length of string
	CMD("ASC", STR_ASCII); // Get the ASCII value of a character
	CMD("CHAR", STR_CHAR); // Get the character at the specified index of the given string

	return nullptr;
}
