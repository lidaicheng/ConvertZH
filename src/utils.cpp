#include "utils.h"
#include <string>
#include <windows.h>

// Use Windows API for Simplified/Traditional Chinese conversion
std::string convertTextUsingWindowsAPI(const std::string& input, DWORD conversionFlags) {
    // Convert UTF-8 string to wide character
    int wideLen = MultiByteToWideChar(CP_UTF8, 0, input.c_str(), -1, NULL, 0);
    if (wideLen <= 0) return input;
    
    std::wstring wideInput(wideLen - 1, 0);
    MultiByteToWideChar(CP_UTF8, 0, input.c_str(), -1, &wideInput[0], wideLen);
    
    // Use Windows API for conversion
    std::wstring wideResult(wideInput.length() * 2, 0);
    DWORD resultLen = LCMapStringW(LOCALE_SYSTEM_DEFAULT, conversionFlags, 
                                  wideInput.c_str(), -1, 
                                  &wideResult[0], static_cast<int>(wideResult.length()));
    
    if (resultLen > 0) {
        wideResult.resize(resultLen - 1);
        
        // Convert wide character back to UTF-8
        int utf8Len = WideCharToMultiByte(CP_UTF8, 0, wideResult.c_str(), -1, NULL, 0, NULL, NULL);
        if (utf8Len > 0) {
            std::string result(utf8Len - 1, 0);
            WideCharToMultiByte(CP_UTF8, 0, wideResult.c_str(), -1, &result[0], utf8Len, NULL, NULL);
            return result;
        }
    }
    
    return input; // Conversion failed, return original text
}

namespace utils {

std::string SimplifiedToTrad(const std::string& input) {
    // Use Windows API for Simplified to Traditional Chinese conversion
    return convertTextUsingWindowsAPI(input, LCMAP_TRADITIONAL_CHINESE);
}

std::string TraditionalToSimp(const std::string& input) {
    // Use Windows API for Traditional to Simplified Chinese conversion
    return convertTextUsingWindowsAPI(input, LCMAP_SIMPLIFIED_CHINESE);
}

} // namespace utils