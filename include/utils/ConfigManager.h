#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include <string>
#include <map>

class ConfigManager {
public:
    explicit ConfigManager(const std::string& filename);
    std::string get(const std::string& section, const std::string& key) const;
    int getInt(const std::string& section, const std::string& key) const;
private:
    std::map<std::string, std::map<std::string, std::string>> configData;
    void parseFile(const std::string& filename);
};

#endif
