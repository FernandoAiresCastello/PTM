#include "t_char.h"

t_char::t_char() : ix(0), fgc(0), bgc(0) 
{
}

t_char::t_char(t_index ix, t_index fgc, t_index bgc) : ix(ix), fgc(fgc), bgc(bgc)
{
}

t_char::t_char(const t_char& other) : ix(other.ix), fgc(other.fgc), bgc(other.bgc)
{
}

bool t_char::operator==(const t_char& other) const
{
	return ix == other.ix && fgc == other.fgc && bgc == other.bgc;
}

t_char& t_char::operator=(const t_char& other)
{
    if (this == &other)
        return *this;

    ix = other.ix;
    fgc = other.fgc;
    bgc = other.bgc;

    return *this;
}

void t_char::set(t_index ix, t_index fgc, t_index bgc)
{
    this->ix = ix;
    this->fgc = fgc;
    this->bgc = bgc;
}

void t_char::set_blank()
{
    ix = 0;
    fgc = 0;
    bgc = 0;
}

bool t_char::is_blank() const
{
    return ix == 0 && fgc == 0 && bgc == 0;
}

bool t_char::is_not_blank() const
{
    return !is_blank();
}

t_char t_char::blank()
{
    return t_char(0, 0, 0);
}
