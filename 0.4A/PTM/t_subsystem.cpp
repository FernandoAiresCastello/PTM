#include "t_subsystem.h"

t_subsystem::t_subsystem()
{
}

t_subsystem::~t_subsystem()
{
}

bool t_subsystem::is_active() const
{
	return active;
}

void t_subsystem::activate()
{
	active = true;
}

void t_subsystem::deactivate()
{
	active = false;
}
