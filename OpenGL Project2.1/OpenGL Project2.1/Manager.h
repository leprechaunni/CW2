#pragma once

#include <string>
#include <memory>
#include <map>

namespace RenderEngine
{
    class ShaderProgram;
    class Texture2D;
}


class Manager {
public:
    Manager(const std::string& executablePath);
    ~Manager() = default;

    Manager(const Manager&) = delete;
    Manager& operator=(const Manager&) = delete;
    Manager& operator=(Manager&&) = delete;
    Manager(Manager&&) = delete;

    std::shared_ptr<RenderEngine::ShaderProgram> loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath);
    std::shared_ptr<RenderEngine::ShaderProgram> getShaderProgram(const std::string& shaderName);
    std::shared_ptr<RenderEngine::Texture2D> loadTexture(const std::string& textureName, const std::string& texturePath);
    std::shared_ptr<RenderEngine::Texture2D> getTexture(const std::string& textureName);

private:
    std::string getFileString(const std::string& relativeFilePath) const;

    typedef std::map<const std::string, std::shared_ptr<RenderEngine::ShaderProgram>> ShaderProgramsMap;
    ShaderProgramsMap m_shaderPrograms;

    typedef std::map<const std::string, std::shared_ptr<RenderEngine::Texture2D>> TexturesMap;
    TexturesMap m_textures;

    std::string m_path;
};