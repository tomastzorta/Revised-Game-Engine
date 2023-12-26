//
// Created by Tomas Tzorta on 25/12/2023.
//

#ifndef BUTTONWIDGET_H
#define BUTTONWIDGET_H

#include "UI/Widget.h"
#include "LabyrinthFramework/EventCallback.h"

namespace labyrinth_engine
{
    class ButtonWidget : public Widget
    {
    public:
        /* Constructors and Destructors */
        ButtonWidget(const std::string& a_buttonText = "Button", const std::string& a_buttonTextureFilename = "PNG/UI/buttonBlue.png");
        /* End of Constructors and Destructors */

        /* Class Functions */

        // Void Functions

        // Boolean Functions

        // Virtual Functions
        sf::FloatRect GetWidgetBounds() const override {return m_buttonSprite.getGlobalBounds();}

        /* End of Class Functions */

        /* Override Functions */
        /* End of Override Functions */

        /* Setters and Getters */

        // Setters

        // Getters

        /* End of Setters and getters */

    protected:

    private:
        void DrawWidget(sf::RenderWindow& a_window) override;
        void UpdateWidgetLocation(const sf::Vector2f& a_position) override;
        void UpdateWidgetRotation(float& a_rotation) override;
        Shared<sf::Texture> m_buttonTexture;
        sf::Sprite m_buttonSprite;

        Shared<sf::Font> m_buttonFont;
        sf::Text m_buttonText;

        sf::Color m_ButtonIdleColour;
        sf::Color m_ButtonPressedColour;
        sf::Color m_ButtonHoverColour;

        bool m_isButtonPressed;
    };
}

#endif //BUTTONWIDGET_H
