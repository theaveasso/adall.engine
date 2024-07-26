#ifndef ADALGL_VIEW_H
#define ADALGL_VIEW_H

#include "adal_pch.h"

// ###################################################################
//                          adlType
// ###################################################################
typedef std::unordered_map<std::string, GLint> adlUniformLocationMap;

// ###################################################################
//                          adlColor
// ###################################################################
struct adlColor {
    GLubyte r, g, b, a;
};

// ###################################################################
//                          adlVertex
// ###################################################################
struct adlVertex {
    glm::vec2 position{0.f}, uvs{0.f};
    adlColor  color{.r = 255, .g = 255, .b = 255, .a = 255};

    /// Sets the vertex color using individual RGBA color components.
    ///
    /// @param r Red component (0-255).
    /// @param g Green component (0-255).
    /// @param b Blue component (0-255).
    /// @param a Alpha component (0-255).
    void setColor(const GLubyte r, const GLubyte g, const GLubyte b, const GLubyte a) {
        color.r = r;
        color.g = g;
        color.b = b;
        color.a = a;
    }

    /// Sets the vertex color using a packed 32-bit integer color value.
    ///
    /// @param iColor The packed color value (ARGB format).
    void setColor(const GLuint iColor) {
        color.r = (iColor >> 24) & 0xFF;
        color.g = (iColor >> 16) & 0xFF;
        color.b = (iColor >> 8) & 0xFF;
        color.a = (iColor >> 0) & 0xFF;
    }
};

// ###################################################################
//                          adlTextureType
// ###################################################################
enum struct adlTextureType {
    PIXEL = 0, SMOOTH, NONE, FRAME_BUFFER
};

// ###################################################################
//                          adlTexture
// ###################################################################
struct adlTexture {
    int    width, height;
    GLuint textureID;

    /// Binds the texture to the active texture unit.
    inline void bind() const {
        glBindTexture(GL_TEXTURE_2D, textureID);
    };

    /// Unbinds the currently bound texture.
    static inline void unbind() {
        glBindTexture(GL_TEXTURE_2D, 0);
    };
};

// ###################################################################
//                          adlShader
// ###################################################################
struct adlShader {
    GLuint                shaderProgramID;
    adlUniformLocationMap uniformLocationMap;
};

// ###################################################################
//                          adlFrameBuffer
// ###################################################################
struct adlFrameBuffer {
    int                         m_width, m_height;
    GLuint                      m_fboID, m_rboID;
    std::shared_ptr<adlTexture> m_texture;
    bool                        m_shouldResize, m_isUseRBO;
};

// ###################################################################
//                          adlTextureLoader
// ###################################################################
struct adlTextureLoader {
    /// Loads a texture from the specified file path.
    ///
    /// @param texturePath The path to the texture image file.
    /// @param width The width of the loaded texture will be stored here.
    /// @param height The height of the loaded texture will be stored here.
    /// @param isPixelated Whether to apply pixelation effects to the texture.
    /// @return True if the texture is loaded successfully, false otherwise.
    static bool adlLoadTexture(const std::string& texturePath, int &width, int &height, bool isPixelated);

    /// Creates a shared pointer to an adlTexture object.
    ///
    /// @param texturePath The path to the texture image file.
    /// @param textureType The type of the texture (2D, cubemap, etc.).
    /// @return A shared pointer to the created adlTexture object, or nullptr on failure.
    static std::shared_ptr<adlTexture> makeADLTexture(const std::string &texturePath, adlTextureType textureType);
};

// ###################################################################
//                          adlShaderLoader
// -------------------------------------------------------------------
struct adlShaderLoader {
private:
    ///  Compiles a GL shader of the specified type from the given shader path.
    ///
    ///  @param shaderType The type of shader (GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, etc.).
    ///  @param shaderPath The path to the shader source file.
    ///  @return The ID of the compiled shader, or 0 on failure.
    static GLuint compileGLShader(GLuint shaderType, const std::string &shaderPath);

    /// Checks if the compilation of the shader was successful.
    ///
    /// @param shaderID The ID of the shader to check.
    /// @return True if compilation was successful, false otherwise.
    static bool isCompileSuccess(GLuint shaderID);

    /// Checks if the GL program is valid.
    ///
    /// @param programID The ID of the program to check.
    /// @return True if the program is valid, false otherwise.
    static bool isValidGLProgram(GLuint programID);

public:
    /// Creates a shared pointer to an adlShader object, compiling and linking the given shaders.
    ///
    /// @param vertShaderPath The path to the vertex shader source file.
    /// @param fragShaderPath The path to the fragment shader source file.
    /// @return A shared pointer to the created adlShader object, or nullptr on failure.
    static std::shared_ptr<adlShader> makeADLShader(const std::string &vertShaderPath
                                                  , const std::string &fragShaderPath);
};

#endif //ADALGL_VIEW_H
