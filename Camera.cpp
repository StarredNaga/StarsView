//
// Created by StarredNaga on 17.10.2026.
//

#include "Camera.h"

#include <stdexcept>

Camera::Camera(float fov, float radius, float yaw, float pitch) {

    if (fov <= minFov) throw std::invalid_argument("fov must be greater than minFov");

    if (fov > maxFov) throw std::invalid_argument("fov must be lower than maxFov");

    if (radius < minRadius) throw std::invalid_argument("radius must be greater than minRadius");

    if (radius > maxRadius) throw std::invalid_argument("radius must be lower than maxRadius");

    if (pitch < minPitch) throw std::invalid_argument("pitch must be greater than minPitch");

    if (pitch > maxPitch) throw std::invalid_argument("pitch must be lower than maxPitch");

    this->fov = fov;
    this->radius = radius;
    this->yaw = yaw;
    this->pitch = pitch;
}

float Camera::GetFov() const {
    return this->fov;
}

float Camera::GetRadius() const {
    return this->radius;
}

float Camera::GetYaw() const {
    return this->yaw;
}

float Camera::GetPitch() const {
    return this->pitch;
}

void Camera::SetFov(float fov) {
    if (fov <= minFov) throw std::invalid_argument("fov must be greater than minFov");

    if (fov > maxFov) throw std::invalid_argument("fov must be lower than maxFov");

    this->fov = fov;
}

void Camera::SetRadius(float radius) {
    if (radius < minRadius) throw std::invalid_argument("radius must be greater than minRadius");

    if (radius > maxRadius) throw std::invalid_argument("radius must be lower than maxRadius");

    this->radius = radius;
}

void Camera::SetPitch(float pitch) {
    if (pitch < minPitch) throw std::invalid_argument("pitch must be greater than minPitch");

    if (pitch > maxPitch) throw std::invalid_argument("pitch must be lower than maxPitch");

    this->pitch = pitch;
}

void Camera::SetYaw(float yaw) {
    this->yaw = yaw;
}
