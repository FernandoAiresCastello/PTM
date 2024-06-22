#include "t_tileflags.h"

t_tileflags::t_tileflags()
{
}

t_tileflags::t_tileflags(const t_tileflags& other) :
    visible(other.visible), monochrome(other.monochrome), 
    hide_bgc(other.hide_bgc), line_wrap(other.line_wrap)
{
}

bool t_tileflags::operator==(const t_tileflags& other) const
{
    return 
        visible == other.visible &&
        monochrome == other.monochrome &&
        hide_bgc == other.hide_bgc &&
        line_wrap == other.line_wrap;
}

t_tileflags& t_tileflags::operator=(const t_tileflags& other)
{
    if (this == &other)
        return *this;

    visible = other.visible;
    monochrome = other.monochrome;
    hide_bgc = other.hide_bgc;
    line_wrap = other.line_wrap;

    return *this;
}
