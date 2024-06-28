#include "t_program_line.h"

t_program_line& t_program_line::operator=(const t_program_line& other)
{
    if (this == &other)
        return *this;

    src_line_nr = other.src_line_nr;
    src = other.src;
    has_error = other.has_error;
    fn = other.fn;
    argc = other.argc;
    arg1 = other.arg1;
    arg2 = other.arg2;
    arg3 = other.arg3;
    arg4 = other.arg4;
    arg5 = other.arg5;

    return *this;
}
