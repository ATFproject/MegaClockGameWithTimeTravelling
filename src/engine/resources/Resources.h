// Copyright (c) 2024. ATF project organization!

//
// Created by livefish on 2/20/24.
//



#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_RESOURCES_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_RESOURCES_H

namespace engine {
    template<typename T>
        std::unique_ptr<T> loadResource(const std::string &fileName);

    class Resource {
        friend class ResourceHandler;

    public:
        inline static int _allocated = 0;

        Resource();
        explicit Resource(std::string loadPath);
        virtual ~Resource();;

        virtual void load() = 0;

        void setPath(const std::string &path);
        [[nodiscard]] std::string getResourcePath() const;

    protected:
        std::string _path = "Empty path";
    };

    class Texture : public Resource {
    public:
        Texture() = default;
        explicit Texture(const std::string &fileName);
        explicit Texture(sf::Texture *tex, const std::string &name = "");

        static Texture *loadCommon(const std::string &name);
        void load() override;

        [[nodiscard]] sf::Texture *getTex() const;

    private:
        std::unique_ptr<sf::Texture> _tex;
    };

    class SoundBuffer : public Resource {
    public:
        SoundBuffer() = default;
        explicit SoundBuffer(const std::string &fileName);

        static SoundBuffer *loadCommon(const std::string &name);
        void load() override;

        [[nodiscard]] const sf::SoundBuffer &getBuffer() const;

    private:
        std::unique_ptr<sf::SoundBuffer> _soundBuffer;
    };

    class Music : public Resource {
    public:
        Music() = default;
        explicit Music(const std::string &fileName);

        static Music *loadCommon(const std::string &name);
        void load() override;

        void play();
        void setVolume(float volume);

    private:
        std::unique_ptr<sf::Music> _music;

    };

    class Font : public Resource {
    public:
        Font() = default;
        explicit Font(const std::string &fileName);

        static Font *loadCommon(const std::string &name);
        void load() override;

        const sf::Font &getFont();

    private:
        std::unique_ptr<sf::Font> _font;
    };

    using resourcePtr = std::unique_ptr<Resource>;

    class ResourceHandler {
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

        void setLoadPath(const std::string &newLoadPath);
        std::string getLoadPath();

    private:
        std::unordered_map<std::string, resourcePtr> _res;
        std::string _loadPath;
    };

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCInconsistentNamingInspection"
    extern ResourceHandler *resourceHandler;
#pragma clang diagnostic pop

    template<typename T>
        std::unique_ptr<T> loadResource(const std::string &fileName) {
            if (fileName.empty())
                throw std::runtime_error("Empty filename for resource loading");
            std::string folder = "../bin/" + (fileName.starts_with("common") ? "" : resourceHandler->getLoadPath());
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
