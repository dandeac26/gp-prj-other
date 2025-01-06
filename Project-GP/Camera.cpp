#include "Camera.hpp"

namespace gps {

    Camera::Camera(glm::vec3 cameraPosition, glm::vec3 cameraTarget, glm::vec3 cameraUp) {
        //this->cameraPosition = cameraPosition;
        //this->cameraTarget = cameraTarget;
        this->cameraUpDirection = cameraUp;

        this->cameraPosition = cameraPosition;
        this->cameraTarget = cameraTarget;
        this->cameraFrontDirection = glm::normalize(cameraPosition - cameraTarget); //cameraDirection
        this->cameraRightDirection = glm::normalize(glm::cross(cameraUpDirection, cameraFrontDirection));
        //this->cameraUpDirection = glm::cross(cameraFrontDirection, cameraRightDirection);

    }

    glm::mat4 Camera::getViewMatrix() {
        // create the view matrix using glm::lookAt function
        return glm::lookAt(cameraPosition, cameraPosition + cameraFrontDirection, cameraUpDirection);
    }
    //update the camera internal parameters following a camera move event
    void Camera::move(MOVE_DIRECTION direction, float speed) {
        // get camera's right vector
        glm::vec3 cameraRight = glm::normalize(glm::cross(cameraUpDirection, cameraTarget - cameraPosition));

        // move camera
        if (direction == MOVE_FORWARD) {
            cameraPosition += cameraFrontDirection * speed;
        }
        else if (direction == MOVE_BACKWARD) {
            cameraPosition -= cameraFrontDirection * speed;
        }
        else if (direction == MOVE_LEFT) {
            cameraPosition -= cameraRightDirection * speed;
        }
        else if (direction == MOVE_RIGHT) {
            cameraPosition += cameraRightDirection * speed;
        }
    }
    glm::vec3 Camera::getCameraTarget()
    {
        return cameraTarget;
    }

    void Camera::scenePreview(float angle) {
        // set the camera
        this->cameraPosition = glm::vec3(-9.0, 20.0, 48.0);

        // rotate with specific angle around Y axis
        glm::mat4 r = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0, 1, 0));

        // compute the new position of the camera 
        // previous position * rotation matrix
        this->cameraPosition = glm::vec4(r * glm::vec4(this->cameraPosition, 1));
        this->cameraFrontDirection = glm::normalize(cameraTarget - cameraPosition);
        cameraRightDirection = glm::normalize(glm::cross(cameraFrontDirection, glm::vec3(0.0f, 1.0f, 0.0f)));
    }

    void Camera::rotate(float pitch, float yaw) {
        // rotate camera
        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

        cameraFrontDirection = glm::normalize(front);
        //cameraTarget = cameraPosition + cameraFrontDirection;
    }
   
    glm::vec3 Camera::getCameraFrontDirection()
    {
        return this->cameraFrontDirection;

    }
    glm::vec3 Camera::getCameraPosition()
    {
        return this->cameraPosition;
    }
}