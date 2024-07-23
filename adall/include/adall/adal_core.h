#ifndef ADAL_CORE_H
#define ADAL_CORE_H

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
		adlRegistry();

		/// @brief @brief Default destructor.
		~adlRegistry() = default;

		/// @brief Gets a reference to the underlying entt::registry.
		/// @return A reference to the entt::registry.
		[[nodiscard]] inline entt::registry &getRegistry() const { return *m_registry; };

		/// @brief Creates a new entity in the registry.
    	/// @return The created entity.
		[[nodiscard]] inline entt::entity makeEntity() const { return m_registry->create(); };

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
	//							  adlEntityManager
	// ###################################################################
	class adlEntity;

	class adlEntityManager {
	private:
		adlRegistry &m_registry;

	public:
		explicit adlEntityManager(adlRegistry &registry)
			: m_registry(registry) {
		};

		~adlEntityManager() = default;

		adlEntity makeEntity(const std::string &name = "", const std::string &group = "");

		std::uint32_t killEntity(adlEntity &entity);
	};

	// ###################################################################
	//							  adlEntityManager
	// ###################################################################

	class adlEntity {
		friend adlEntityManager;

	private:
		adlRegistry &m_registry;
		entt::entity m_entity;
		std::string  m_name, m_group;

	public:
		adlEntity(adlRegistry& registry, entt::entity entity, const std::string &name, const std::string &group);

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
				return m_registry.getRegistry().replace<TComponent>(m_entity, std::forward<Args>(args)...);
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
		void adlRemoveComponent() const {
			if (adlHasComponent<TComponent>()) {
				m_registry.getRegistry().remove<TComponent>(m_entity);
			}
		}
	};

	// ###################################################################
	//							  adlAssetManager
	// ###################################################################
	typedef std::unordered_map<std::string, std::shared_ptr<adlTexture> > adlTextureMap;
	typedef std::unordered_map<std::string, std::shared_ptr<adlShader> >  adlShaderMap;

	class adlAssetManager {
	public:
		adlAssetManager() = default;

		~adlAssetManager() = default;

		bool addTexture(const std::string &name, const std::string &texturePath, bool isPixelated = true);

		bool addShader(const std::string &name
		             , const std::string &vertexShaderSourcePath
		             , const std::string &fragmentShaderSourcePath);

		const adlTexture &getTexture(const std::string &name);

		adlShader &getShader(const std::string &name);
	};
}

#endif //ADAL_CORE_H
