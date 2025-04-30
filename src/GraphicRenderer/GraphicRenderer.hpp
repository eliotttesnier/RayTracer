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
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class GraphicRenderer {
    public:
        GraphicRenderer(std::string const &filename);
        ~GraphicRenderer() = default;

        void run();
        bool loadFromFile(const std::string& filename);
        void exportToPNG() const;

    private:
        int _width, _height;
        std::vector<sf::Uint8> _pixels;
        sf::RenderWindow _window;
        sf::Texture _texture;
        sf::Sprite _sprite;
        std::string _inputFilename;
};

#endif /* !GRAPHICRENDERER_HPP_ */
