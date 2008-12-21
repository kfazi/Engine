#ifndef ENGINE_WINDOWS_CLEANUP_HPP
#define ENGINE_WINDOWS_CLEANUP_HPP

/** Remove ERROR constant defined in WinGDI */
#undef ERROR

/** Define std::min and std::max */
#ifdef _cpp_min
#undef min
#undef max
#define min _cpp_min
#define max _cpp_max
#endif /* _cpp_min */

#endif /* ENGINE_WINDOWS_CLEANUP_HPP */

/* EOF */

