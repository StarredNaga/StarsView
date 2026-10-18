//
// Created by StarredNaga on 17.10.2026.
//

#ifndef STARSVIEW_CAMERA_H
#define STARSVIEW_CAMERA_H


class Camera {

    public:
    Camera(float fov, float radius = 1.f, float yaw = 1.5f, float pitch = 1.5f);

    const float maxFov = 700.f;
    const float minFov = 0.f;

    const float minRadius = 2.f;
    const float maxRadius = 80.f;

    const float minPitch = -1.5f;
    const float maxPitch = 1.5f;

    float GetFov() const;
    float GetRadius() const;
    float GetYaw() const;
    float GetPitch() const;

    void SetFov(float fov);
    void SetRadius(float radius);
    void SetYaw(float yaw);
    void SetPitch(float pitch);

    private:
    float fov;
    float radius;
    float yaw;
    float pitch;
};


#endif //STARSVIEW_CAMERA_H
