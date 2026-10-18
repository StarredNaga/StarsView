//
// Created by StarredNaga on 18.10.2026.
//

#include "Engine.h"

#include <cmath>
#include <stdexcept>

sf::Vector3f Engine::TransformCamera(const Camera &camera) {

    auto R = camera.GetRadius();
    auto pitch = camera.GetPitch();
    auto yaw = camera.GetYaw();

    auto cam_x = R * std::cos(pitch) * std::sin(yaw);
    auto cam_y = R * std::sin(pitch);
    auto cam_z = R * std::cos(pitch) * std::cos(yaw);

    return {cam_x, cam_y, cam_z};
}

float Engine::TransformPoint(const sf::Vector3f &point, const Camera &camera,
                            const sf::Vector2f screenCenter, sf::Vector2f& outScreenPoint) {

    auto camPosition = TransformCamera(camera);
    auto yaw = camera.GetYaw();
    auto pitch = camera.GetPitch();
    auto fov = camera.GetFov();

    float cosYaw = std::cos(yaw);
    float sinYaw = std::sin(yaw);
    float cosPitch = std::cos(pitch);
    float sinPitch = std::sin(pitch);

    auto dx = point.x - camPosition.x;
    auto dy = point.y - camPosition.y;
    auto dz = point.z - camPosition.z;

    auto x_r = dx * cosYaw - dz * sinYaw;
    auto z_r = dx * sinYaw + dz * cosYaw;

    auto x_c = x_r;
    auto y_c = dy * cosPitch - z_r * sinPitch;
    auto z_c = dy * sinPitch + z_r * cosPitch;

    float depth = -z_c;

    if (depth <= 0.005f) {
        return -1.0f;
    }

    auto x_projected = (x_c * fov) / depth;
    auto y_projected = (y_c * fov) / depth;

    outScreenPoint = {x_projected + screenCenter.x, screenCenter.y - y_projected};
    return depth;
}


std::vector<sf::Vector2f> Engine::TransformPoints(const std::vector<sf::Vector3f>& points, const Camera &camera,
    const sf::Vector2f screenCenter) {

    std::vector<sf::Vector2f> resultPoints;

    resultPoints.reserve(points.size());

    for (const auto& point : points) {

        sf::Vector2f screenPoint;

        float depth = TransformPoint(point, camera, screenCenter, screenPoint);

        if (depth > 0.0f) {
            resultPoints.push_back(screenPoint);
        }
    }

    return resultPoints;
}

std::vector<sf::Vector3f> Engine::CreateCircle(const float radius, const sf::Vector3f center, const int segments) {

    std::vector<sf::Vector3f> points;

    if (segments <= 0) throw std::invalid_argument("segments must be greater than 0.");

    auto angle = 2.0f * std::numbers::pi_v<float> / segments;

    for (int i = 0; i < segments; i++)
    {
        auto pointAngle = angle * i;

        auto x = center.x + radius * std::cos(pointAngle);

        auto z = center.z + radius * std::sin(pointAngle);

        auto y = center.y;

        points.emplace_back(x, y, z);
    }
    return points;
}

