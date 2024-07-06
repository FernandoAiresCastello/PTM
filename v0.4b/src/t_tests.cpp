#include <cassert>
#include "t_tests.h"
#include "t_char.h"
#include "t_tile.h"
#include "t_data.h"
#include "t_tilebuffer.h"
#include "t_window.h"
#include "t_interpreter.h"

void t_tests::run()
{
	t_char_tests();
	t_data_tests();
	t_tile_tests();
	t_tilebuf_tests();
	interpreter_tests();
}

void t_tests::t_char_tests()
{
	// default constructor
	t_char ch1;
	assert(ch1.is_blank());
	assert(ch1.ix == 0);
	assert(ch1.fgc == 0);
	assert(ch1.bgc == 0);

	// set all values at once
	ch1.set(12, 34, 56);
	assert(ch1.ix == 12);
	assert(ch1.fgc == 34);
	assert(ch1.bgc == 56);

	// constructor setting all values
	t_char ch2(23, 45, 67);
	assert(ch2.is_not_blank());
	assert(ch2.ix == 23);
	assert(ch2.fgc == 45);
	assert(ch2.bgc == 67);

	// assignment operator
	ch2 = ch1;
	assert(ch2 == ch1);
	assert(ch2.ix == 12);
	assert(ch2.fgc == 34);
	assert(ch2.bgc == 56);

	// copy constructor
	t_char ch3(ch2);
	assert(ch3 == ch2);
	assert(ch3.ix == 12);
	assert(ch3.fgc == 34);
	assert(ch3.bgc == 56);

	// set to blank
	ch3.set_blank();
	assert(ch3.is_blank());
	assert(ch3.ix == 0);
	assert(ch3.fgc == 0);
	assert(ch3.bgc == 0);

	// create a new blank instance
	t_char ch4 = t_char::blank();
	assert(ch4.is_blank());
	assert(ch4.ix == 0);
	assert(ch4.fgc == 0);
	assert(ch4.bgc == 0);
}

void t_tests::t_data_tests()
{
	// default constructor
	t_data data;
	assert(data.is_empty());

	// set string value
	data.set("string_data", "abcd");
	assert(data.is_not_empty());
	assert(data.has("string_data"));
	assert(data.has("string_data", "abcd"));

	// get string value
	auto string_data = data.get("string_data");
	assert(string_data == "abcd");

	// set int value
	data.set("int_data", 1234);
	assert(data.has("int_data"));
	assert(data.has("int_data", 1234));

	// get int value
	auto int_data = data.get_int("int_data");
	assert(int_data == 1234);

	// get non-existent data
	auto nonsense1 = data.get("asdfasf");
	assert(nonsense1 == t_data::null);
	auto nonsense2 = data.get_int("asdfasf");
	assert(nonsense2 == t_data::null_int);

	// copy constructor
	t_data first_copied_data(data);
	assert(first_copied_data.is_not_empty());
	assert(first_copied_data == data);

	// assignment operator
	t_data second_copied_data;
	assert(second_copied_data.is_empty());
	assert(second_copied_data != first_copied_data);
	second_copied_data = first_copied_data;
	assert(second_copied_data.is_not_empty());
	assert(second_copied_data == first_copied_data);

	// clear data
	second_copied_data.clear();
	assert(second_copied_data.is_empty());
	assert(second_copied_data != first_copied_data);

	// get all data
	auto all_data = data.get_all();
	assert(all_data.size() == 2);
	assert(all_data.contains("int_data"));
	assert(all_data.contains("string_data"));
}

void t_tests::t_tile_tests()
{
	// default constructor
	t_tile tile;
	assert(tile.is_blank());
	assert(tile.char_count() == 1);
	assert(tile.data.is_empty());
	assert(tile.get_char().is_blank());
	assert(tile.get_char(0).is_blank());
	assert(tile.get_char() == tile.get_char(0));
	assert(&tile.get_char() == &tile.get_char(0));

	// set first char
	tile.set_char(12, 34, 56);
	assert(tile.is_not_blank());
	assert(tile.char_count() == 1);
	assert(tile.get_char().is_not_blank());
	assert(tile.get_char() == t_char(12, 34, 56));

	// add char
	tile.add_char(23, 45, 67);
	assert(tile.is_not_blank());
	assert(tile.char_count() == 2);
	assert(tile.get_char(1).is_not_blank());
	assert(tile.get_char(1) == t_char(23, 45, 67));

	// set char at index
	tile.set_char(1, 77, 88, 99);

	// copy constructor
	t_tile copy(tile);
	assert(copy == tile);
	assert(copy.is_not_blank());
	assert(copy.char_count() == 2);
	assert(copy.get_char(1).is_not_blank());
	assert(copy.get_char(1) == t_char(77, 88, 99));

	// assignment operator
	t_tile second_copy;
	assert(second_copy.is_blank());
	assert(second_copy != tile);
	second_copy = tile;
	assert(second_copy == tile);
	assert(second_copy.is_not_blank());
	assert(second_copy.char_count() == 2);
	assert(second_copy.get_char(1).is_not_blank());
	assert(second_copy.get_char(1) == t_char(77, 88, 99));
}

void t_tests::t_tilebuf_tests()
{
	// constructor
	t_tilebuffer buf(t_window::cols, t_window::rows);
	assert(buf.cols == t_window::cols);
	assert(buf.rows == t_window::rows);

	// assert all tiles are blank
	for (int y = 0; y < buf.rows; y++) {
		for (int x = 0; x < buf.cols; x++) {
			assert(buf.get_ref(x, y).is_blank());
		}
	}

	// alter tile by reference
	t_tile& tile = buf.get_ref(11, 22);
	tile.set_char('@', 33, 44);
	tile.data.set("Test Data", "This is a test");
	t_char& ch1 = buf.get_ref(11, 22).get_char();
	assert(ch1.ix == '@');
	assert(ch1.fgc == 33);
	assert(ch1.bgc == 44);
	t_tile& tile2 = buf.get_ref(11, 22);
	assert(tile2.data.has("Test Data", "This is a test"));

	// copy tile
	t_tile copy = buf.get_copy(1, 2);
	tile.set_char('#', 55, 66);
	t_char& ch2 = buf.get_ref(1, 2).get_char();
	assert(ch2.is_blank());

	// set tile
	buf.set(copy, 30, 10);
	t_tile& tile3 = buf.get_ref(30, 10);
	assert(tile3 == copy);
}

void t_tests::interpreter_tests()
{
}
