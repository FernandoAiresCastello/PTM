#include "t_tileflags.h"

t_tileflags::t_tileflags() : 
    visible(true), monochrome(false), hide_bgc(false)
{
}

bool t_tileflags::operator==(const t_tileflags& other) const
{
    return 
        visible == other.visible &&
        monochrome == other.monochrome &&
        hide_bgc == other.hide_bgc;
}
