#ifndef ENGINE_WINDOWS_CLEANUP_HPP
#define ENGINE_WINDOWS_CLEANUP_HPP

/* Correcting windows fuckups. */

#define WIN32_MEAN_AND_LEAN
#define NOMINMAX
#define NOGDI

#if !defined(_WIN32_WINNT) || _WIN32_WINNT < 0x0600
/* Vista minimum */
//#define _WIN32_WINNT (0x0600)
#endif

#endif /* ENGINE_WINDOWS_CLEANUP_HPP */

/* EOF */

