#pragma once

#ifdef ENGINE_PLATFORM_WINDOWS
    #if ENGINE_DYNAMIC_LINK
        #ifdef ENGINE_BUILD_DLL
            #define ENGINE_API __declspec(dllexport) 
        #else
            #define ENGINE_API __declspec(dllimport)
        #endif
    #else
           #define ENGINE_API
    #endif
#else
    #error Engine supports Windows only
#endif

#ifdef ENGINE_ENABLE_ASSERTS
    #define ENGINE_ASSERT(x, ...) { if(!(x)) { ENGINE_ERROR("Assertion Failed : {0}" , __VA_ARGS__); __debugbreak(); } } 
    #define ENGINE_CORE_ASSERT(x, ...) { if(!(x)) { ENGINE_CORE_ERROR("Assertion Failed : {0}" , __VA_ARGS__); __debugbreak(); } } 
#else
    #define ENGINE_ASSERT(x, ...)
    #define ENGINE_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define ENGINE_BIND_EVENT(x) std::bind(&x , this , std::placeholders::_1)
