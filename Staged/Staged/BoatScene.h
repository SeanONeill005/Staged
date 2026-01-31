#pragma once

#include "SceneManager.h"
#include "BaseScene.h"

class BoatScene :
	public BaseScene
{
public:
	BoatScene();
	~BoatScene();

	virtual void processEvents() override;

	virtual void update(sf::Time t_dT) override;

	virtual void render() override;
private:

	void processKeys(const std::optional<sf::Event> t_event);
	void processClick(const std::optional<sf::Event> t_event);
};