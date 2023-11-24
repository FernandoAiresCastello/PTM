#pragma once
#include "../Common/common.h"
#include "ptm_api.h"

class ptm_system
{
public:
	ptm_system();
	~ptm_system();

	void run();

private:
	ptm_api api;

	void show_intro();
};
