/* Please refer to license.txt */

#include "build_config.hpp"

#include "config/config.hpp"
#include "data/data.hpp"

#ifdef SQLITE_FOUND
#include "data/sqlite.hpp"
#endif

#include "error/error.hpp"
#include "file/file.hpp"
#include "graphic/graphic.hpp"
#include "graphic/2d/2d.hpp"
#include "graphic/window/window.hpp"
#include "interface/interface.hpp"
#include "math/math.hpp"
#include "net/client/client.hpp"
#include "net/server/server.hpp"
#include "misc/rand.hpp" //Random <something> generation.
#include "misc/time.hpp" //Time related stuff.
#include "string/string.hpp"
