#include "t_game.h"

bool t_game::has_var(string var) {
    return vars.find(var) != vars.end();
}
string t_game::get_var(string var) {
    return has_var(var) ? vars[var] : "";
}
