#pragma once

#if HZ_PROFILE
#include "../../vendor/Tracy/Tracy.hpp"
#define HZ_PROFILE_BEGIN_SESSION(name, filepath)
#define HZ_PROFILE_END_SESSION()
#define HZ_PROFILE_SCOPE(name) ZoneScopedN(name)
#define HZ_PROFILE_FUNCTION() ZoneScoped
#define HZ_PROFILE_FRAMEMARKER() FrameMark
#else
#define HZ_PROFILE_BEGIN_SESSION(name, filepath)
#define HZ_PROFILE_END_SESSION()
#define HZ_PROFILE_SCOPE(name)
#define HZ_PROFILE_FUNCTION()
#define HZ_PROFILE_FRAMEMARKER()
#endif
