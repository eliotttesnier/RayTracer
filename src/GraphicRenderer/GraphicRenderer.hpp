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
#include <mutex>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "../Graphic/Color.hpp"

enum runResult_e {
    FINISHED,
    RELOAD_CONFIG
};

class GraphicRenderer {
    public:
        GraphicRenderer(
            std::string const &configFilename,
            std::string const &previewFilename,
            std::string const &finalFilename = "",
            bool isPreviewMode = true,
            bool isProgressiveMode = false
        );
        ~GraphicRenderer() = default;

        runResult_e run(std::atomic<bool>& renderingComplete);
        bool loadFromFile(const std::string& filename);
        void exportToPNG(const std::string& outputFilename) const;
        void switchToFinalImage();
        void displayLoadingMessage(const std::string& message);
        void updateProgressiveRendering(const std::vector<std::vector<Graphic::color_t>>& pixelBuffer);
        void setProgressiveMode(bool isProgressiveMode);

    private:
        void updatePixelsFromBuffer(const std::vector<std::vector<Graphic::color_t>>& pixelBuffer);
        void updateTexture();

        int _width, _height;
        std::vector<sf::Uint8> _pixels;
        sf::RenderWindow _window;
        sf::Texture _texture;
        sf::Sprite _sprite;
        std::string _inputFilename;
        std::string _finalFilename;
        bool _isPreviewMode;
        bool _isProgressiveMode;
        sf::Font _font;
        sf::Text _loadingText;
        std::mutex _pixelMutex;
        std::string _configFilename;
        int _inotifyId;
};

#endif /* !GRAPHICRENDERER_HPP_ */
