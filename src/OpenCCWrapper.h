#pragma once
#include <string>

// OpenCC 包装器类
// 提供简化的简繁转换接口
class OpenCCWrapper {
public:
    static bool Initialize();
    static void Cleanup();
    static std::string SimplifiedToTraditional(const std::string& input);
    static std::string TraditionalToSimplified(const std::string& input);
    static bool IsInitialized();

private:
    static bool initialized;
    static void* s2t_converter;
    static void* t2s_converter;
    
    // 内部转换函数
    static std::string ConvertText(const std::string& input, bool toTraditional);
    static void InitializeCharMaps();
    static void AddCharPair(const wchar_t* simp, const wchar_t* trad);
};
