//
// Created by livefish on 5/19/24.
//

#ifndef MEGACLOCKGAMEWITHTIMETRAVELLING_CARS_H
#define MEGACLOCKGAMEWITHTIMETRAVELLING_CARS_H

#include "mcgwtt/components/Box2dGraphics.h"

namespace mcgwtt {
    enum class Cell {
        Road, Boarder, Filler, Spawn
    };

    class CarMap {
    private:
        std::vector<Cell> _map;

    public:
        uint _width = 0, _height = 0;


        void set(uint x, uint y, Cell c) {
            _map[y * _width + x] = c;
        }

        Cell get(uint x, uint y) {
            return _map[y * _width + x];
        }

        CarMap() = default;

        explicit CarMap(const engine::Texture &tex)
                : _width(tex.getTex()->getSize().x), _height(tex.getTex()->getSize().y) {
            _map.resize(tex.getTex()->getSize().x * tex.getTex()->getSize().y); // FIXME: GOYDAAA
            auto img = tex.getTex()->copyToImage();
            for (uint y = 0; y < tex.getTex()->getSize().y; ++y) {
                for (uint x = 0; x < tex.getTex()->getSize().x; ++x) {
                    sf::Color pixel = img.getPixel(x, y);
                    if (pixel.a > 0) {
                        if (pixel == sf::Color::Yellow)
                            set(x, y, Cell::Filler);
                        else
                            set(x, y, Cell::Boarder);
                    } else {
                        set(x, y, Cell::Road);
                    }
                }
            }
        }
        void print() {
            std::cout << "__________________________________________\n\n\n";
            for (uint y = 0; y < _height; ++y) {
                for (uint x = 0; x < _width; ++x) {
                    if (get(x, y) == Cell::Boarder) {
                        std::cout << "**";
                    } else if (get(x, y) == Cell::Filler) {
                        std::cout << "##";
                    } else {
                        std::cout << "  ";
                    }
                }
                std::cout << "\n";
            }
        }
    };

    struct MapData : engine::Event {
        CarMap _map;
        std::vector<b2Fixture *> _fixtures;
        b2Body *_body;

        MapData(const CarMap &map, const std::vector<b2Fixture *> &fixtures, b2Body *body) : _map(map),
                                                                                             _fixtures(fixtures),
                                                                                             _body(body) {}
    };


    class CarMapPhysics : public engine::components::PhysicsComponent {
    private:
        b2Body *_body{nullptr};
        engine::Texture _mapTex;
        CarMap _map;

        void tick(engine::game::Game &game) override {

        }

        void init(engine::game::Game &game) override {
            b2BodyDef bd;
            bd.type = b2_staticBody;
            bd.position.Set(-64, -64);
            _body = game._world->CreateBody(&bd);
            b2PolygonShape shapeBody;
            std::vector<b2Fixture *> fixtures;

            for (uint y = 0; y < _map._height; y++) {
                for (uint x = 0; x < _map._width; x++) {
                    if (_map.get(x, y) == Cell::Boarder) {
                        shapeBody.SetAsBox(0.5, 0.5, {x * 1.f, y * 1.f}, 0);
                        fixtures.push_back(_body->CreateFixture(&shapeBody, 5.0f));
                    }
                }
            }
            _map.print();

            notify(MapData(_map, fixtures, _body));
        }

    public:
        explicit CarMapPhysics(const std::string &mapTex)
                : _mapTex(mapTex), _map(_mapTex) {
        }
    };

    class CarMapGraphics : public BodyGraphics {
    private:
        CarMap _map;
        engine::Texture _borderTex, _roadTex;
        sf::Sprite _fillSprite;

        void initSprites(const MapData *mapData) {
            _map = mapData->_map;
            _body = mapData->_body;

            sf::ConvexShape body;
            sf::Texture *tex = _borderTex.getTex();
            body.setTexture(tex);

            for (auto &fix : mapData->_fixtures) {
                _shapes[fix] = body;
            }
            _fillSprite.setTexture(*_borderTex.getTex());
            _fillSprite.setScale({1.f / _borderTex.getTex()->getSize().x, 1.f / _borderTex.getTex()->getSize().y});
            _fillSprite.setRotation(0);
        }

    public:
        explicit CarMapGraphics(sf::RenderWindow *win,
                                const std::string &borderTex,
                                const std::string &roadTex
        )
                : BodyGraphics(win), _borderTex(borderTex), _roadTex(roadTex) {

        }

        void draw() override {
            BodyGraphics::draw();
            if (_map._width == 0)
                return;

            for (uint y = 0; y < _map._height; y++) {
                for (uint x = 0; x < _map._width; x++) {
                    if (_map.get(x, y) == Cell::Filler) {
                        _fillSprite.setPosition(static_cast<float>(x) - 64.5f, static_cast<float>(y) - 64.5f);
                        _win->draw(_fillSprite);
                    }
                }
            }
        }

        void onNotify(const engine::Event &event) override {
            ENGINE_CHECK_EVENT(MapData, initSprites(e);)
        }
    };
}


#endif //MEGACLOCKGAMEWITHTIMETRAVELLING_CARS_H