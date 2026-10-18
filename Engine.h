//
// Created by StarredNaga on 18.10.2026.
//

#ifndef STARSVIEW_ENGINE_H
#define STARSVIEW_ENGINE_H
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector3.hpp>

#include "Camera.h"


class Engine {

    public:

    static sf::Vector3f TransformCamera(const Camera &camera);

    static std::vector<sf::Vector2f> TransformPoints(const std::vector<sf::Vector3f> &points, const Camera &camera,
                                                     sf::Vector2f screenCenter);

    static float TransformPoint(const sf::Vector3f &point, const Camera &camera,
                                sf::Vector2f screenCenter, sf::Vector2f& outScreenPoint);


    static std::vector<sf::Vector3f> CreateCircle(float radius, sf::Vector3f center, int segments);
};


#endif //STARSVIEW_ENGINE_H
