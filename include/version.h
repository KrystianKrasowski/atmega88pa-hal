#ifndef AVRHAL_VERSION_H_
#define AVRHAL_VERSION_H_

#ifndef AVRHAL_VER_MAJOR
#error Unspecified AVRHAL lib version number.
#endif

#if AVRHAL_VER_MAJOR > 1
#error Unsupported AVRHAL lib version
#endif

#endif
