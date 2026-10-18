//
// Created by StarredNaga on 17.10.2026.
//

#ifndef STARSVIEW_STAR_H
#define STARSVIEW_STAR_H

#include <stdexcept>
#include <string>
#include <SFML/System/Vector3.hpp>
#include <SFML/Graphics/Color.hpp>

class Star {
public:

    Star() : name("Unknown"), center(0.f, 0.f, 0.f), radius(1.f), color(sf::Color::White) {}

    Star(const std::string &name, sf::Vector3f center, float radius, sf::Color color) {

        if (name.empty()) throw std::invalid_argument("Star name cannot be empty");
        if (radius <= 0) throw std::invalid_argument("Star radius must be greater than zero");

        this->name = name;
        this->center = center;
        this->radius = radius;
        this->color = color;
    }

    std::string getName() const { return this->name; }
    sf::Vector3f getCenter() const { return this->center; }
    float getRadius() const { return this->radius; }
    sf::Color getColor() const { return this->color; }

private:
    std::string name;
    sf::Vector3f center;
    float radius;
    sf::Color color;
};

#endif //STARSVIEW_STAR_H
