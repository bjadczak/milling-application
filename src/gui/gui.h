//
// Created by Bartosz Jadczak on 08/10/2024.
//

#ifndef GUI_H
#define GUI_H

#include "../app/AppContext.h"
#include "../renderContext/renderContext.h"

class Gui {
    AppContext &appContext;
    RenderContext &renderContext;

    bool show_fps_window = false;

    const int rightWindowWidth = 400;
    std::vector<float> frames;
    void showFPSWindow();
    void showOptionWindow();
    void showMillingOptions();
    void showScene() const;
    void showCameraModeDropDown() const;
    void loadGCode() const;

public:
    explicit Gui(AppContext &appContext, RenderContext &renderContext);

    static void postRender();

    static void preRender();

    void draw();



    void updateCameraPos(ImVec2 canvas_sz) const;

    ~Gui();
};




#endif //GUI_H
