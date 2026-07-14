#include "t_palette.h"
#include "t_filesystem.h"

t_palette::t_palette()
{
	reset();
}

t_palette::t_palette(const t_palette& other)
{
	copy_from(other);
}

t_palette& t_palette::operator=(const t_palette& other)
{
	if (this == &other)
		return *this;

	copy_from(other);

	return *this;
}

void t_palette::copy_from(const t_palette& other)
{
	remove_all();
	for (int i = 0; i < other.colors.size(); i++) {
		colors.emplace_back(other.colors[i]);
	}
}

void t_palette::remove_all()
{
	colors.clear();
}

void t_palette::add(const t_color& color)
{
	colors.emplace_back(color);
}

t_color& t_palette::get(t_index index)
{
	return colors[index];
}

void t_palette::set(t_index index, const t_color& color)
{
	colors[index] = color;
}

int t_palette::size() const
{
	return (int)colors.size();
}

void t_palette::reset()
{
	remove_all();

	add(0x000000);
	add(0x111111);
	add(0x222222);
	add(0x333333);
	add(0x444444);
	add(0x555555);
	add(0x666666);
	add(0x777777);
	add(0x888888);
	add(0x999999);
	add(0xaaaaaa);
	add(0xbbbbbb);
	add(0xcccccc);
	add(0xdddddd);
	add(0xeeeeee);
	add(0xffffff);
	add(0xff8181);
	add(0xff0000);
	add(0xbf3f3f);
	add(0x7f0000);
	add(0x551414);
	add(0x573b3b);
	add(0x8e5555);
	add(0xab7373);
	add(0xc78f8f);
	add(0xe3abab);
	add(0xff6262);
	add(0xd5524a);
	add(0xa5140a);
	add(0xc07872);
	add(0x73413c);
	add(0xda2010);
	add(0xa0695f);
	add(0x401811);
	add(0xff3c0a);
	add(0xf55a32);
	add(0xd08a74);
	add(0x621800);
	add(0xe19b7d);
	add(0xebaa8c);
	add(0xf5b99b);
	add(0xf6c8af);
	add(0x5f3214);
	add(0xf5e1d2);
	add(0xa04b05);
	add(0x7e6e60);
	add(0xda6e0a);
	add(0x7f3f00);
	add(0xbf7f3f);
	add(0xff7f00);
	add(0xffbf81);
	add(0xcbaa89);
	add(0xe3c7ab);
	add(0x8f7357);
	add(0x73573b);
	add(0x3b2d1f);
	add(0xb45a00);
	add(0xc49e73);
	add(0xffa53c);
	add(0xd79b0f);
	add(0xf6bd31);
	add(0xa6a090);
	add(0x8c805a);
	add(0xffd510);
	add(0xac9400);
	add(0xe6d55a);
	add(0xffea4a);
	add(0x53500a);
	add(0xffffbf);
	add(0xffff00);
	add(0xbfbf3f);
	add(0x7f7f00);
	add(0x414123);
	add(0x73733b);
	add(0x8f8f57);
	add(0xa2a255);
	add(0xb5b572);
	add(0xc7c78f);
	add(0xdadaab);
	add(0xededc7);
	add(0x626200);
	add(0xb1b10a);
	add(0x283405);
	add(0xc8ff41);
	add(0x465032);
	add(0x191e0f);
	add(0x96dc19);
	add(0x6aa805);
	add(0x73c805);
	add(0x8ebe55);
	add(0xc7e3ab);
	add(0xabc78f);
	add(0x738f57);
	add(0x9bf046);
	add(0x3c6e14);
	add(0x587d3e);
	add(0x204608);
	add(0x149605);
	add(0x7dff73);
	add(0x14e60a);
	add(0x007f00);
	add(0x3fbf3f);
	add(0x00ff00);
	add(0xafffaf);
	add(0x3b573b);
	add(0x506450);
	add(0x578f57);
	add(0x73ab73);
	add(0x8fc78f);
	add(0xa2d8a2);
	add(0x0c5c0c);
	add(0x0ad70a);
	add(0x4bf05a);
	add(0x00c514);
	add(0x87b48e);
	add(0x3b7349);
	add(0x64c082);
	add(0x507d5f);
	add(0x1e2d23);
	add(0xb4eeca);
	add(0x05b450);
	add(0x235037);
	add(0x1c8c4e);
	add(0xabe3c5);
	add(0x00de6a);
	add(0x3cfea5);
	add(0x0f6946);
	add(0x2deba8);
	add(0x6affcd);
	add(0x06c491);
	add(0x129880);
	add(0x123832);
	add(0x08ded5);
	add(0x007f7f);
	add(0x3fbfbf);
	add(0x00ffff);
	add(0xbfffff);
	add(0x7e9494);
	add(0x3b7373);
	add(0x64abab);
	add(0x8fc7c7);
	add(0xabe3e3);
	add(0xc7f1f1);
	add(0x055a5c);
	add(0xe1f8fa);
	add(0x234146);
	add(0x55e6ff);
	add(0x91ebff);
	add(0x6e8287);
	add(0x7dd7f0);
	add(0x00bfff);
	add(0x109cde);
	add(0x5ac5ff);
	add(0x699dc3);
	add(0x007fff);
	add(0xabc7e3);
	add(0x8fabc7);
	add(0x578fc7);
	add(0x57738f);
	add(0x3b5773);
	add(0x326496);
	add(0x186abd);
	add(0x4aa4ff);
	add(0x004a9c);
	add(0x2378dc);
	add(0x4b7dc8);
	add(0xbed2f0);
	add(0x162c52);
	add(0x0f377d);
	add(0x0c2148);
	add(0xa8b9dc);
	add(0x0f192d);
	add(0x0052f6);
	add(0x90b0ff);
	add(0xd0daf8);
	add(0x4a5aff);
	add(0x0010bd);
	add(0x101cda);
	add(0x8181ff);
	add(0x0000ff);
	add(0x3f3fbf);
	add(0x00007f);
	add(0x0f0f50);
	add(0x1f1f3b);
	add(0x3b3b57);
	add(0x494973);
	add(0x57578f);
	add(0x7676ca);
	add(0x8f8fc7);
	add(0xababe3);
	add(0xe3e3ff);
	add(0x3c3cf5);
	add(0x736eaa);
	add(0xbeb9fa);
	add(0x786ef0);
	add(0x231094);
	add(0x6241f6);
	add(0xb991ff);
	add(0xd7c3fa);
	add(0x5010b0);
	add(0x6010d0);
	add(0x9c41ff);
	add(0x7f00ff);
	add(0xab8fc7);
	add(0x8f57c7);
	add(0x73578f);
	add(0x573b73);
	add(0x8732d2);
	add(0xd7a5ff);
	add(0xbd62ff);
	add(0x5a187b);
	add(0x410062);
	add(0x320a46);
	add(0xbd29ff);
	add(0x8c14be);
	add(0xbcafc0);
	add(0xe673ff);
	add(0xf8c6fc);
	add(0xbd10c5);
	add(0xda20e0);
	add(0xfd81ff);
	add(0x7f007f);
	add(0xbf3fbf);
	add(0xf500f5);
	add(0x3c233c);
	add(0x463246);
	add(0x724072);
	add(0x8f578f);
	add(0xab57ab);
	add(0xab73ab);
	add(0xe3c7e3);
	add(0xff52ff);
	add(0x641464);
	add(0xebace1);
	add(0xa01982);
	add(0xc78fb9);
	add(0xffdcf5);
	add(0x280a1e);
	add(0xff50bf);
	add(0xe1b9d2);
	add(0xff6ac5);
	add(0xc80078);
	add(0xd7a0be);
	add(0xc35a91);
	add(0x551937);
	add(0xc87da0);
	add(0x321623);
	add(0xe61e78);
	add(0x4b2837);
	add(0xfc3a8c);
	add(0xfaa0b9);
	add(0x911437);
	add(0x98344d);
	add(0xbd1039);
	add(0xf8d2da);
	add(0xffc0cb);
}

void t_palette::load(const t_string& filename)
{
	remove_all();
	t_filesystem::load_palette_plaintext(this, filename);
}

void t_palette::save(const t_string& filename)
{
	t_filesystem::save_palette_plaintext(this, filename);
}
