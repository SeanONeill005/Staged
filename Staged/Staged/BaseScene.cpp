#include "BaseScene.h"
#include "Globals.h"
#include <cmath>

BaseScene::BaseScene()
    : m_leftCurtain(TextureManager::getInstance().get(Textures::Stage::LeftCurtain))
    , m_rightCurtain(TextureManager::getInstance().get(Textures::Stage::RightCurtain))
    , m_leftLight(TextureManager::getInstance().get(Textures::Stage::LeftLight))
    , m_rightLight(TextureManager::getInstance().get(Textures::Stage::RightLight))
{
    setupTransitionSprites();
    startOpeningTransition();
}

float BaseScene::easeOutCubic(float t)
{
    // Ease out cubic: fast start, slow end
    return 1.f - std::pow(1.f - t, 2.f);
}

void BaseScene::setupTransitionSprites()
{
    // Set up left curtain
    sf::FloatRect leftCurtainBounds = m_leftCurtain.getLocalBounds();
    m_leftCurtain.setOrigin({ leftCurtainBounds.size.x, 0.f });
    m_leftCurtain.setPosition({ WINDOW_WIDTH / 2.f, 0.f });
    float scaleY = WINDOW_HEIGHT / leftCurtainBounds.size.y;
    m_leftCurtain.setScale({ 1.f, scaleY });

    // Set up right curtain
    sf::FloatRect rightCurtainBounds = m_rightCurtain.getLocalBounds();
    m_rightCurtain.setPosition({ WINDOW_WIDTH / 2.f, 0.f });
    scaleY = WINDOW_HEIGHT / rightCurtainBounds.size.y;
    m_rightCurtain.setScale({ 1.f, scaleY });

    // Set up left light
    sf::FloatRect leftLightBounds = m_leftLight.getLocalBounds();
    m_leftLight.setOrigin({ leftLightBounds.size.x / 2.f, 0.f });
    m_leftLight.setPosition({ WINDOW_WIDTH * 0.3f, LIGHT_START_OFFSET });

    // Set up right light
    sf::FloatRect rightLightBounds = m_rightLight.getLocalBounds();
    m_rightLight.setOrigin({ rightLightBounds.size.x / 2.f, 0.f });
    m_rightLight.setPosition({ WINDOW_WIDTH * 0.7f, LIGHT_START_OFFSET });
}

void BaseScene::startOpeningTransition()
{
    m_transitionState = TransitionState::Opening;
    m_curtainProgress = 0.f;
    m_lightProgress = 0.f;
    m_delayTimer = 0.f;
    m_closingComplete = false;
}

void BaseScene::startClosingTransition()
{
    m_transitionState = TransitionState::Closing;
    m_curtainProgress = 1.f;
    m_lightProgress = 1.f;
}

void BaseScene::updateTransition(sf::Time t_dT)
{
    if (m_transitionState == TransitionState::Idle) {
        return;
    }

    if (m_transitionState == TransitionState::Opening) {
        // Phase 1: Open curtains
        if (m_curtainProgress < 1.f) {
            m_curtainProgress += (1.f / CURTAIN_DURATION) * t_dT.asSeconds();
            if (m_curtainProgress >= 1.f) {
                m_curtainProgress = 1.f;
                m_transitionState = TransitionState::WaitingForLights;
                m_delayTimer = 0.f;
            }
        }
    }
    else if (m_transitionState == TransitionState::WaitingForLights) {
        // Wait before lowering lights
        m_delayTimer += t_dT.asSeconds();
        if (m_delayTimer >= TRANSITION_DELAY) {
            m_transitionState = TransitionState::Opening;
            m_delayTimer = 0.f;
        }
    }

    // Continue opening after delay, lower lights
    if (m_transitionState == TransitionState::Opening && m_curtainProgress >= 1.f && m_delayTimer == 0.f) {
        if (m_lightProgress < 1.f) {
            m_lightProgress += (1.f / LIGHT_DURATION) * t_dT.asSeconds();
            if (m_lightProgress >= 1.f) {
                m_lightProgress = 1.f;
                m_transitionState = TransitionState::Idle;
            }
        }
    }
    else if (m_transitionState == TransitionState::Closing) {
        // Phase 1: Raise lights
        if (m_lightProgress > 0.f) {
            m_lightProgress -= (1.f / LIGHT_DURATION) * t_dT.asSeconds();
            if (m_lightProgress <= 0.f) {
                m_lightProgress = 0.f;
            }
        }
        // Phase 2: Close curtains (after lights are up)
        else if (m_curtainProgress > 0.f) {
            m_curtainProgress -= (1.f / CURTAIN_DURATION) * t_dT.asSeconds();
            if (m_curtainProgress <= 0.f) {
                m_curtainProgress = 0.f;
                m_transitionState = TransitionState::Idle;
                m_closingComplete = true;
            }
        }
    }

    // Apply easing to progress values
    float easedCurtainProgress = easeOutCubic(m_curtainProgress);
    float easedLightProgress = easeOutCubic(m_lightProgress);

    // Update sprite positions based on eased progress
    float curtainOffset = easedCurtainProgress * CURTAIN_MAX_OFFSET;
    float lightOffset = LIGHT_START_OFFSET + (easedLightProgress * (LIGHT_END_OFFSET - LIGHT_START_OFFSET));

    m_leftCurtain.setPosition({ WINDOW_WIDTH / 2.f - curtainOffset, 0.f });
    m_rightCurtain.setPosition({ WINDOW_WIDTH / 2.f + curtainOffset, 0.f });
    m_leftLight.setPosition({ WINDOW_WIDTH * 0.3f, lightOffset });
    m_rightLight.setPosition({ WINDOW_WIDTH * 0.7f, lightOffset });
}

void BaseScene::renderTransition()
{
    if (m_window) {
        m_window->draw(m_leftLight);
        m_window->draw(m_rightLight);
        m_window->draw(m_leftCurtain);
        m_window->draw(m_rightCurtain);
    }
}

sf::Vector2f BaseScene::getMousePosition() const
{
    sf::Vector2i pixelPos = sf::Mouse::getPosition(*m_window);
    return m_window->mapPixelToCoords(pixelPos);
}
