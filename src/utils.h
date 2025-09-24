#ifndef UTILS_H
#define UTILS_H

#include <string>

namespace utils {
    // Simplified to Traditional Chinese conversion
    std::string SimplifiedToTrad(const std::string& input);
    
    // Traditional to Simplified Chinese conversion
    std::string TraditionalToSimp(const std::string& input);
}

#endif //UTILS_H
