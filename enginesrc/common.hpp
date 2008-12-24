#ifndef ENGINE_COMMON_HPP
#define ENGINE_COMMON_HPP

/* Check against stupidity. */
#if (defined WINDOWS && defined UNIX) || (defined WINDOWS && defined OSX) || (defined UNIX && defined OSX)
#error DEFINE ONLY ONE PLATFORM
#endif /* (defined WINDOWS && defined UNIX) || (defined WINDOWS && defined OSX) || (defined UNIX && defined OSX) */
#if !defined WINDOWS && !defined UNIX && !defined OSX
#error NO PLATFORM DEFINED
#endif /* !defined WINDOWS && !defined UNIX && !defined OSX */
/* Stupidity prevented. */

/* engineconfig.hpp file must be located in game's directory. */
#include <engineconfig.hpp>

#endif /* ENGINE_COMMON_HPP */

#ifdef WINDOWS
#include "windowscleanup.hpp"
#endif /* WINDOWS */

/* EOF */

