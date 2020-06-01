#pragma once

#if HZ_PROFILE
#include "../../vendor/Tracy/Tracy.hpp"
#define HZ_PROFILE_BEGIN_SESSION(name, filepath)
#define HZ_PROFILE_END_SESSION()
#define HZ_PROFILE_SCOPE(name) ZoneScopedN(name)
#define HZ_PROFILE_FUNCTION() ZoneScoped
#define HZ_PROFILE_FRAMEMARKER() FrameMark
#define HZ_PROFILE_LOCK(type, var, name) TracyLockableN(type, var, name)
#define HZ_PROFILE_LOCKMARKER(var) LockMark(var)
#else
#define HZ_PROFILE_BEGIN_SESSION(name, filepath)
#define HZ_PROFILE_END_SESSION()
#define HZ_PROFILE_SCOPE(name)
#define HZ_PROFILE_FUNCTION()
#define HZ_PROFILE_FRAMEMARKER()
#define HZ_PROFILE_LOCK(type, var, name) type var
#define HZ_PROFILE_LOCKMARKER(var)
#endif
