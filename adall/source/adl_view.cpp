#include <stb/stb_image.h>
#include "adall/adal_view.h"

/* -------------------------------------------------------------------------
	adlTextureLoader
--------------------------------------------------------------------------*/
bool adlTextureLoader::adlLoadTexture(const std::string &texturePath, int &width, int &height, bool isPixelated) {
	int channels = 0;

	unsigned char *data = stbi_load(texturePath.c_str(), &width, &height, &channels, 4);
	if (!data) {
		return false;
	}

	if (isPixelated) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	GLint format;
	if (channels == 3) format = GL_RGB;
	else format = GL_RGBA;

	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

	stbi_image_free(data);
	return true;
}

std::shared_ptr<adlTexture>
	adlTextureLoader::makeADLTexture(const std::string &texturePath, adlTextureType textureType) {
	return nullptr;
}

/* -------------------------------------------------------------------------
	adlShaderLoader
--------------------------------------------------------------------------*/
GLuint adlShaderLoader::compileGLShader(const GLuint shaderType, const std::string &shaderPath) {
	const auto shaderID = glCreateShader(shaderType);

	std::ifstream ifs(shaderPath);
	if (ifs.fail()) {
		return 0;
	}
	std::string contents, line;
	while (std::getline(ifs, line)) {
		contents += line + "\n";
	}
	ifs.close();

	const char *contentsPtr = contents.data();
	glShaderSource(shaderID, 1, &contentsPtr, nullptr);
	glCompileShader(shaderID);

	if (!isCompileSuccess(shaderID)) {
		return 0;
	}

	return shaderID;
}

bool adlShaderLoader::isCompileSuccess(const GLuint shaderID) {
	GLint status;

	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE) {
		GLint maxLength;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

		std::string error(maxLength, ' ');
		glGetShaderInfoLog(shaderID, maxLength, &maxLength, error.data());
		glDeleteShader(shaderID);

		return false;
	}

	return true;
}

bool adlShaderLoader::isValidGLProgram(const GLuint programID) {
	GLint status;

	glGetProgramiv(programID, GL_LINK_STATUS, &status);
	if (status != GL_TRUE) {
		GLint maxLength;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);

		std::string error(maxLength, ' ');
		glGetProgramInfoLog(programID, maxLength, &maxLength, error.data());

		return false;
	}

	return true;
}

std::shared_ptr<adlShader> adlShaderLoader::makeADLShader(const std::string &vertShaderPath
                                                        , const std::string &fragShaderPath) {
	const GLuint programID = glCreateProgram();
	const GLuint vShaderID = compileGLShader(GL_VERTEX_SHADER, vertShaderPath);
	const GLuint fShaderID = compileGLShader(GL_FRAGMENT_SHADER, fragShaderPath);

	if (vShaderID == 0 || fShaderID == 0) {
		return nullptr;
	}

	glAttachShader(programID, vShaderID);
	glAttachShader(programID, fShaderID);

	glLinkProgram(programID);
	if (!isValidGLProgram(programID)) {
		glDeleteProgram(programID);
		glDeleteShader(vShaderID);
		glDeleteShader(fShaderID);
		return nullptr;
	}

	glDetachShader(programID, vShaderID);
	glDetachShader(programID, fShaderID);

	glDeleteShader(vShaderID);
	glDeleteShader(fShaderID);

	return std::make_shared<adlShader>(adlShader({.shaderProgramID = programID, .uniformLocationMap = {}}));
}


