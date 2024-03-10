#ifndef AVRHAL_VERSION_H_
#define AVRHAL_VERSION_H_

#ifndef AVRHAL_VER_MAJOR
#warning "Unspecified AVRHAL lib version number. Falling back to 1.x"
#define AVRHAL_VER_MAJOR 1
#endif

#if AVRHAL_VER_MAJOR > 1
#error Unsupported AVRHAL lib version
#endif

#endif
