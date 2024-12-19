//
// Created by Badi on 12/4/2024.
//

#ifndef PROJECT_ESPRIT_MODEL_C_CORRUPTED_H
#define PROJECT_ESPRIT_MODEL_C_CORRUPTED_H

#include "../Command.h"
#include "../../data_structures/YFastTrie.h"
#include <SFML/Graphics.hpp>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <string>

class TestYFastTrieCommand : public Command {
private:
    sf::RenderWindow trieWindow;
    sf::Font consoleFont;
    sf::Text logText;
    std::string inputBuffer;
    std::vector<std::string> logLines;
    YFastTrie<int, std::string> yFastTrie;

    void updateLogDisplay() {
        std::ostringstream logStream;
        for (const auto& line : logLines) {
            logStream << line << "\n";
        }
        logText.setString(logStream.str());
    }

    void renderTrie(sf::RenderWindow& window) {
        const int NODE_RADIUS = 20;
        const int HORIZONTAL_SPACING = 150;
        const int VERTICAL_SPACING = 100;

        int currentY = 50;

        // Loop through all clusters
        for (const auto& [key, cluster] : yFastTrie.getClusterMap()) {
            if (!cluster) continue;

            int currentX = 50;

            // Draw the cluster representative
            sf::CircleShape nodeShape(NODE_RADIUS);
            nodeShape.setFillColor(sf::Color::Blue);
            nodeShape.setPosition(currentX, currentY);

            sf::Text nodeLabel;
            nodeLabel.setFont(consoleFont);
            nodeLabel.setCharacterSize(14);
            nodeLabel.setFillColor(sf::Color::White);
            nodeLabel.setString(std::to_string(key));
            nodeLabel.setPosition(currentX + 10, currentY);

            window.draw(nodeShape);
            window.draw(nodeLabel);

            // Draw the AVL tree associated with this cluster
            cluster->visualizeAVL(window, currentX, currentY + VERTICAL_SPACING, consoleFont);

            currentX += HORIZONTAL_SPACING;
        }
    }

public:
    TestYFastTrieCommand()
            : Command("/testyfasttrie"),
              trieWindow(sf::VideoMode(800, 600), "Y-Fast Trie Visualization") {
        if (!consoleFont.loadFromFile("resources/Minecraft.ttf")) {
            throw std::runtime_error("Failed to load font");
        }

        logText.setFont(consoleFont);
        logText.setCharacterSize(14);
        logText.setFillColor(sf::Color::Yellow);
        logText.setPosition(10, 500);
    }

    void execute(std::vector<std::string>& consoleLines) override {
        logLines.emplace_back("Testing Y-Fast Trie Visualization...");
        yFastTrie.insert(10, "Ten");
        yFastTrie.insert(20, "Twenty");
        yFastTrie.insert(5, "Five");
        yFastTrie.insert(7, "Seven");
        logLines.emplace_back("Inserted nodes: 10, 20, 5, 7");
        updateLogDisplay();

        while (trieWindow.isOpen()) {
            sf::Event event{};
            while (trieWindow.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    trieWindow.close();
                }

                if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode == '\r') { // Enter key
                        logLines.emplace_back("> Command executed.");
                        if (!inputBuffer.empty()) {
                            std::istringstream ss(inputBuffer);
                            int key;
                            std::string value;
                            ss >> key >> value;
                            yFastTrie.insert(key, value);
                            logLines.emplace_back("Inserted node: " + std::to_string(key) + ", " + value);
                            inputBuffer.clear();
                        }
                        updateLogDisplay();
                        renderTrie(trieWindow);
                    } else if (event.text.unicode == '\b') { // Backspace
                        if (!inputBuffer.empty()) {
                            inputBuffer.pop_back();
                        }
                    } else if (event.text.unicode < 128) { // Normal characters
                        inputBuffer += static_cast<char>(event.text.unicode);
                    }
                }
            }

            trieWindow.clear();
            renderTrie(trieWindow);
            trieWindow.draw(logText);
            trieWindow.display();
        }
    }

    std::string getName() const override {
        return "test_y_fast_trie";
    }
};


#endif //PROJECT_ESPRIT_MODEL_C_CORRUPTED_H
