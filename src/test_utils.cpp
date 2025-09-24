#include "utils.h"
#include <iostream>
#include <string>

int main() {
    // 测试简体转繁体
    std::string simp_text = "简体中文测试";
    std::string trad_result = utils::SimplifiedToTrad(simp_text);
    std::cout << "简体: " << simp_text << std::endl;
    std::cout << "繁体: " << trad_result << std::endl;
    
    // 测试繁体转简体
    std::string trad_text = "繁體中文測試";
    std::string simp_result = utils::TraditionalToSimp(trad_text);
    std::cout << "繁体: " << trad_text << std::endl;
    std::cout << "简体: " << simp_result << std::endl;
    
    // 测试更多字符
    std::string test_text = "这是一个测试，包含标点符号！";
    std::string converted = utils::SimplifiedToTrad(test_text);
    std::cout << "原文: " << test_text << std::endl;
    std::cout << "转换: " << converted << std::endl;
    
    return 0;
}
