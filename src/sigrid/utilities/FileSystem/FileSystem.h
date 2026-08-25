#pragma once

#include <optional>

#include "sigrid/utilities/String/String.h"

namespace sigrid_filesystem{

bool exists(const sigrid::String& filename);

bool createFolderForFile(const sigrid::String filename);

std::optional<sigrid::String> getFilenameFromDialog();

}  // namespace sigrid_filesystem