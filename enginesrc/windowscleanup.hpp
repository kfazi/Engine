#define WIN32_MEAN_AND_LEAN
#define NOMINMAX

/** Define std::min and std::max */
#ifdef _cpp_min
#undef min
#undef max
#define min _cpp_min
#define max _cpp_max
#endif /* _cpp_min */

/* EOF */

