// Copyright (c) 2024. ATF project organization!

//
// Created by livefish on 2/20/24.
//



#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_RESOURCES_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_RESOURCES_H

#include "EngineDef.h"

#include <utility>

namespace engine {
    template<typename T>
        std::unique_ptr<T> loadResource(const std::string &fileName);

    class Resource {
        friend class ResourceHandler;

    public:
        inline static int _allocated = 0;

        Resource() {
            _path = "";
            _allocated++;
            std::cout << "Res created (" << _allocated << " allocated)\n";
        }

        explicit Resource(std::string loadPath) : _path(std::move(loadPath)) {
            _allocated++;
            std::cout << "Res created (\"" << _path << "\") (" << _allocated << " allocated)\n";
        }

        virtual ~Resource() {
            _allocated--;
            std::cout << "Res free (\"" << _path << "\") (" << _allocated << " allocated)\n";
        };

        virtual void load() = 0;

        void setPath(const std::string &path) {
            _path = path;
        }

        [[nodiscard]] std::string getResourcePath() const {
            return _path;
        }

    protected:
        std::string _path = "Empty path";
    };

    class Texture : public Resource {
    private:
        std::unique_ptr<sf::Texture> _tex;

    public:
        Texture() = default;

        explicit Texture(const std::string &fileName) : Resource(fileName) {
            _tex = loadResource<sf::Texture>(fileName);
        }

        explicit Texture(sf::Texture *tex, const std::string &name = "") : Resource(name) {
            _tex.reset(tex);
        }

        static Texture *loadCommon(const std::string &name) {
            return new Texture("common/textures/" + name);
        }

        void load() override {
            _tex = loadResource<sf::Texture>(_path);
        }

        [[nodiscard]] sf::Texture *getTex() const {
            return _tex.get();
        }
    };

    class SoundBuffer : public Resource {
    private:
        std::unique_ptr<sf::SoundBuffer> _soundBuffer;

    public:
        SoundBuffer() = default;

        explicit SoundBuffer(const std::string &fileName) : Resource(fileName) {
            _soundBuffer = loadResource<sf::SoundBuffer>(fileName);
        }

        static SoundBuffer *loadCommon(const std::string &name) {
            return new SoundBuffer("common/sounds/" + name);
        }

        void load() override {
            _soundBuffer = loadResource<sf::SoundBuffer>(_path);
        }

        [[nodiscard]] const sf::SoundBuffer &getBuffer() const {
            return *_soundBuffer;
        }
    };

    class Music : public Resource {
    private:
        std::unique_ptr<sf::Music> _music;

    public:
        Music() = default;
        explicit Music(const std::string &fileName) : Resource(fileName) {
            _music = loadResource<sf::Music>(fileName);
        }

        static Music *loadCommon(const std::string &name) {
            return new Music("common/music/" + name);
        }

        void load() override {
            _music = loadResource<sf::Music>(_path);
        }

        void play() {
            if (_music->getStatus() != sf::SoundStream::Status::Playing)
                _music->play();
        }

        void setVolume(float volume) {
            _music->setVolume(volume);
        }
    };

    class Font : public Resource {
    private:
        std::unique_ptr<sf::Font> _font;
    public:
        Font() = default;
        explicit Font(const std::string &fileName) : Resource(fileName) {
            _font = loadResource<sf::Font>(fileName);
        }

        static Font *loadCommon(const std::string &name) {
            return new Font("common/fonts/" + name);
        }

        const sf::Font &getFont() {
            return *_font;
        }

        void load() override {
            _font = loadResource<sf::Font>(_path);
        }
    };

    using resourcePtr = std::unique_ptr<Resource>;

    class ResourceHandler {
    private:
        std::unordered_map<std::string, resourcePtr> _res;
        std::string _loadPath;

    public:
        template<typename T>
            requires std::is_base_of_v<Resource, T>
            T *getResource(const std::string &name) {
                auto find = _res.find(name);
                if (find != _res.end())
                    throw std::runtime_error("Res: " + name + " not found!");
                auto ptr = dynamic_cast<T *>(_res.find(name)->second);
                if (!ptr)
                    throw std::runtime_error("Res: " + name + " not found!");
                return ptr;
            }

        template<typename T>
            requires std::is_base_of_v<Resource, T>
            T *addRes(const std::string &name, T *mem) {
                _res.try_emplace(name, resourcePtr(mem));
                return mem;
            }

        template<typename T>
            requires std::is_base_of_v<Resource, T>
            T *loadRes(T *mem) {
                std::string resName;
                if (!mem->getResourcePath().empty())
                    resName = mem->getResourcePath();
                else
                    throw std::runtime_error("No name provided for resource!");

                auto find = _res.find(resName);
                if (find != _res.end()) {
                    auto ptr = dynamic_cast<T *>(find->second.get());
                    if (ptr) {
                        delete mem;
                        return ptr;
                    }
                }

                mem->load();

                _res.try_emplace(resName, resourcePtr(mem));

                return mem;
            }

        void setLoadPath(const std::string &newLoadPath) {
            _loadPath = newLoadPath;
        }

        std::string getLoadPath() {
            return _loadPath;
        }
    };

    inline ResourceHandler resourceHandler;

    template<typename T>
        std::unique_ptr<T> loadResource(const std::string &fileName) {
            if (fileName.empty())
                throw std::runtime_error("Empty filename for resource loading");
            std::string addPath = fileName.starts_with("common")? "" : resourceHandler.getLoadPath();
            std::string folder = "../bin/" + addPath;
            std::string path = folder + fileName;
            auto data = std::make_unique<T>();
            bool res;

            if constexpr (requires { data->loadFromFile(path); }) {
                res = data->loadFromFile(path);
            } else if constexpr (requires { data->openFromFile(path); }) {
                res = data->openFromFile(path);
            } else {
                std::cerr << "No matching loadResource function found!" << std::endl;
                res = false;
            }
            if (!res) {
                throw std::runtime_error("Failed to loadResource \"" + path + "\"");
            }
            return data;
        }
} // engine

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_RESOURCES_H
