#pragma once
#include "Defines.h"

#define ASSERTIONS_ENABLED

#ifdef ASSERTIONS_ENABLED
#if _MSC_VER
#include <intrin.h>
#define debugBreak() __debugbreak()
#else
#define debugBreak() __builtin_trap()
#endif // _MSV_VER

namespace TextureGenEngine {

	TAPI void ReportAssertionFailure(const char* expression, const char* file, int line, const char* message = nullptr);

#define THAUMA_ASSERT(expr) \
{ \
	if (expr) {} \
	else \
	{ \
		TextureGenEngine::ReportAssertionFailure(#expr, __FILE__, __LINE__); \
		debugBreak(); \
	} \
}

#define THAUMA_ASSERT_MSG(expr, msg) \
{ \
	if (expr) {} \
	else \
	{ \
		TextureGenEngine::ReportAssertionFailure(#expr, __FILE__, __LINE__, msg); \
		debugBreak(); \
	} \
}
#ifdef TDEBUG
#define THAUMA_ASSERT_DEBUG(expr)  \
{ \
	if (expr) {} \
	else \
	{ \
		TextureGenEngine::ReportAssertionFailure(#expr, __FILE__, __LINE__); \
		debugBreak(); \
	} \
}
#else
#define THAUMA_ASSERT_DEBUG(expr)
#endif // TDEBUG

#else 
#define THAUMA_ASSERT(expr)
#define THAUMA_ASSERT_MSG(expr, msg)
#define THAUMA_ASSERT_DEBUG(expr)


#endif // ASSERTIONS_ENABLED

}