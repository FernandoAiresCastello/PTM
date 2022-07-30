#include "t_performance_monitor.h"

bool perfmon_thread_running = false;
double cached_cpu_usage = 0.0;

int perfmon_thread_run(void* dummy) {
    perfmon_thread_running = true;
    while (perfmon_thread_running) {
        cached_cpu_usage = t_performance_monitor::calculate_cpu_usage();
        SDL_Delay(1000);
    }
    return 0;
}

HANDLE self;
ULARGE_INTEGER lastCPU, lastSysCPU, lastUserCPU;
int numProcessors;

t_performance_monitor::t_performance_monitor() {
    SYSTEM_INFO sysInfo;
    FILETIME ftime, fsys, fuser;

    GetSystemInfo(&sysInfo);
    numProcessors = sysInfo.dwNumberOfProcessors;

    GetSystemTimeAsFileTime(&ftime);
    memcpy(&lastCPU, &ftime, sizeof(FILETIME));

    self = GetCurrentProcess();
    GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
    memcpy(&lastSysCPU, &fsys, sizeof(FILETIME));
    memcpy(&lastUserCPU, &fuser, sizeof(FILETIME));

    SDL_CreateThread(perfmon_thread_run, "perfmon_thread_run", nullptr);
}
t_performance_monitor::~t_performance_monitor() {
    perfmon_thread_running = false;
}
double t_performance_monitor::calculate_cpu_usage() {
    FILETIME ftime, fsys, fuser;
    ULARGE_INTEGER now, sys, user;
    double percent;

    GetSystemTimeAsFileTime(&ftime);
    memcpy(&now, &ftime, sizeof(FILETIME));

    GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
    memcpy(&sys, &fsys, sizeof(FILETIME));
    memcpy(&user, &fuser, sizeof(FILETIME));
    percent = (sys.QuadPart - lastSysCPU.QuadPart) + (user.QuadPart - lastUserCPU.QuadPart);
    percent /= (now.QuadPart - lastCPU.QuadPart);
    percent /= numProcessors;
    lastCPU = now;
    lastUserCPU = user;
    lastSysCPU = sys;

    return percent * 100;
}
size_t t_performance_monitor::get_working_memory_usage_mb() {
    PROCESS_MEMORY_COUNTERS_EX pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
    return pmc.WorkingSetSize;
}
string t_performance_monitor::format_info() {
    return String::Format(
        "CPU: %.0f%% | RAM: %s", 
        cached_cpu_usage, 
        Util::FormatNumberOfBytes(get_working_memory_usage_mb()).c_str());
}
