#pragma once

#include <xtrap/all.h>
#pragma comment(lib, "xtrap.lib")

#define THROW(exception) XTRAP_THROW(exception)
#define THROW_EXCEPTION(msg) XTRAP_THROW_EXCEPTION(msg)
#define THROW_NOT_IMPLEMENTED(msg) XTRAP_THROW_NOT_IMPLEMENTED(msg)
#define THROW_NOT_SUPPORTED(msg) XTRAP_THROW_NOT_SUPPORTED(msg)
#define THROW_INVALID_STATE(msg) XTRAP_THROW_INVALID_STATE(msg)
#define THROW_ARGUMENT_ERROR(arg, details) XTRAP_THROW_ARGUMENT_ERROR(arg, details)
#define THROW_ARGUMENT_NULL(arg) XTRAP_THROW_ARGUMENT_NULL(arg)

namespace xTunnel
{
    using namespace xtrap;
}
