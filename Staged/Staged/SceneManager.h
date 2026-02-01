#pragma once

#include <functional>
#include <memory>
#include <unordered_map>

#include "Globals.h"
#include "BaseScene.h"

enum class SceneType { MAIN_MENU, WESTERN, CIRCUS, BOAT, CHEST, GAME_OVER };
using Scene = std::unique_ptr<BaseScene>;

class SceneManager
{
public:
	static SceneManager* getInstance() {
		static SceneManager instance;
		return &instance;
	}

	SceneManager(SceneManager const&) = delete;
	void operator=(SceneManager const&) = delete;

	void setRenderWindow(std::shared_ptr<sf::RenderWindow> t_window) { m_window = t_window; }

	template<typename T, typename... Args>
	void registerScene(SceneType t_sceneType, const Args& ...t_args) {
		m_sceneCache.emplace(t_sceneType, [t_args...]() {
			return std::make_unique<T>(t_args...);
			});
	}

	void setScene(SceneType t_sceneType) {
		if (m_currentScene) {
			// Start closing transition on current scene
			m_nextSceneType = t_sceneType;
			m_currentScene->startClosingTransition();
			m_transitioning = true;
		}
		else {
			// No current scene, just switch directly
			switchToScene(t_sceneType);
		}
	}

	void processEvents() {
		if (m_currentScene && !m_transitioning) {
			m_currentScene->processEvents();
		}
	}

	void update(sf::Time t_dT) {
		if (m_currentScene) {
			m_currentScene->updateTransition(t_dT);

			if (m_transitioning && m_currentScene->isClosingComplete()) {
				switchToScene(m_nextSceneType);
				m_transitioning = false;
			}

			// Only update scene logic when not transitioning
			if (!m_transitioning) {
				m_currentScene->update(t_dT);
			}
		}
	}

	void render() {
		if (m_currentScene) {
			m_currentScene->render();
			m_currentScene->renderTransition();
			m_window->display();
		}
	}

private:
	using SceneCache = std::unordered_map<SceneType, std::function<Scene()>>;

	SceneManager() {}

	void switchToScene(SceneType t_sceneType) {
		if (const auto it = m_sceneCache.find(t_sceneType); it != m_sceneCache.end()) {
			m_currentScene = it->second();
			m_currentScene->setRenderWindow(m_window);
		}
		else {
			std::cerr << "Trying to create scene which hasn't been registered with SceneManager!" << std::endl;
		}
	}

	SceneCache m_sceneCache;
	Scene m_currentScene;
	std::shared_ptr<sf::RenderWindow> m_window;

	bool m_transitioning = false;
	SceneType m_nextSceneType;
};

