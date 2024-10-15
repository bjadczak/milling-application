//
// Created by Bartosz Jadczak on 08/10/2024.
//

#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#include <imgui.h>
#include <memory>
#include <glm/glm.hpp>
#include <stdexcept>
#include "../camera/baseCamera.h"
#include "../camera/CameraAnchorFree.h"
#include "../camera/CameraGameLike.h"
#include "../framebufferManager/FrameBufferManager.h"
#include "../millingObjects/millingPlate.h"
#include "../light/PointLight.h"
#include "../millingObjects/pathObject.h"
#include "../millingObjects/mill.h"

struct AppContext {
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    std::unique_ptr<BaseCamera> camera;
    std::unique_ptr<FrameBufferManager> frameBufferManager;

    std::unique_ptr<MillingPlate> millingObject;
    std::unique_ptr<Mill> mill;
    std::unique_ptr<PathObject> pathObject;

    //glm::vec2 heightMapSize;
    glm::vec<2, int> baseResolution;
    glm::vec3 baseDimensions;

    std::unique_ptr<PointLight> light;

    CameraType cameraType;

    bool guiFocus = true;

    float cameraSensitivity = 0.8f;

    /*
     *  Window resizing callback used in inputManager
     */
    void glfw_window_resize(const unsigned int width, const unsigned int height) const {
        camera->resize(width, height); // NOLINT(*-narrowing-conversions)
        frameBufferManager->create_buffers(camera->screenWidth, camera->screenHeight);
    }

    /*
     *  Allocation of complex attribute Camera
     */
    void allocateCamera(const CameraType setType)
    {
        cameraType = setType;
        switch(setType)
        {
            case CameraType::GAMELIKE:
                if(camera != nullptr)
                    camera.reset();
            camera = std::make_unique<CameraGameLike>(1920, 1080, CameraMode::FREE, glm::vec3(0.0f, 60.0f, 160.0f), glm::vec3(0.f), glm::vec3(-glm::pi<float>() / 4, 0, 0));
            break;
            case CameraType::FREEANCHOR:
                if(camera != nullptr)
                    camera.reset();
            camera = std::make_unique<CameraAnchorFree>(1920, 1080, CameraMode::ANCHOR, glm::vec3(0.0f, 60.0f, 160.0f), glm::vec3(0.f), glm::vec3(-glm::pi<float>() / 4, 0, 0));
            break;
            default:
                throw std::invalid_argument("Invalid camera type");

        }
    }

    void initFrameBufferManager()
    {
        frameBufferManager = std::make_unique<FrameBufferManager>();
        frameBufferManager->create_buffers(camera->screenWidth, camera->screenHeight);
    }

    AppContext()
    {
        allocateCamera(CameraType::GAMELIKE);
    }
};

#endif //APPCONTEXT_H