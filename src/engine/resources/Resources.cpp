// Copyright (c) 2024. ATF project organization!

//
// Created by Дом on 25.06.2024.
//

#include "Resources.h"

namespace engine {
    Resource::Resource() : _path("") {
        _allocated++;
        std::cout << "Res created (" << _allocated << " allocated)\n";
    }

    Resource::Resource(std::string loadPath) : _path(std::move(loadPath)) {
        _allocated++;
        std::cout << "Res created (\"" << _path << "\") (" << _allocated << " allocated)\n";
    }

    Resource::~Resource() {
        _allocated--;
        std::cout << "Res free (\"" << _path << "\") (" << _allocated << " allocated)\n";
    }

    void Resource::setPath(const std::string &path) {
        _path = path;
    }

    std::string Resource::getResourcePath() const {
        return _path;
    }

    Texture::Texture(const std::string &fileName) : Resource(fileName) {
        _tex = loadResource<sf::Texture>(fileName);
    }

    Texture::Texture(sf::Texture *tex, const std::string &name) : Resource(name) {
        _tex.reset(tex);
    }

    Texture *Texture::loadCommon(const std::string &name) {
        return new Texture("common/textures/" + name);
    }

    void Texture::load() {
        _tex = loadResource<sf::Texture>(_path);
    }

    sf::Texture *Texture::getTex() const {
        return _tex.get();
    }

    SoundBuffer::SoundBuffer(const std::string &fileName) : Resource(fileName) {
        _soundBuffer = loadResource<sf::SoundBuffer>(fileName);
    }

    SoundBuffer *SoundBuffer::loadCommon(const std::string &name) {
        return new SoundBuffer("common/sounds/" + name);
    }

    void SoundBuffer::load() {
        _soundBuffer = loadResource<sf::SoundBuffer>(_path);
    }

    const sf::SoundBuffer &SoundBuffer::getBuffer() const {
        return *_soundBuffer;
    }

    Music::Music(const std::string &fileName) : Resource(fileName) {
        _music = loadResource<sf::Music>(fileName);
    }

    Music *Music::loadCommon(const std::string &name) {
        return new Music("common/music/" + name);
    }

    void Music::load() {
        _music = loadResource<sf::Music>(_path);
    }

    void Music::play() {
        if (_music->getStatus() != sf::SoundStream::Status::Playing)
            _music->play();
    }

    void Music::setVolume(float volume) {
        _music->setVolume(volume);
    }

    Font::Font(const std::string &fileName) : Resource(fileName) {
        _font = loadResource<sf::Font>(fileName);
    }

    Font *Font::loadCommon(const std::string &name) {
        return new Font("common/fonts/" + name);
    }

    const sf::Font &Font::getFont() {
        return *_font;
    }

    void Font::load() {
        _font = loadResource<sf::Font>(_path);
    }

    void ResourceHandler::setLoadPath(const std::string &newLoadPath) {
        _loadPath = newLoadPath;
    }

    std::string ResourceHandler::getLoadPath() {
        return _loadPath;
    }

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCInconsistentNamingInspection"
    ResourceHandler *resourceHandler = nullptr;
#pragma clang diagnostic pop
}
