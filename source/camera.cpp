#include "camera.hpp"

#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

namespace N1ghtTheF0x::KitsuneCraft
{
    Camera::Camera(): Camera({0,0,3})
    {
        
    }
    Camera::Camera(glm::vec3 position): _position(position), _target({0,0,-1}), _up({0,1,0})
    {
        
    }
    void Camera::setPosition(glm::vec3 position)
    {
        _position = position;
    }
    void Camera::setTarget(glm::vec3 target)
    {
        _target = target;
    }
    void Camera::setUp(glm::vec3 up)
    {
        _up = up;
    }
    void Camera::setYaw(float yaw)
    {
        _yaw = yaw;
        setTarget(_yaw,_pitch);
    }
    void Camera::setPitch(float pitch)
    {
        _pitch = pitch;
        if(_pitch > 89.0f)
            _pitch = 89.0f;
        if(_pitch < -89.0f)
            _pitch = -89.0f;
        setTarget(_yaw,_pitch);
    }
    glm::vec3 Camera::position() const
    {
        return _position;
    }
    glm::vec3 Camera::target() const
    {
        return _target;
    }
    glm::vec3 Camera::up() const
    {
        return _up;
    }
    float Camera::yaw() const
    {
        return _yaw;
    }
    float Camera::pitch() const
    {
        return _pitch;
    }
    glm::mat4 Camera::view() const
    {
        return glm::lookAt(_position,_position + _target,_up);
    }
    void Camera::setTarget(float yaw,float pitch)
    {
        glm::vec3 d;
        d.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        d.y = sin(glm::radians(pitch));
        d.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        _target = d;
    }
}