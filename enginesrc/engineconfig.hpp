#ifndef ENGINE_ENGINECONFIG_HPP
#define ENGINE_ENGINECONFIG_HPP

/** The constant frames per second value. */
#define ENGINE_FPS (60)

/** The interval between FPS counter refreshes in seconds. */
#define ENGINE_FPS_COUNTER_INTERVAL (0.2)

/** Should rendering be constrained by the ENGINE_FPS value. */
#define ENGINE_CONSTRAIN_FPS

/** Default configuration file. */
#define ENGINE_DEFAULT_CONFIG_FILE ("config.cfg")

/**
 * The internal engine's string char type.
 * Possible values are:
 * - 0 for UTF32
 * - 1 for UTF16
 * On modern machines, where memory is not a concern UTF32 is preferred over UTF16.
 */
#define ENGINE_STRING_CHAR 0

#define OPENGL_ALPHA (8)
#define OPENGL_DEPTH (24)
#define OPENGL_STENCIL (24)

#endif /* ENGINE_ENGINECONFIG_HPP */

/* EOF */
