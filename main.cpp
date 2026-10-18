#include <SFML/Graphics.hpp>
#include <optional>
#include <iostream>

#include "Camera.h"
#include "SceneRenderer.h"
#include "StarCatalog.h"
#include "WindowSettings.h"


int main() {

    sf::RenderWindow window(sf::VideoMode({WindowSettings::windowWidth, WindowSettings::windowHeight}),
        WindowSettings::windowName);

    window.setFramerateLimit(WindowSettings::fpsLimit);

    auto centerX = WindowSettings::windowWidth / 2.0f;
    auto centerY = WindowSettings::windowHeight / 2.0f;

    auto camera = Camera(WindowSettings::commonCameraFov, WindowSettings::commonCameraRadius,
        WindowSettings::commonCameraYaw, WindowSettings::commonCameraPitch);

    auto starCatalog = StarCatalog(WindowSettings::saveLoadFile);

    sf::Font font;

    if (!font.openFromFile(WindowSettings::fontFile)) {

        std::cerr << "Error loading font!" << std::endl;
        return -1;
    }

    auto mustRender = true;

    while (window.isOpen()) {

        while (const std::optional<sf::Event> event = window.pollEvent()) {

            if (event->is<sf::Event::Closed>()) {

                window.close();
            }

            if (const auto* mouseWheel = event->getIf<sf::Event::MouseWheelScrolled>()) {

                mustRender = true;

                auto movement = mouseWheel->delta * WindowSettings::scrollSensitivity;

                if (camera.GetRadius() - movement >= camera.minRadius
                    && camera.GetRadius() - movement <= camera.maxRadius) {

                    camera.SetRadius(camera.GetRadius() - movement);
                }

            }

        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {

            starCatalog.saveToFile(WindowSettings::saveLoadFile);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {

            camera.SetYaw(camera.GetYaw() - WindowSettings::horizontalRotateSensitivity);

            mustRender = true;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {

            camera.SetYaw(camera.GetYaw() + WindowSettings::horizontalRotateSensitivity);

            mustRender = true;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)
            && camera.GetPitch() - WindowSettings::verticalRotateSensitivity >= camera.minPitch) {

            camera.SetPitch(camera.GetPitch() - WindowSettings::verticalRotateSensitivity);

            mustRender = true;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)
            && camera.GetPitch() + WindowSettings::verticalRotateSensitivity <= camera.maxPitch) {

            camera.SetPitch(camera.GetPitch() + WindowSettings::verticalRotateSensitivity);

            mustRender = true;
        }

        if (!mustRender) continue;

        SceneRenderer::Render(window, camera, starCatalog.getStars(), centerX, centerY, font);

        mustRender = false;
    }

    return 0;
}
