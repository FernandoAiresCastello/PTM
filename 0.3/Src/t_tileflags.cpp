#include "t_tileflags.h"

t_tileflags::t_tileflags()
{
    clear();
}

t_tileflags::t_tileflags(const t_tileflags& other) :
    visible(other.visible), monochrome(other.monochrome), 
    hide_bgc(other.hide_bgc)
{
}

bool t_tileflags::operator==(const t_tileflags& other) const
{
    return
        visible == other.visible &&
        monochrome == other.monochrome &&
        hide_bgc == other.hide_bgc;
}

t_tileflags& t_tileflags::operator=(const t_tileflags& other)
{
    if (this == &other)
        return *this;

    visible = other.visible;
    monochrome = other.monochrome;
    hide_bgc = other.hide_bgc;

    return *this;
}

void t_tileflags::clear()
{
    visible = true;
    monochrome = true;
    hide_bgc = false;
}
