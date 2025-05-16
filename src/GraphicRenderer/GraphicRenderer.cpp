/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** GraphicRenderer implementation
*/

#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <vector>

#include "GraphicRenderer.hpp"
#include "../Core/Core.hpp"

namespace AnsiColor {
const std::string RESET      = "\033[0m";
const std::string BOLD       = "\033[1m";
const std::string UNDERLINE  = "\033[4m";
const std::string GREEN      = "\033[32m";
const std::string CYAN       = "\033[36m";
}

GraphicRenderer::GraphicRenderer(
    const std::string &configFilename,
    std::string const &previewFilename,
    std::string const &finalFilename,
    bool isPreviewMode,
    bool isProgressiveMode
) : _inputFilename(previewFilename),
    _finalFilename(finalFilename.empty() ? "output.ppm" : finalFilename),
    _isPreviewMode(isPreviewMode),
    _isProgressiveMode(isProgressiveMode),
    _configFilename(configFilename),
    _inotify()
{
    _inotify.addWatch(_configFilename);
    _width = 1920;
    _height = 1080;
    if (!_isPreviewMode) {
        _pixels.resize(_width * _height * 4, 0);
        for (size_t i = 3; i < _pixels.size(); i += 4) {
            _pixels[i] = 255;
        }
    }

    _window.create(sf::VideoMode(1920, 1080), "Ray Tracer Visualizer - Preview Mode");

    if (!_font.loadFromFile("assets/Arial.ttf"))
        std::cerr << "Warning: Could not load font for loading message" << std::endl;
    else {
        _loadingText.setFont(_font);
        _loadingText.setCharacterSize(24);
        _loadingText.setFillColor(sf::Color::White);
    }
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

void GraphicRenderer::displayLoadingMessage(const std::string& message)
{
    if (_font.getInfo().family.empty())
        return;

    sf::Text text = _loadingText;
    text.setString(message);

    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top + textRect.height/2.0f);
    text.setPosition(1920/2.0f, 1080/2.0f);

    sf::RectangleShape background(sf::Vector2f(textRect.width + 20, textRect.height + 20));
    background.setFillColor(sf::Color(0, 0, 0, 200));
    background.setOrigin(background.getSize().x/2.0f, background.getSize().y/2.0f);
    background.setPosition(1920/2.0f, 1080/2.0f);

    _window.clear(sf::Color::Black);
    _window.draw(background);
    _window.draw(text);
    _window.display();
}

void GraphicRenderer::switchToFinalImage()
{
    if (!_isPreviewMode)
        return;

    displayLoadingMessage("Loading final image...");
    if (!loadFromFile(_finalFilename)) {
        std::cerr << "Failed to load final PPM file: " << _finalFilename << std::endl;
        return;
    }

    _window.setTitle("Ray Tracer Visualizer - Final Image");
    _texture.create(_width, _height);
    _texture.update(_pixels.data());
    _sprite.setTexture(_texture, true);

    float scaleX = 1920.0f / static_cast<float>(_width);
    float scaleY = 1080.0f / static_cast<float>(_height);
    float scale = std::min(scaleX, scaleY);
    _sprite.setScale(scale, scale);

    float scaledWidth = _width * scale;
    float scaledHeight = _height * scale;
    _sprite.setPosition((1920.0f - scaledWidth) / 2.0f, (1080.0f - scaledHeight) / 2.0f);
    _isPreviewMode = false;
}

void GraphicRenderer::exportToPNG(const std::string& outputFilename) const
{
    sf::Texture exportTexture;
    if (!exportTexture.create(_width, _height)) {
        std::cerr << "Failed to create texture for export." << std::endl;
        return;
    }
    exportTexture.update(_pixels.data());

    sf::Image image = exportTexture.copyToImage();
    if (image.saveToFile(outputFilename)) {
        std::cout << AnsiColor::GREEN << "✅ " << AnsiColor::BOLD << "Image exported to: "
                  << AnsiColor::RESET << AnsiColor::CYAN << AnsiColor::UNDERLINE
                  << outputFilename << AnsiColor::RESET << std::endl;
    } else {
        std::cerr << "Failed to export image to: " << outputFilename << std::endl;
    }
}

runResult_e GraphicRenderer::handleCamMovement(sf::Event event)
{
    if (event.type != sf::Event::KeyPressed)
        return NOTHING;

    runResult_e result = NOTHING;
    switch (event.key.code) {
        case sf::Keyboard::Z: result = MOVE_FORWARD; break;
        case sf::Keyboard::S: result = MOVE_BACKWARD; break;
        case sf::Keyboard::D: result = MOVE_RIGHT; break;
        case sf::Keyboard::Q: result = MOVE_LEFT; break;
        case sf::Keyboard::A: result = MOVE_UP; break;
        case sf::Keyboard::E: result = MOVE_DOWN; break;
        default: return NOTHING;
    }
    return result;
}

runResult_e GraphicRenderer::run(const std::atomic<bool> &renderingComplete)
{
    bool finalImageLoaded = false;
    bool pngExported = false;
    sf::Clock checkClock;

    if (_isPreviewMode) {
        if (!loadFromFile(_inputFilename)) {
            std::cerr << "Failed to load preview PPM file: " << _inputFilename << std::endl;
            throw std::runtime_error("Failed to load preview PPM file");
        }
    }

    if (!_texture.create(_width, _height)) {
        std::cerr << "Failed to create texture." << std::endl;
        throw std::runtime_error("Failed to create texture");
    }

    _texture.update(_pixels.data());
    _sprite.setTexture(_texture);
    float scaleX = 1920.0f / static_cast<float>(_width);
    float scaleY = 1080.0f / static_cast<float>(_height);
    float scale = std::min(scaleX, scaleY);
    _sprite.setScale(scale, scale);

    float scaledWidth = _width * scale;
    float scaledHeight = _height * scale;
    _sprite.setPosition((1920.0f - scaledWidth) / 2.0f, (1080.0f - scaledHeight) / 2.0f);

    if (_isPreviewMode)
        exportToPNG("preview.png");

    while (_window.isOpen()) {
        if (_inotify.fileModified()) {
            return RELOAD_CONFIG;
        }

        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                _window.close();

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                _window.close();

            runResult_e camMovementResult = handleCamMovement(event);
            if (camMovementResult != NOTHING) {
                return camMovementResult;
            }
        }

        if (
            _isPreviewMode &&
            !_isProgressiveMode &&
            !finalImageLoaded &&
            renderingComplete.load()
        ) {
            switchToFinalImage();
            finalImageLoaded = true;
            exportToPNG("output.png");
        }

        _window.clear(sf::Color::Black);
        _window.draw(_sprite);

        if ((_isPreviewMode || _isProgressiveMode) && _font.getInfo().family.length() > 0) {
            sf::Text statusText;
            statusText.setFont(_font);
            statusText.setCharacterSize(16);
            statusText.setFillColor(sf::Color::White);

            if (renderingComplete.load() && !_isProgressiveMode) {
                statusText.setString("Switching to final image...");
            } else if (_isProgressiveMode) {
                int n = (static_cast<int>(checkClock.getElapsedTime().asSeconds() * 2) % 4);
                std::string dots;
                for (int i = 0; i < n; i++) dots += ".";

                if (renderingComplete.load()) {
                    if (!pngExported) {
                        exportToPNG("output.png");
                        pngExported = true;
                    }
                } else {
                    statusText.setString("Progressive rendering" + dots);
                }
            } else {
                int n = (static_cast<int>(checkClock.getElapsedTime().asSeconds() * 2) % 4);
                std::string dots;
                for (int i = 0; i < n; i++) dots += ".";
                statusText.setString("Rendering full resolution image" + dots);
            }

            if (!pngExported) {
                statusText.setPosition(10, 10);
                sf::FloatRect textRect = statusText.getLocalBounds();
                sf::RectangleShape back(sf::Vector2f(textRect.width + 20,
                    textRect.height + 10));
                back.setFillColor(sf::Color(0, 0, 0, 180));
                back.setPosition(5, 5);
                _window.draw(back);
                _window.draw(statusText);
            }
        }

        _window.display();
        sf::sleep(sf::milliseconds(33));
    }
    return FINISHED;
}

void GraphicRenderer::updateProgressiveRendering(
    const std::vector<std::vector<Graphic::color_t>> &pixelBuffer)
{
    if (!_isProgressiveMode) {
        return;
    }

    std::lock_guard<std::mutex> lock(_pixelMutex);
    updatePixelsFromBuffer(pixelBuffer);
    updateTexture();
}

void GraphicRenderer::updatePixelsFromBuffer(
    const std::vector<std::vector<Graphic::color_t>> &pixelBuffer)
{
    int height = pixelBuffer.size();
    if (height == 0) return;

    int width = pixelBuffer[0].size();
    if (width == 0) return;

    if (width != _width || height != _height) {
        _width = width;
        _height = height;
        _pixels.resize(width * height * 4);
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            const auto &color = pixelBuffer[y][x];
            int r = static_cast<int>(std::round(std::max(0.0, std::min(255.0, color.r))));
            int g = static_cast<int>(std::round(std::max(0.0, std::min(255.0, color.g))));
            int b = static_cast<int>(std::round(std::max(0.0, std::min(255.0, color.b))));

            int index = (y * width + x) * 4;
            _pixels[index] = static_cast<sf::Uint8>(r);
            _pixels[index + 1] = static_cast<sf::Uint8>(g);
            _pixels[index + 2] = static_cast<sf::Uint8>(b);
            _pixels[index + 3] = 255;
        }
    }
}

void GraphicRenderer::updateTexture()
{
    if (_width != static_cast<int>(_texture.getSize().x) ||
        _height != static_cast<int>(_texture.getSize().y)) {
        if (!_texture.create(_width, _height)) {
            std::cerr << "Failed to recreate texture" << std::endl;
            return;
        }

        _sprite.setTexture(_texture, true);
        float scaleX = 1920.0f / static_cast<float>(_width);
        float scaleY = 1080.0f / static_cast<float>(_height);
        float scale = std::min(scaleX, scaleY);
        _sprite.setScale(scale, scale);

        float scaledWidth = _width * scale;
        float scaledHeight = _height * scale;
        _sprite.setPosition((1920.0f - scaledWidth) / 2.0f, (1080.0f - scaledHeight) / 2.0f);
    }

    _texture.update(_pixels.data());
}

void GraphicRenderer::setProgressiveMode(bool isProgressiveMode)
{
    _isProgressiveMode = isProgressiveMode;
    if (_isProgressiveMode) {
        _window.setTitle("Ray Tracer Visualizer - Progressive Mode");
    }
}

void GraphicRenderer::setPreviewMode(bool isPreviewMode)
{
    _isPreviewMode = isPreviewMode;
    if (_isPreviewMode) {
        _window.setTitle("Ray Tracer Visualizer - Preview Mode");
    }
}
