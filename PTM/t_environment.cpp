#include "t_environment.h"

bool t_environment::has_var(string var) {
    return vars.find(var) != vars.end();
}
string t_environment::get_var(string var) {
    return has_var(var) ? vars[var] : "";
}
