#include "utils/ConfigManager.h"
#include "utils/ConfigManager.h"
#include <fstream>
#include <sstream>
#include <iostream>

ConfigManager::ConfigManager(const std::string& filename) {
    parseFile(filename);
}

void ConfigManager::parseFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Opennig config file is not possible";
        return;
    }
    std::string line, section;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        if (line[0] == '[') {
            section = line.substr(1, line.find("]") - 1);
        } else {
                std::istringstream iss(line);
                std::string key, value;
                if (std::getline(iss, key, '=') && std::getline(iss, value)) {
                    configData[section][key] = value;
                }
        }
    }
}

std::string ConfigManager::get(const std::string& section, const std::string& key) const {
    auto secIt = configData.find(section);
    if (secIt != configData.end()) {
        auto keyIt = secIt->second.find(key);
        if (keyIt != secIt->second.end()) {
            return keyIt->second;
        }
    }
    return "";
}

int ConfigManager::getInt(const std::string& section, const std::string& key) const {
    std::string value = get(section, key);
    if (value.empty()) {
        std::cerr << "Clave '" << key << "' no encontrada en sección '" << section << "'\n";
        return -1; // o un valor por defecto
    }
    try {
        return std::stoi(value);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Valor inválido para '" << key << "': " << value << "\n";
        return -1;
    }
}