//
// Created by Bartosz Jadczak on 09/10/2024.
//

#include "scene.h"

Scene::Scene(AppContext &appContext, RenderContext &renderContext) :
    appContext(appContext),
    renderContext(renderContext)
{
    grid = std::make_unique<GridModule>(appContext);
    millingShader = std::make_unique<ShaderProgram>(
        "res/shaders/millingObject/millingObject.vert",
        "res/shaders/millingObject/millingObject.frag",
        "res/shaders/millingObject/millingObject.geom"
        );
    basicShader = std::make_unique<ShaderProgram>(
    "res/shaders/basic/basic.vert",
    "res/shaders/basic/basic.frag"
    );

    appContext.millingObject = std::make_unique<MillingObject>();

    appContext.light = std::make_unique<PointLight>();
    appContext.light->position = {0.0f , 0.0f, 0.25f};

    appContext.baseDimensions = {150, 50, 150};
    appContext.baseResolution = {1500, 1500};

    appContext.heightMapSize = glm::vec2(1000);
    std::vector<float> t(appContext.heightMapSize.x*appContext.heightMapSize.y);
    for(int i = 0; i < appContext.heightMapSize.x; i++)
        for(int j = 0; j < appContext.heightMapSize.y; j++)
            t[i*appContext.heightMapSize.y + j] = (40 + 10*sin(0.025*i) + 10*cos(0.01 * j))/50;
    appContext.heightMap = std::make_unique<Texture>(appContext.heightMapSize.x, appContext.heightMapSize.y, 1, GL_RED, GL_RED, GL_FLOAT, GL_TEXTURE_2D,
                                                     nullptr);
    appContext.heightMap->update2D(t.data());
}

void Scene::update() {
}

void Scene::render() {
    appContext.frameBufferManager->bind();

    millingShader->Activate();
    millingShader->setUniform("model", glm::mat4(1.0f));
    millingShader->setUniform("viewPos", appContext.camera->getViewPosition());
    millingShader->setUniform("view", appContext.camera->getViewMatrix());
    millingShader->setUniform("projection", appContext.camera->getProjectionMatrix());
    millingShader->setUniform("material.hasTexture", false);
    millingShader->setUniform("material.albedo", glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
    millingShader->setUniform("material.shininess", 256.f);
    millingShader->setUniform("uGridSize", appContext.baseResolution);
    millingShader->setUniform("uBaseSize", glm::vec2(appContext.baseDimensions.x,appContext.baseDimensions.z));
    millingShader->setUniform("uHeightScale", appContext.baseDimensions.y);
    appContext.heightMap->bind(1);
    millingShader->setUniform("uHeightMap", 1);
    appContext.light->setupPointLight(*millingShader);
    appContext.millingObject->render(appContext.baseResolution.x * appContext.baseResolution.y);

    if(appContext.pathObject != nullptr) {
        basicShader->Activate();
        basicShader->setUniform("model", glm::mat4(1.0f));
        basicShader->setUniform("projection", appContext.camera->getProjectionMatrix());
        basicShader->setUniform("view", appContext.camera->getViewMatrix());
        appContext.pathObject->render();
    }

    grid->draw();
    appContext.frameBufferManager->unbind();
}

void Scene::destroy() {
    grid->destroy();
    millingShader->Delete();
}
