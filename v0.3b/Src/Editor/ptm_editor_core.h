#pragma once
#include "../Common/common.h"
#include "ptm_editor_immcmd.h"

class ptm_editor_core
{
public:
	void run();

private:
	enum class ptm_editor_mode {
		immcmd, prgedit
	} mode;

	ptm_editor_immcmd immcmd;
};
