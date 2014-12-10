#pragma once

namespace xutil
{
    string ExtractFileName(const string& path);
    string ExtractParentDirectory(const string& path);

    string GetApplicationPath();
    string GetApplicationDirectory();
}