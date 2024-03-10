//
// Created by livefish on 2/20/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_RESOURCES_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_RESOURCES_H

#include <utility>

#include "EngineDef.h"

namespace engine {
    extern std::map<std::string, std::string> extensionFolder;

    template<typename T>
        T *loadResource(const std::string &FileName) {
            if (FileName.empty())
                throw std::runtime_error("Empty filename for resource loading");
            std::string ext = FileName.substr(FileName.find_last_of('.'));
            std::string folder = "../resources/" + extensionFolder[ext] + "/";
            std::string path = folder + FileName;
            auto data = new T();
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
                std::cerr << "Failed to loadResource \"" << path << "\", exiting'" << std::endl;
                exit(30);
            }
            return data;
        }

    class Resource {
        friend class ResourceHandler;

    public:
        inline static int allocated = 0;
        Resource() {
            allocated++;
            std::cout << "Res created (" << allocated << " allocated)\n";
        }

        virtual ~Resource() {
            allocated--;
            std::cout << "Res free (\"" << _path << "\") (" << allocated << " allocated)\n";
        };

        explicit Resource(std::string LoadPath) : _path(std::move(LoadPath)) {
            allocated++;
            std::cout << "Res created (\"" << _path << "\") (" << allocated << " allocated)\n";
        }

        virtual void load() = 0;

        void setPath(const std::string &Path) {
            _path = Path;
        }

        [[nodiscard]] std::string getResourcePath() const {
            return _path;
        }

    protected:
        std::string _path;
    };

    class Texture : public Resource {
    private:
        sf::Texture _tex;

    public:
        Texture() = default;
        explicit Texture(const std::string &FileName) : Resource(FileName) {
            _tex = *loadResource<sf::Texture>(_path);
        }

        void load() override {
            _tex = *loadResource<sf::Texture>(_path);
        }

        operator const sf::Texture &() const { // NOLINT(*-explicit-constructor)
            return _tex;
        }
    };

    class SoundBuffer : public Resource {
    private:
        sf::SoundBuffer _soundBuffer;

    public:
        SoundBuffer() = default;

        explicit SoundBuffer(const std::string &FileName) : Resource(FileName) {
            _soundBuffer = *loadResource<sf::SoundBuffer>(FileName);
        }

        void load() override {
            _soundBuffer = *loadResource<sf::SoundBuffer>(_path);
        }

        operator const sf::SoundBuffer &() const { // NOLINT(*-explicit-constructor)
            return _soundBuffer;
        }
    };

    class Music : public Resource {
    private:
        sf::Music *_music{};

    public:
        Music() = default;
        explicit Music(const std::string &FileName) : Resource(FileName) {
            _music = loadResource<sf::Music>(FileName);
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
    public:
        sf::Font _font;

        Font() = default;
        explicit Font(const std::string &FileName) : Resource(FileName) {
            _font = *loadResource<sf::Font>(FileName);
        }

        void load() override {
            _font = *loadResource<sf::Font>(_path);
        }
    };

    using resource_ptr = std::unique_ptr<Resource>;

    class ResourceHandler {
    private:
        std::unordered_map<std::string, resource_ptr> _res;

    public:
        template<typename T>
            requires std::is_base_of_v<Resource, T>
            T *getResource(const std::string &name) {
                auto ptr = dynamic_cast<T *>(_res.find(name)->second);
                if (!ptr)
                    throw std::runtime_error("Res: " + name + " not found!");
                return ptr;
            }

        template<typename T>
            requires std::is_base_of_v<Resource, T>
            T *addRes(T *mem, const std::string &FileName = "", const std::string &Name = "") {
                std::string resName;
                if (!Name.empty())
                    resName = Name;
                else if (!FileName.empty())
                    resName = FileName;
                else if (!mem->getResourcePath().empty())
                    resName = mem->getResourcePath();
                else
                    throw std::runtime_error("No name provided for resource!");

                if (!FileName.empty())
                    mem->setPath(FileName);

                auto find = _res.find(resName);
                if (find != _res.end()) {
                    auto ptr = dynamic_cast<T *>(find->second.get());
                    if (ptr) {
                        delete mem;
                        return ptr;
                    }
                }

                mem->load();
                _res.emplace(resName, resource_ptr(mem));

                return mem;
            }
    };

    extern ResourceHandler resourceHandler;
} // engine

#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_RESOURCES_H
