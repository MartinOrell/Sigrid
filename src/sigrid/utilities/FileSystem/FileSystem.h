#pragma once

#include <optional>

#include "sigrid/utilities/String/String.h"

namespace sigrid_filesystem{

std::optional<sigrid::String> getFilenameFromDialog();

}  // namespace sigrid_filesystem