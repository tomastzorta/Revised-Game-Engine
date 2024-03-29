//
// Created by Tomas Tzorta on 25/12/2023.
//

#include "UI/ButtonWidget.h"

#include "LabyrinthFramework/AssetManager.h"

namespace labyrinth_engine
{
    ButtonWidget::ButtonWidget(const std::string& a_buttonText, const std::string& a_buttonTextureFilename)
        : m_buttonTexture{AssetManager::GetInstance().LoadTexture(a_buttonTextureFilename)}
        , m_buttonSprite{*m_buttonTexture.get()}
        , m_buttonFont{AssetManager::GetInstance().LoadFont("Bonus/kenvector_future.ttf")}
        , m_buttonText{a_buttonText, *m_buttonFont.get(), }
        , m_ButtonIdleColour{128, 128, 128, 255}
        , m_ButtonPressedColour{64, 64, 64, 255}
        , m_ButtonHoverColour{192, 192, 192, 255}
        , m_bIsButtonPressed{false}
    {
        m_buttonSprite.setColor(m_ButtonIdleColour);
        CenterWidgetText();
    }

    void ButtonWidget::ButtonReleased()
    {
        m_bIsButtonPressed = false;
        m_buttonSprite.setColor(m_ButtonIdleColour);
    }

    void ButtonWidget::ButtonPressed()
    {
        m_bIsButtonPressed = true;
        m_buttonSprite.setColor(m_ButtonPressedColour);
    }

    void ButtonWidget::ButtonHovered()
    {
        m_buttonSprite.setColor(m_ButtonHoverColour);
    }

    bool ButtonWidget::IsMouseOver(const sf::Event& a_event)
    {
        if (!IsWidgetVisible()) return false; // if the widget is not visible, return false

        bool isMouseOver = false;
        if (a_event.type == sf::Event::MouseButtonReleased)
        {
            if (a_event.mouseButton.button == sf::Mouse::Left)
            {
                if(m_buttonSprite.getGlobalBounds().contains(a_event.mouseButton.x, a_event.mouseButton.y) && m_bIsButtonPressed)
                {
                    OnButtonPressed.Broadcast();
                    isMouseOver = true;
                }
            }
            ButtonReleased();
        }
        else if (a_event.type == sf::Event::MouseButtonPressed)
        {
            if (a_event.mouseButton.button == sf::Mouse::Left)
            {
                if(m_buttonSprite.getGlobalBounds().contains(a_event.mouseButton.x, a_event.mouseButton.y))
                {
                    ButtonPressed();
                    isMouseOver = true;
                }
            }
        }
        else if (a_event.type == sf::Event::MouseMoved)
        {
            if(!sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if(m_buttonSprite.getGlobalBounds().contains(a_event.mouseMove.x, a_event.mouseMove.y))
                {
                    ButtonHovered();
                }
                else
                {
                    ButtonReleased();
                }
            }
        }
        return isMouseOver || Widget::IsMouseOver(a_event);
    }

    void ButtonWidget::SetButtonText(const std::string& a_buttonText)
    {
        m_buttonText.setString(a_buttonText);
        CenterWidgetText();
    }

    void ButtonWidget::SetButtonTextSize(unsigned a_fontSize)
    {
        m_buttonText.setCharacterSize(a_fontSize);
        CenterWidgetText();
    }

    void ButtonWidget::CenterWidgetText()
    {
        sf::Vector2f widgetCenter = GetWidgetCenterPosition();
        sf::FloatRect textBounds = m_buttonText.getGlobalBounds();
        m_buttonText.setPosition(widgetCenter - sf::Vector2f{textBounds.width/2.0f, textBounds.height});
    }

    void ButtonWidget::DrawWidget(sf::RenderWindow& a_window)
    {
        a_window.draw(m_buttonSprite);
        a_window.draw(m_buttonText);
    }

    void ButtonWidget::UpdateWidgetLocation(const sf::Vector2f& a_position)
    {
        m_buttonSprite.setPosition(a_position);
        CenterWidgetText();
    }

    void ButtonWidget::UpdateWidgetRotation(float& a_rotation)
    {
        m_buttonSprite.setRotation(a_rotation);
        m_buttonText.setRotation(a_rotation);
    }
}
