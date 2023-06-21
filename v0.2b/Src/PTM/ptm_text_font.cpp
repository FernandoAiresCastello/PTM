#include "ptm_text_font.h"
#include "ptm_tile_system.h"

void ptm_init_text_font()
{
	tileset.set(32, "0000000000000000000000000000000000000000000000000000000000000000"); // 32 Space
	tileset.set(33, "0011000000110000001100000011000000110000000000000011000000000000"); // 33 !
	tileset.set(34, "0110110001101100011011000000000000000000000000000000000000000000"); // 34 "
	tileset.set(35, "0000000000010100001111100001010000111110000101000000000000000000"); // 35 #
	tileset.set(36, "0001000011111110110100001111111000010110110101101111111000010000"); // 36 $
	tileset.set(37, "0000000001100010011001000000100000010000001001100100011000000000"); // 37 %
	tileset.set(38, "0001000001111100011000000011100001100000011111000001000000000000"); // 38 &
	tileset.set(39, "0000000000011000000110000011000000000000000000000000000000000000"); // 39 '
	tileset.set(40, "0000110000011000001100000011000000110000000110000000110000000000"); // 40 (
	tileset.set(41, "0011000000011000000011000000110000001100000110000011000000000000"); // 41 )
	tileset.set(42, "0000000001101100001110001111111000111000011011000000000000000000"); // 42 *
	tileset.set(43, "0000000000011000000110000111111000011000000110000000000000000000"); // 43 +
	tileset.set(44, "0000000000000000000000000000000000011000000110000011000000000000"); // 44 ,
	tileset.set(45, "0000000000000000000000000111111000000000000000000000000000000000"); // 45 -
	tileset.set(46, "0000000000000000000000000000000000000000000110000001100000000000"); // 46 .
	tileset.set(47, "0000000100000010000001000000100000010000001000000100000010000000"); // 47 /
	tileset.set(48, "0000000011111110110001101101011011010110110001101111111000000000"); // 48 Digit 0
	tileset.set(49, "0000000000111000000110000001100000011000000110000111111000000000"); // 49 Digit 1
	tileset.set(50, "0000000001111110011001100000011001111110011000000111111000000000"); // 50 Digit 2
	tileset.set(51, "0000000001111110000001100011110000000110000001100111111000000000"); // 51 Digit 3
	tileset.set(52, "0000000001100110011001100110011001111110000001100000011000000000"); // 52 Digit 4
	tileset.set(53, "0000000001111110011000000111111000000110011001100111111000000000"); // 53 Digit 5
	tileset.set(54, "0000000001111110011000000111111001100110011001100111111000000000"); // 54 Digit 6
	tileset.set(55, "0000000001111110000001100000110000011000001100000011000000000000"); // 55 Digit 7
	tileset.set(56, "0000000001111110011001100011110001100110011001100111111000000000"); // 56 Digit 8
	tileset.set(57, "0000000001111110011001100110011001111110000001100111111000000000"); // 57 Digit 9
	tileset.set(58, "0000000000000000000110000001100000000000000110000001100000000000"); // 58 :
	tileset.set(59, "0000000000000000000110000001100000000000000110000001100000001000"); // 59 ;
	tileset.set(60, "0000000000000110000110000110000000011000000001100000000000000000"); // 60 <
	tileset.set(61, "0000000000000000011111100000000001111110000000000000000000000000"); // 61 =
	tileset.set(62, "0000000001100000000110000000011000011000011000000000000000000000"); // 62 >
	tileset.set(63, "0111111001100110000001100001111000011000000000000001100000000000"); // 63 ?
	tileset.set(64, "1111111010000010101110101010101010111110100000001111111000000000"); // 64 @
	tileset.set(65, "0111111001100110011001100110011001111110011001100110011000000000"); // 65 Letter A
	tileset.set(66, "0111111001100110011001100111110001100110011001100111111000000000"); // 66 Letter B
	tileset.set(67, "0111111001100110011000000110000001100000011001100111111000000000"); // 67 Letter C
	tileset.set(68, "0111110001100110011001100110011001100110011001100111110000000000"); // 68 Letter D
	tileset.set(69, "0111111001100000011000000111110001100000011000000111111000000000"); // 69 Letter E
	tileset.set(70, "0111111001100000011000000111110001100000011000000110000000000000"); // 70 Letter F
	tileset.set(71, "0111111001100110011000000110111001100110011001100111111000000000"); // 71 Letter G
	tileset.set(72, "0110011001100110011001100111111001100110011001100110011000000000"); // 72 Letter H
	tileset.set(73, "0111111000011000000110000001100000011000000110000111111000000000"); // 73 Letter I
	tileset.set(74, "0000011000000110000001100000011001100110011001100111111000000000"); // 74 Letter J
	tileset.set(75, "0110011001100110011011000111100001100110011001100110011000000000"); // 75 Letter K
	tileset.set(76, "0110000001100000011000000110000001100000011000000111111000000000"); // 76 Letter L
	tileset.set(77, "1000001011000110111011101111111011010110110101101100011000000000"); // 77 Letter M
	tileset.set(78, "0100011001100110011101100111111001101110011001100110001000000000"); // 78 Letter N
	tileset.set(79, "0111111001100110011001100110011001100110011001100111111000000000"); // 79 Letter O
	tileset.set(80, "0111111001100110011001100110011001111110011000000110000000000000"); // 80 Letter P
	tileset.set(81, "0111111001100110011001100110011001100110011011100111111000000011"); // 81 Letter Q
	tileset.set(82, "0111111001100110011001100110011001111100011001100110011000000000"); // 82 Letter R
	tileset.set(83, "0111111001100110011000000111111000000110011001100111111000000000"); // 83 Letter S
	tileset.set(84, "0111111000011000000110000001100000011000000110000001100000000000"); // 84 Letter T
	tileset.set(85, "0110011001100110011001100110011001100110011001100111111000000000"); // 85 Letter U
	tileset.set(86, "0110011001100110011001100010010000111100000110000001100000000000"); // 86 Letter V
	tileset.set(87, "1100011011000110110101101101011011111110011011000110110000000000"); // 87 Letter W
	tileset.set(88, "0110011001100110001111000001100000111100011001100110011000000000"); // 88 Letter X
	tileset.set(89, "0110011001100110011001100110011001111110000110000001100000000000"); // 89 Letter Y
	tileset.set(90, "0111111000000110000011000001100000110000011000000111111000000000"); // 90 Letter Z
	tileset.set(91, "0001111000011000000110000001100000011000000110000001100000011110"); // 91 [
	tileset.set(92, "1000000001000000001000000001000000001000000001000000001000000001"); // 92 Backslash (\)
	tileset.set(93, "0111100000011000000110000001100000011000000110000001100001111000"); // 93 ]
	tileset.set(94, "0001000000111000011011001100011000000000000000000000000000000000"); // 94 ^
	tileset.set(95, "0000000000000000000000000000000000000000000000000111111000000000"); // 95 _
	tileset.set(96, "0000000000011000000110000011000000000000000000000000000000000000"); // 96 Backtick (`)
	tileset.set(97, "0000000000000000011111000000110001111100011011000111111000000000"); // 97 Letter a
	tileset.set(98, "0111000000110000001111100011011000110110001101100011111000000000"); // 98 Letter b
	tileset.set(99, "0000000000000000011111100110011001100000011000000111111000000000"); // 99 Letter c
	tileset.set(100, "0000111000001100011111000110110001101100011011000111110000000000"); // 100 Letter d
	tileset.set(101, "0000000000000000011111100110011001111110011000000111111000000000"); // 101 Letter e
	tileset.set(102, "0000000000111110001100000111110000110000001100000011000000000000"); // 102 Letter f
	tileset.set(103, "0000000000000000011111100110110001101100011111000000110001111100"); // 103 Letter g
	tileset.set(104, "0110000001100000011111000110110001101100011011000110111000000000"); // 104 Letter h
	tileset.set(105, "0001100000000000001110000001100000011000000110000111111000000000"); // 105 Letter i
	tileset.set(106, "0000011000000000000001100000011000000110001101100011011000111110"); // 106 Letter j
	tileset.set(107, "0110000001100000011001100110110001111000011001100110011000000000"); // 107 Letter k
	tileset.set(108, "0011100000011000000110000001100000011000000110000111111000000000"); // 108 Letter l
	tileset.set(109, "0000000000000000111111101101011011010110110101101101011000000000"); // 109 Letter m
	tileset.set(110, "0000000000000000011111100011011000110110001101100011011000000000"); // 110 Letter n
	tileset.set(111, "0000000000000000011111100110011001100110011001100111111000000000"); // 111 Letter o
	tileset.set(112, "0000000000000000011111100011011000110110001111100011000000110000"); // 112 Letter p
	tileset.set(113, "0000000000000000011111000110110001101100011111000000110000001110"); // 113 Letter q
	tileset.set(114, "0000000000000000011111100011011000110000001100000011000000000000"); // 114 Letter r
	tileset.set(115, "0000000000000000011111100110000001111110000001100111111000000000"); // 115 Letter s
	tileset.set(116, "0000000000110000011111100011000000110000001100000011111000000000"); // 116 Letter t
	tileset.set(117, "0000000000000000011011000110110001101100011011000111111000000000"); // 117 Letter u
	tileset.set(118, "0000000000000000011001100110011001100110001111000001100000000000"); // 118 Letter v
	tileset.set(119, "0000000000000000110101101101011011010110111111100110110000000000"); // 119 Letter w
	tileset.set(120, "0000000000000000011001100011110000011000001111000110011000000000"); // 120 Letter x
	tileset.set(121, "0000000000000000011101100011011000110110001111100000011000111110"); // 121 Letter y
	tileset.set(122, "0000000000000000011111100000011000011000011000000111111000000000"); // 122 Letter z
	tileset.set(123, "0000111000001000000010000011000000001000000010000000111000000000"); // 123 {
	tileset.set(124, "0001100000011000000110000001100000011000000110000001100000011000"); // 124 |
	tileset.set(125, "0111000000010000000100000000110000010000000100000111000000000000"); // 125 }
	tileset.set(126, "0000000000000000011000001111001010011110000011000000000000000000"); // 126 ~
}
