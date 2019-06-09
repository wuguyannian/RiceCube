#pragma once

#ifdef _DEBUG
#define RICE_ENABLE_ASSERTS
#endif

#ifdef RICE_ENABLE_ASSERTS

#define RICE_ASSERTS(x, ...) { if(!(x)) {RICE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}

#else

#define RICE_ASSERTS(x, ...)

#endif

#define BIT(b) (1 << b)

#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)