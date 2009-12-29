#ifndef COMMON_INTERNAL_HPP
#define COMMON_INTERNAL_HPP

/* Check against stupidity. */
#if (defined WINDOWS && defined UNIX) || (defined WINDOWS && defined OSX) || (defined UNIX && defined OSX)
#error DEFINE ONLY ONE PLATFORM
#endif /* (defined WINDOWS && defined UNIX) || (defined WINDOWS && defined OSX) || (defined UNIX && defined OSX) */
#if !defined WINDOWS && !defined UNIX && !defined OSX
#error NO PLATFORM DEFINED
#endif /* !defined WINDOWS && !defined UNIX && !defined OSX */
/* Stupidity prevented. */

/* Compiler dependent DLL macros */
#ifdef WINDOWS
#ifdef __MINGW32__
#else /* __MINGW32__ */
#ifdef CommonLib_EXPORTS
#define COMMONDLLIMPORTEXPORT __declspec(dllexport)
#else
#define COMMONDLLIMPORTEXPORT __declspec(dllimport)
#endif /* common_EXPORTS */
#endif /* __MINGW32__ */
#endif /* WINDOWS */

#include "Memory/new.hpp"
#include "Errors/Assert.hpp"
#include "Memory/CDefaultAllocator.hpp"

#endif /* COMMON_INTERNAL_HPP */

/* EOF */

