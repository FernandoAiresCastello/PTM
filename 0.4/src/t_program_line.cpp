#include "t_program_line.h"

t_program_line& t_program_line::operator=(const t_program_line& other)
{
    if (this == &other)
        return *this;

    immediate = other.immediate;
    is_label = other.is_label;
    is_comment = other.is_comment;
    label = other.label;
    line_nr = other.line_nr;
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

const t_string& t_program_line::to_string() const
{
    return src;
}
