/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** GraphicRenderer implementation
*/

#include <iostream>
#include <string>
#include <algorithm>

#include "GraphicRenderer.hpp"

GraphicRenderer::GraphicRenderer(std::string const &filename) : _inputFilename(filename)
{
    if (!loadFromFile(filename)) {
        std::cerr << "Failed to load PPM file: " << filename << std::endl;
        throw std::runtime_error("Failed to load PPM file");
    }

    _window.create(sf::VideoMode(1920, 1080), "Ray Tracer Visualizer");

    if (!_texture.create(_width, _height)) {
        std::cerr << "Failed to create texture." << std::endl;
        throw std::runtime_error("Failed to create texture");
    }

    _texture.update(_pixels.data());
    _sprite.setTexture(_texture);

    float scaleX = 1920.0f / _width;
    float scaleY = 1080.0f / _height;
    float scale = std::min(scaleX, scaleY);

    _sprite.setScale(scale, scale);

    float scaledWidth = _width * scale;
    float scaledHeight = _height * scale;
    _sprite.setPosition((1920 - scaledWidth) / 2.0f, (1080 - scaledHeight) / 2.0f);
}

bool GraphicRenderer::loadFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }

    std::string format;
    file >> format;
    file >> std::ws;
    char next = file.peek();

    while (next == '#') {
        std::string comment;
        std::getline(file, comment);
        file >> std::ws;
        next = file.peek();
    }

    file >> _width >> _height;
    int maxColorValue;
    file >> maxColorValue;
    _pixels.resize(_width * _height * 4);

    for (int y = 0; y < _height; y++) {
        for (int x = 0; x < _width; x++) {
            int r, g, b;
            file >> r >> g >> b;

            int index = (y * _width + x) * 4;
            _pixels[index] = static_cast<sf::Uint8>(r);
            _pixels[index + 1] = static_cast<sf::Uint8>(g);
            _pixels[index + 2] = static_cast<sf::Uint8>(b);
            _pixels[index + 3] = 255;
        }
    }
    return true;
}

void GraphicRenderer::exportToPNG() const
{
    sf::Texture exportTexture;
    if (!exportTexture.create(_width, _height)) {
        std::cerr << "Failed to create texture for export." << std::endl;
        return;
    }
    exportTexture.update(_pixels.data());

    std::string outputFilename = _inputFilename;
    size_t dotPos = outputFilename.find_last_of('.');
    if (dotPos != std::string::npos) {
        outputFilename = outputFilename.substr(0, dotPos);
    }
    outputFilename += ".png";

    sf::Image image = exportTexture.copyToImage();
    if (image.saveToFile(outputFilename)) {
        std::cout << "Image exported to: " << outputFilename << std::endl;
    } else {
        std::cerr << "Failed to export image." << std::endl;
    }
}

void GraphicRenderer::run()
{
    while (_window.isOpen()) {
        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                _window.close();

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                _window.close();
        }

        _window.clear(sf::Color::Black);
        _window.draw(_sprite);
        _window.display();
    }
    exportToPNG();
}
