#include "Shader.h"

Shader::Shader(const std::string& filepath) : myFilepath(filepath), myRendererId(0)
{
    ShaderSource ss = ParseShader();
    myRendererId = CreateShader(ss.vertexSrc, ss.fragmentSrc);

    DeviceMemoryManager::GetInstance().AddShaderRef(myRendererId);
}
Shader::Shader(Shader& sh)
{
    DeviceMemoryManager::GetInstance().RemoveShaderRef(myRendererId);

    myRendererId = sh.myRendererId;
    myFilepath = sh.myFilepath;
    myUniformLocCache = sh.myUniformLocCache;

    DeviceMemoryManager::GetInstance().AddShaderRef(myRendererId);
}
Shader& Shader::operator=(const Shader& sh)
{
    DeviceMemoryManager::GetInstance().RemoveShaderRef(myRendererId);

    myRendererId = sh.myRendererId;
    myFilepath = sh.myFilepath;
    myUniformLocCache = sh.myUniformLocCache;

    DeviceMemoryManager::GetInstance().AddShaderRef(myRendererId);

    return *this;
}
Shader::~Shader()
{
    DeviceMemoryManager::GetInstance().RemoveShaderRef(myRendererId);
}

ShaderSource Shader::ParseShader()
{
    std::ifstream stream(myFilepath);

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    }

    return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(vertexShader, GL_VERTEX_SHADER);
    unsigned int fs = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);

    GlCall(glAttachShader(program, vs));
    GlCall(glAttachShader(program, fs));
    GlCall(glLinkProgram(program));
    GlCall(glValidateProgram(program));

    GlCall(glDeleteShader(vs));
    GlCall(glDeleteShader(fs));

    return program;
}

unsigned int Shader::CompileShader(const std::string& source, unsigned int type)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    GlCall(glShaderSource(id, 1, &src, nullptr));
    GlCall(glCompileShader(id));

    int result;
    GlCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE)
    {
        int length;
        GlCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = new char[length];
        GlCall(glGetShaderInfoLog(id, length, &length, message));
        std::cout << "Failed to compile: " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
        std::cout << message << std::endl;
        delete[] message;
    }

    return id;
}

void Shader::Bind() const
{
    GlCall(glUseProgram(myRendererId));
}
void Shader::Unbind() const
{
    GlCall(glUseProgram(0));
}

void Shader::SetUniform1i(const std::string& name, const int value)
{
    Bind();
    int valueId = GetUniformLocation(name);
    GlCall(glUniform1i(valueId, value));
}
void Shader::SetUniform4f(const std::string& name, const glm::mat4& matrix)
{
    Bind();
    int matrixId = GetUniformLocation(name);
    GlCall(glUniformMatrix4fv(matrixId, 1, GL_FALSE, &matrix[0][0]));
}

int Shader::GetUniformLocation(const std::string& name)
{
    if (myUniformLocCache.find(name) != myUniformLocCache.end())
        return myUniformLocCache[name];

    GlCall(int location = glGetUniformLocation(myRendererId, name.c_str()));
    if (location == -1)
        std::cout << "Error" << std::endl;

    myUniformLocCache[name] = location;
    return location;
}