//
//  ResourceManager.cpp
//  Fireworks
//
//  Created by 郭珂桢 on 2025/2/17.
//

#include "ResourceManager.hpp"
#include "Constants.h"

#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <filesystem>

std::vector<std::map<std::string, float>> ResourceManager::allFireworkProperties;

std::random_device ResourceManager::rd;
std::default_random_engine ResourceManager::generator(rd());


std::map<std::string, glm::vec3> ResourceManager::colorsMap = {
    {"red", RED},
    {"green", GREEN},
    {"blue", BLUE},
    {"pink", PINK},
    {"purple", PURPLE},
    {"orange", ORANGE},
    {"light_blue", LIGHT_BLUE},
    {"maganta", MAGANTA},
    {"cyan", CYAN},
    {"yellow", YELLOW},
};


void ResourceManager::loadAllProperties()
{
    const std::string dir = "/Users/guokezhen/Desktop/计算机/计算机图形学/Opengl Project/Fireworks/Fireworks/res/fireworkProperties";
    // 获取路径下所有文件路径
    std::vector<std::string> filePaths;
    try {
        for (const auto & entry : std::filesystem::directory_iterator(dir))
        {
            if (std::filesystem::is_regular_file(entry))
            {
                filePaths.push_back(entry.path().filename().string());
            }
        }
    } catch (const std::exception & e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    // 读取文件
    std::vector<std::map<std::string, float>> allProperties;
    for (std::string filePath : filePaths)
    {
        std::cout << filePath << std::endl;
        allFireworkProperties.push_back(loadParticleProperties(dir + '/' + filePath));
    }
}

std::map<std::string, float> ResourceManager::loadParticleProperties(std::string filePath)
{
    std::map<std::string, float> properties;
    // 打开文件
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cout << "Failed to oen file " << filePath << std::endl;
        return properties;
    }
    
    std::string line;
    while (std::getline(file, line))
    {
        // 在每一行中找到冒号分隔符
        std::stringstream ss(line);
        std::string key;
        std::string valueStr;
        
        if (std::getline(ss, key, ':') && std::getline(ss, valueStr))
        {
            try {
                float value = std::stof(valueStr);
                properties[key] = value;
            } catch (const std::invalid_argument & e) {
                std::cerr << "Invalid float value in line: " << line << std::endl;
            }
        }
        
    }
    
    file.close();
    
    return properties;
}

