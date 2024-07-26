#include "adall/adal_core.h"

namespace adlCore {
	adlEntity::adlEntity(adlRegistry &registry, const entt::entity entity, std::string name, const std::string &group): m_registry(registry),
		m_entity(entity),
		m_name(std::move(name)),
		m_group(group) {
	}


	/* -------------------------------------------------------------------------
		adlAssetManager
	--------------------------------------------------------------------------*/
	bool adlAssetManager::makeTexture(const std::string &name, const std::string &texturePath, const bool isPixelated) {
		if (!m_textureMap.contains(name)) {
			return false;
		}

		const auto textureType = isPixelated ? adlTextureType::PIXEL : adlTextureType::SMOOTH;
		auto texture = std::move(adlTextureLoader::makeADLTexture(texturePath, textureType));
		m_textureMap.insert(std::make_pair(name, std::move(texture)));

		return true;
	}

	bool adlAssetManager::makeShader(const std::string &name, const std::string &vertexShaderSourcePath, const std::string &fragmentShaderSourcePath) {
		if (m_shaderMap.contains(name)) {
			return false;
		}

		auto shader = std::move(adlShaderLoader::makeADLShader(vertexShaderSourcePath, fragmentShaderSourcePath));
		m_shaderMap.insert(std::make_pair(name, std::move(shader)));

		return true;
	}

	const adlTexture & adlAssetManager::getTexture(const std::string &name) {
		const auto itr = m_textureMap.find(name);
		if (itr != m_textureMap.end()) {
			static auto defaultTexture = adlTexture{.width= 0, .height= {}, .textureID = 0};
			return defaultTexture;
		}

		return *(itr->second);
	}

	adlShader &adlAssetManager::getShader(const std::string &name) {
		const auto itr = m_shaderMap.find(name);
		if (itr != m_shaderMap.end()) {
			static auto defaultShader = adlShader{.shaderProgramID =  0, .uniformLocationMap = {}};
			return defaultShader;
		}

		return *(itr->second);
	}

}
