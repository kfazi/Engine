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

#include "engineconfig.hpp"

#endif /* ENGINE_COMMON_HPP */

#ifdef WINDOWS
#include "windowscleanup.hpp"
#endif /* WINDOWS */

/* Compiler dependent DLL macros */
#ifdef WINDOWS
#ifdef __MINGW32__
#else /* __MINGW32__ */
#ifdef engine_EXPORTS
#define DLLFUNCTION __declspec(dllexport)
#else
#define DLLFUNCTION __declspec(dllimport)
#endif /* engine_EXPORTS */
#endif /* __MINGW32__ */
#endif /* WINDOWS */

/* EOF */

