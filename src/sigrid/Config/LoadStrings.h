#pragma once

#include "sigrid/utilities/String/String.h"
#include "sigrid/utilities/lists/Vector.h"
#include "sigrid/utilities/InputStream/InputStream.h"

namespace sigrid_config{

bool loadStrings(sigrid_list::Vector<sigrid::String>& strings, sigrid::InputStream& is);

}  // namespace sigrid_config