//
//  ResourceManager.hpp
//  Fireworks
//
//  Created by 郭珂桢 on 2025/2/17.
//

#ifndef ResourceManager_hpp
#define ResourceManager_hpp

#include <map>
#include <vector>
#include <random>

#include <glm/glm.hpp>

class ResourceManager
{
public:
    static std::vector<std::map<std::string, float>> allFireworkProperties;
    
    static std::map<std::string, glm::vec3> colorsMap;
    
    static std::random_device rd;
    
    static std::default_random_engine generator;

    static void loadAllProperties();
    
        
private:
    static std::map<std::string, float> loadParticleProperties(std::string filePath);
    
};

#endif /* ResourceManager_hpp */
