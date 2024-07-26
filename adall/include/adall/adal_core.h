#ifndef ADAL_CORE_H
#define ADAL_CORE_H

#include <utility>

#include "entt/entt.hpp"

#include "adal_pch.h"
#include "adal_view.h"

namespace adlCore {
	// ###################################################################
	//							  adlRegistry
	// ###################################################################

	/// @class adlRegistry
	/// @brief A wrapper class for the entt::registry to manage entities and contexts in an ECS architecture.
	class adlRegistry {
	private:
		std::unique_ptr<entt::registry> m_registry; ///< Pointer to the underlying entt::registry instance.

	public:
		/// @brief Constructs an adlRegistry instance.
		adlRegistry() {
			m_registry = std::make_unique<entt::registry>();
		};

		/// @brief @brief Default destructor.
		~adlRegistry() = default;

		/// @brief Gets a reference to the underlying entt::registry.
		/// @return A reference to the entt::registry.
		[[nodiscard]] inline entt::registry &getRegistry() const { return *m_registry; };

		/// @brief Creates a new entity in the registry.
    	/// @return The created entity.
		[[nodiscard]] inline entt::entity makeEntity() const { return m_registry->create(); };

		/// @brief Delete an entity in the registry.
    	/// @return The deleted entity.
		[[nodiscard]] inline std::uint32_t destroyEntity(const entt::entity &entity) const {
			return m_registry->destroy(entity);
		};

		/// @brief Adds a context to the registry.
    	/// @tparam TContext The type of the context.
    	/// @param context The context instance to add.
    	/// @return The added context instance.
		template<typename TContext>
		TContext adlAddContext(TContext context) {
			return m_registry->ctx().emplace<TContext>(context);
		}

		/// @brief Gets a reference to a context from the registry.
    	/// @tparam TContext The type of the context.
    	/// @return A reference to the context instance.
		template<typename TContext>
		TContext &adlGetContext() {
			return m_registry->ctx().get<TContext>();
		}
	};

	// ###################################################################
	//							  adlEntity
	// ###################################################################
	class adlEntityManager;

	class adlEntity {
		friend adlEntityManager;

	private:
		adlRegistry &m_registry;
		entt::entity m_entity;
		std::string  m_name, m_group;

	public:
		adlEntity(adlRegistry &registry, entt::entity entity, std::string name, const std::string &group);;

		inline entt::entity &getEntity() { return m_entity; };

		inline const std::string &name() { return m_name; };
		inline const std::string &group() { return m_group; };

		inline void setName(const std::string &name) { m_name = name; };
		inline void setGroup(const std::string &group) { m_group = group; };

		template<typename TComponent, typename... Args>
		TComponent &addComponent(Args &&... args) {
			return m_registry.getRegistry().emplace<TComponent>(m_entity, std::forward<Args>(args)...);
		}

		template<typename TComponent>
		[[nodiscard]] bool adlHasComponent() const {
			if (m_registry.getRegistry().all_of<TComponent>(m_entity)) {
				return true;
			}

			return false;
		}

		template<typename TComponent, typename... Args>
		TComponent &adlReplaceComponent(Args &&... args) {
			if (adlHasComponent<TComponent>()) {
				return m_registry.getRegistry().replace<TComponent>(std::forward<Args>(args)...);
			}
			return nullptr;
		}

		template<typename TComponent>
		TComponent &adlGetComponent() {
			if (adlHasComponent<TComponent>()) {
				return m_registry.getRegistry().get<TComponent>(m_entity);
			}
			return nullptr;
		}

		template<typename TComponent>
		void adlRemoveComponent(entt::entity &entity) const {
			if (adlHasComponent<TComponent>(entity)) {
				m_registry.getRegistry().remove<TComponent>(entity);
			}
		}
	};

	// ###################################################################
	//							  adlEntityManager
	// ###################################################################
	class adlEntityManager {
	private:
		adlRegistry &m_registry;

	public:
		explicit adlEntityManager(adlRegistry &registry)
			: m_registry(registry) {
		};

		~adlEntityManager() = default;

		[[nodiscard]] adlEntity makeEntity(const std::string &name = "", const std::string &group = "") const {
			return {m_registry, m_registry.makeEntity(), name, group};
		};

		std::uint32_t killEntity(adlEntity &entity);
	};


	// ###################################################################
	//							  adlAssetManager
	// ###################################################################
	typedef std::unordered_map<std::string, std::shared_ptr<adlTexture> > adlTextureMap;
	typedef std::unordered_map<std::string, std::shared_ptr<adlShader> >  adlShaderMap;

	class adlAssetManager {
	private:
		adlTextureMap m_textureMap;
		adlShaderMap  m_shaderMap;

	public:
		adlAssetManager() = default;

		~adlAssetManager() = default;

		bool makeTexture(const std::string &name, const std::string &texturePath, bool isPixelated = true);

		bool makeShader(const std::string &name
		              , const std::string &vertShaderPath
		              , const std::string &fragShaderPath);

		const adlTexture &getTexture(const std::string &name);

		adlShader &getShader(const std::string &name);
	};
}

#endif //ADAL_CORE_H
