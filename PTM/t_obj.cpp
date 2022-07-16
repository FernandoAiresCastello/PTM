#include "t_obj.h"

t_obj& t_obj::operator=(const t_obj& other) {
    tile = other.tile;
    prop = other.prop;
    return *this;
}
