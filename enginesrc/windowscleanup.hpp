#ifndef ENGINE_WINDOWS_CLEANUP_HPP
#define ENGINE_WINDOWS_CLEANUP_HPP

/* Correcting windows fuckups. */

#define WIN32_MEAN_AND_LEAN
#define NOMINMAX
//#define NOGDI

#if !defined(_WIN32_WINNT) || _WIN32_WINNT < 0x0600
#define _WIN32_WINNT 0x0600 /* Vista minimum */
#endif

/** Define std::min and std::max */
/*
#ifdef _cpp_min
#undef std::min
#undef std::max
template<class CType> const CType &std::min(const CType &x, const CType &y)
{
	return _cpp_min(x, y);
}

template<class CType> const CType &std::max(const CType &x, const CType &y)
{
	return _cpp_max(x, y);
}
#endif /* _cpp_min */

#endif /* ENGINE_WINDOWS_CLEANUP_HPP */

/* EOF */

