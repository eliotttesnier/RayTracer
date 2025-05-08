/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** GraphicRenderer
*/

#ifndef GRAPHICRENDERER_HPP_
#define GRAPHICRENDERER_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <atomic>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class GraphicRenderer {
    public:
        GraphicRenderer(std::string const &previewFilename, std::string const &finalFilename = "");
        ~GraphicRenderer() = default;

        void run(std::atomic<bool>& renderingComplete);
        bool loadFromFile(const std::string& filename);
        void exportToPNG() const;
        void switchToFinalImage();
        void displayLoadingMessage(const std::string& message);

    private:
        int _width, _height;
        std::vector<sf::Uint8> _pixels;
        sf::RenderWindow _window;
        sf::Texture _texture;
        sf::Sprite _sprite;
        std::string _inputFilename;
        std::string _finalFilename;
        bool _isPreviewMode;
        sf::Font _font;
        sf::Text _loadingText;
};

#endif /* !GRAPHICRENDERER_HPP_ */
