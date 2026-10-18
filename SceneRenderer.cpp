//
// Created by StarredNaga on 18.10.2026.
//

#include "SceneRenderer.h"

#include <cmath>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Engine.h"
#include "WindowSettings.h"

namespace {
    struct RenderableStar {
        const Star* starData;
        sf::Vector2f screenPos;
        float depth;
    };
}

static void drawDottedLine(sf::RenderWindow& window, sf::Vector2f start, sf::Vector2f end,
                           float dashLength, float gapLength, sf::Color color) {

    sf::VertexArray dottedLine(sf::PrimitiveType::Lines);

    sf::Vector2f direction = end - start;

    float totalLength = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (totalLength > 0) {
        direction /= totalLength;
    }

    float currentLength = 0.f;

    while (currentLength < totalLength) {

        sf::Vector2f p1 = start + direction * currentLength;

        currentLength = std::min(currentLength + dashLength, totalLength);

        sf::Vector2f p2 = start + direction * currentLength;

        dottedLine.append(sf::Vertex(p1, color));

        dottedLine.append(sf::Vertex(p2, color));

        currentLength += gapLength;
    }

    window.draw(dottedLine);
}

static sf::VertexArray createLine(const Camera &camera, sf::Vector2f center,
                                  const std::vector<sf::Vector3f>& points, sf::Color color, bool closed = false) {

    sf::VertexArray curve(sf::PrimitiveType::LineStrip);

    auto flatPoints = Engine::TransformPoints(points, camera, center);

    if (flatPoints.empty()) return curve;

    for (const auto& point : flatPoints) {

        curve.append(sf::Vertex(point, color));
    }

    if (closed) {

        curve.append(sf::Vertex(flatPoints[0], color));
    }

    return curve;
}

void SceneRenderer::Render(sf::RenderWindow &window, const Camera &camera, const std::vector<Star> &stars,
    float centerX, float centerY, const sf::Font& font) {

    const std::vector circles = {
        Engine::CreateCircle(10, {0, 0, 0}, 64),
        Engine::CreateCircle(20, {0, 0, 0}, 64),
        Engine::CreateCircle(30, {0, 0, 0}, 64),
        Engine::CreateCircle(35, {0, 0, 0}, 64)
    };

    const std::vector<std::vector<sf::Vector3f>> lines = {
        {sf::Vector3f({-35, 0, 0}), sf::Vector3f({35, 0, 0})},
        {sf::Vector3f({0, 0, 35}), sf::Vector3f({0, 0, -35})},
    };

     window.clear(WindowSettings::clearColor);

        for (const auto& circle : circles) {

            sf::VertexArray curve = createLine(camera, {centerX, centerY}, circle, sf::Color::Blue, true);

            window.draw(curve);
        }

        for (const auto& line : lines) {

            sf::VertexArray curve = createLine(camera, {centerX, centerY}, line, sf::Color::Blue);

            window.draw(curve);
        }

        std::vector<RenderableStar> visibleStars;

        visibleStars.reserve(stars.size());

        for (const auto& star : stars) {

            sf::Vector2f screenPos;

            float depth = Engine::TransformPoint(star.getCenter(), camera, {centerX, centerY}, screenPos);

            if (depth > 0.0f) {
                visibleStars.push_back({&star, screenPos, depth});
            }
        }

        std::sort(visibleStars.begin(), visibleStars.end(), [](const RenderableStar& a, const RenderableStar& b) {
            return a.depth > b.depth;
        });

        for (const auto& rStar : visibleStars) {

            const auto& star = *(rStar.starData);

            sf::Vector2f center = rStar.screenPos;

            if (star.getCenter().y > 0) {

                auto starCenter = star.getCenter();

                sf::VertexArray curve = createLine(camera, {centerX, centerY},
                    {starCenter, {starCenter.x, 0, starCenter.z}}, sf::Color::Cyan);

                window.draw(curve);
            }

            if (star.getCenter().y < 0) {

                sf::Vector2f endScreenPos;

                Engine::TransformPoint({star.getCenter().x, 0, star.getCenter().z}, camera,
{centerX, centerY}, endScreenPos);

                drawDottedLine(window, center, endScreenPos, 2.f, 6.f, sf::Color::Cyan);
            }

            auto circle = sf::CircleShape(star.getRadius(), 32);

            circle.setFillColor(star.getColor());

            circle.setPosition(sf::Vector2f(center.x - star.getRadius(), center.y - star.getRadius()));

            window.draw(circle);

            sf::Text text(font, star.getName(), 10);

            text.setFillColor(sf::Color::Cyan);

            text.setPosition(sf::Vector2f(center.x + star.getRadius() + 6.f, center.y - 10.f));

            window.draw(text);
        }

        window.display();
}
