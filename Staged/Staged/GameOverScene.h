#pragma once

#include "SceneManager.h"
#include "BaseScene.h"

class GameOverScene :
	public BaseScene
{
public:
	GameOverScene();
	~GameOverScene();

	virtual void processEvents() override;

	virtual void update(sf::Time t_dT) override;

	virtual void render() override;
private:

	void processKeys(const std::optional<sf::Event> t_event);
	void processClick(const std::optional<sf::Event> t_event);
};