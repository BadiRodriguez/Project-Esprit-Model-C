//
// Created by Badi on 12/19/2024.
//

#ifndef PROJECT_ESPRIT_MODEL_C_TYPINGTEXT_H
#define PROJECT_ESPRIT_MODEL_C_TYPINGTEXT_H

#include <iostream>
#include <valarray>
#include "SFML/Graphics.hpp"

class TypingText {
private:
    std::string fullText;
    std::string currentText;
    sf::Clock clock;
    float typingSpeed; // Characters per second

public:
    TypingText(const std::string& text, float speed = 30.0f)
            : fullText(text), typingSpeed(speed) {}

    bool update() {
        if (clock.getElapsedTime().asSeconds() >= (1.0f / typingSpeed)) {
            if (currentText.size() < fullText.size()) {
                currentText += fullText[currentText.size()];
                clock.restart();
                return true; // Indicates text is still animating
            }
        }
        return false; // Typing animation complete
    }

    const std::string& getText() const {
        return currentText;
    }

    sf::Color getPulsatingColor(float speed = 2.0f) {
        float intensity = 128 + 127 * std::sin(speed * clock.getElapsedTime().asSeconds());
        return sf::Color(0, 255, 0, static_cast<sf::Uint8>(intensity)); // Green glow
    }

};

#endif //PROJECT_ESPRIT_MODEL_C_TYPINGTEXT_H
