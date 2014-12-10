#include "stdafx.h"
#include "path.h"

namespace xutil
{
#ifdef WIN32
    string GetApplicationPath()
    {
        char path[MAX_PATH + 1];
        if (!GetModuleFileName(NULL, path, MAX_PATH + 1))
        {
            throw SystemError("Failed to retrieve applicatin path");
        }

        return string(path);
    }
#endif

    string ExtractFileName(const string& path)
    {
        unsigned pos = path.find_last_of("/\\");
        if (pos == string::npos)
        {
            return path;
        }

        return path.substr(pos + 1);
    }

    string ExtractParentDirectory(const string& path)
    {
        unsigned count = path.length();
        if (!count)
        {
            return "";
        }

        char last_char = path[count - 1];
        if (last_char == '/' || last_char == '\\')
        {
            count--;
        }

        unsigned pos = path.find_last_of("/\\", 0, count);
        if (pos == string::npos)
        {
            return "";
        }

        return path.substr(0, pos);
    }

    string GetApplicationDirectory()
    {
        string app_path = GetApplicationPath();
        string app_dir = ExtractParentDirectory(app_path);
        return app_dir;
    }
}
