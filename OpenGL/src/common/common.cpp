#include "common/common.h"
#include <fstream>
#include <sstream>

std::optional<std::string> LoadTextFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        SPDLOG_ERROR("Failed to open file: {}", filename);
        return std::nullopt;
    }

    std::stringstream string;
    string << file.rdbuf();
    return string.str();
}