//
// Created by StarredNaga on 18.10.2026.
//

#ifndef STARSVIEW_SCENERENDERER_H
#define STARSVIEW_SCENERENDERER_H
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Camera.h"
#include "Star.h"


class SceneRenderer {

    public:
    static void Render(sf::RenderWindow &window, const Camera &camera, const std::vector<Star> &stars,
    float centerX, float centerY, const sf::Font& font);
};


#endif //STARSVIEW_SCENERENDERER_H
