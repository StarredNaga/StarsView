//
// Created by StarredNaga on 18.10.2026.
//

#ifndef STARSVIEW_WINDOWSETTINGS_H
#define STARSVIEW_WINDOWSETTINGS_H
#include <string>
#include <SFML/Graphics/Color.hpp>


class WindowSettings {

    public:
    static constexpr std::string windowName = "Stars Viewer";

    static constexpr std::string saveLoadFile = "your save file";
    static constexpr std::string fontFile = "your font file";

    static constexpr int windowWidth = 1000;
    static constexpr int windowHeight = 800;

    static constexpr int fpsLimit = 60;

    static constexpr sf::Color clearColor = sf::Color::Black;

    static constexpr float horizontalRotateSensitivity = 0.04f;
    static constexpr float verticalRotateSensitivity = 0.04f;
    static constexpr float scrollSensitivity = 1.f;

    static constexpr float commonCameraFov = 500.f;
    static constexpr float commonCameraRadius = 60.f;
    static constexpr float commonCameraYaw = 0.f;
    static constexpr float commonCameraPitch = 0.4f;
};


#endif //STARSVIEW_WINDOWSETTINGS_H
