#pragma once
#include <Windows.h>
#include <Psapi.h>
#include "common.h"

struct t_performance_monitor {
	t_performance_monitor();
	~t_performance_monitor();
	string format_info();
private:
	friend int perfmon_thread_run(void* dummy);
	static double calculate_cpu_usage();
	static size_t get_working_memory_usage_mb();
};
