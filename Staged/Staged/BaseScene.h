#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "TextureManager.h"

enum class TransitionState {
    Idle,
    Opening,
    Closing,
    WaitingForLights
};

class BaseScene {
public:
    BaseScene();
    virtual ~BaseScene() = default;

    void setRenderWindow(std::shared_ptr<sf::RenderWindow> t_window) { m_window = t_window; }

    virtual void processEvents() = 0;
    virtual void update(sf::Time t_dT) = 0;
    virtual void render() = 0;

    // Transition methods
    void startOpeningTransition();
    void startClosingTransition();
    bool isTransitionComplete() const { return m_transitionState == TransitionState::Idle; }
    bool isClosingComplete() const { return m_closingComplete; }

    void updateTransition(sf::Time t_dT);
    void renderTransition();

protected:
    std::shared_ptr<sf::RenderWindow> m_window;

private:
    // Transition sprites
    sf::Sprite m_leftCurtain;
    sf::Sprite m_rightCurtain;
    sf::Sprite m_leftLight;
    sf::Sprite m_rightLight;

    // Transition state
    TransitionState m_transitionState = TransitionState::Opening;
    float m_curtainProgress = 0.f;  // 0.0 to 1.0
    float m_lightProgress = 0.f;    // 0.0 to 1.0
    float m_delayTimer = 0.f;
    bool m_closingComplete = false;

    // Animation constants
    static constexpr float CURTAIN_DURATION = 1.5f;
    static constexpr float LIGHT_DURATION = 0.5f;
    static constexpr float CURTAIN_MAX_OFFSET = 960.f;
    static constexpr float LIGHT_START_OFFSET = -500.f;
    static constexpr float LIGHT_END_OFFSET = -200.f;
    static constexpr float TRANSITION_DELAY = 0.3f;

    void setupTransitionSprites();
    float easeOutCubic(float t); // Smooth stop easing function
};