#pragma once

namespace xutil
{
    void ExitApplication(int exit_code = -1);
    void RestartApplication(int secs_to_wait = 2, string working_dir = "", void (*exit_function)() = nullptr);
    unsigned GetApplicationProcessID();
}
