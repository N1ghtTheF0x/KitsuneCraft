#ifndef __N1GHTTHEF0X_KITSUNECRAFT_CAMERA_HPP
#define __N1GHTTHEF0X_KITSUNECRAFT_CAMERA_HPP

#include <glm.hpp>

namespace N1ghtTheF0x::KitsuneCraft
{
    class Camera
    {
    private:
        glm::vec3 _position;
        glm::vec3 _target;
        glm::vec3 _up;

        float _yaw;
        float _pitch;
    public:
        Camera();
        Camera(glm::vec3 position);

        void setPosition(glm::vec3 position);
        glm::vec3 position() const;
        void setTarget(glm::vec3 target);
        void setTarget(float yaw,float pitch);
        glm::vec3 target() const;
        void setUp(glm::vec3 up);
        glm::vec3 up() const;
        void setYaw(float yaw);
        float yaw() const;
        void setPitch(float pitch);
        float pitch() const;

        glm::mat4 view() const;
    };
}

#endif