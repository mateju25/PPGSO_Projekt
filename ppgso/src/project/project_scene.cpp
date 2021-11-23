// Example gl_scene
// - Introduces the concept of a dynamic scene of objects
// - Uses abstract object interface for Update and Render steps
// - Creates a simple game scene with Player, Asteroid and Space objects
// - Contains a generator object that does not render but adds Asteroids to the scene
// - Some objects use shared resources and all object deallocations are handled automatically
// - Controls: LEFT, RIGHT, "R" to reset, SPACE to fire

#include <iostream>
#include <map>
#include <list>

#include <ppgso/ppgso.h>
#include "camera.h"
#include "scene.h"
#include "terrain.h"

const unsigned int SIZE = 1000;

/*!
 * Custom windows for our simple game
 */
class SceneWindow : public ppgso::Window {
private:
    Scene scene;

    /*!
     * Reset and initialize the game scene
     * Creating unique smart pointers to objects that are stored in the scene object list
     */
    void initScene() {
        scene.objects.clear();

        // Create a camera
        auto camera = std::make_unique<Camera>();
        scene.camera = move(camera);

        // Create terrain
        auto terrain = std::make_unique<Terrain>();
        scene.objects.push_back(move(terrain));
    }

public:

    glm::vec2 mouse_delta;

    /*!
     * Construct custom game window
     */
    SceneWindow() : Window{"PODMORSKY SVET", SIZE, SIZE} {
        //hideCursor();
        glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);

        // Initialize OpenGL state
        // Enable Z-buffer
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        // Enable polygon culling
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glCullFace(GL_BACK);

        initScene();
    }

    /*!
     * Handles pressed key when the window is focused
     * @param key Key code of the key being pressed/released
     * @param scanCode Scan code of the key being pressed/released
     * @param action Action indicating the key state change
     * @param mods Additional modifiers to consider
     */
    void onKey(int key, int scanCode, int action, int mods) override {
        scene.keyboard[key] = action;

        // Reset
        if (key == GLFW_KEY_R && action == GLFW_PRESS) {
            initScene();
        }

        if (key == GLFW_KEY_W) {
            scene.camera->moveForward();
        }
        if (key == GLFW_KEY_S) {
            scene.camera->moveBackward();
        }
        if (key == GLFW_KEY_A) {
            scene.camera->strafeLeft();
        }
        if (key == GLFW_KEY_D) {
            scene.camera->strafeRight();
        }
        if (key == GLFW_KEY_SPACE) {
            scene.camera->moveUp();
        }
        if (key == GLFW_KEY_RIGHT_SHIFT) {
            scene.camera->moveDown();
        }
//

//
//
//        if (key == GLFW_KEY_S) {
//            scene.camera->position.y -= 0.5;
//        }
//
//        glm::vec2 mouse_delta = {0, 0};
//
//        if (key == GLFW_KEY_UP) {
//            mouse_delta.y = 0.1;
//        }
//
//        if (key == GLFW_KEY_DOWN) {
//            mouse_delta.y -= 0.1;
//        }
//
//        if (key == GLFW_KEY_RIGHT) {
//            mouse_delta.x = 0.1;
//        }
//
//        if (key == GLFW_KEY_LEFT) {
//            mouse_delta.x -= 0.1;
//        }

        scene.camera->updateRotation(mouse_delta);
    }

    /*!
     * Handle cursor position changes
     * @param cursorX Mouse horizontal position in window coordinates
     * @param cursorY Mouse vertical position in window coordinates
     */
//    void onCursorPos(double cursorX, double cursorY) override {
//        mouse_delta = {scene.cursor.x - cursorX, scene.cursor.y - cursorY};
//
//        scene.camera->updateRotation(mouse_delta);
//
//        scene.cursor.x = cursorX;
//        scene.cursor.y = cursorY;
//    }

    /*!
     * Handle cursor buttons
     * @param button Mouse button being manipulated
     * @param action Mouse bu
     * @param mods
     */
    void onMouseButton(int button, int action, int mods) override {
        if (button == GLFW_MOUSE_BUTTON_LEFT) {
            scene.cursor.left = action == GLFW_PRESS;

            if (scene.cursor.left) {
                // Convert pixel coordinates to Screen coordinates
                double u = (scene.cursor.x / width - 0.5f) * 2.0f;
                double v = -(scene.cursor.y / height - 0.5f) * 2.0f;

                // Get mouse pick vector in world coordinates
                auto direction = scene.camera->cast(u, v);
                auto position = scene.camera->position;

                // Get all objects in scene intersected by ray
                auto picked = scene.intersect(position, direction);

                // Go through all objects that have been picked
                for (auto &obj: picked) {
                    // Pass on the click event
                    obj->onClick(scene);
                }
            }
        }
        if (button == GLFW_MOUSE_BUTTON_RIGHT) {
            scene.cursor.right = action == GLFW_PRESS;
        }
    }

    /*!
     * Window update implementation that will be called automatically from pollEvents
     */
    void onIdle() override {
        // Track time
        static auto time = (float) glfwGetTime();

        // Compute time delta
        float dt = (float) glfwGetTime() - time;

        // Set gray background
        glClearColor(.5f, .5f, .5f, 0);
        // Clear depth and color buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//        scene.camera->rotation.z += dt/100;

        // Update and render all objects
//        scene.camera->position.x -= sin(dt);
        scene.update(dt);
        scene.render();
    }
};

int main() {
    // Initialize our window
    SceneWindow window;

    // Main execution loop
    while (window.pollEvents()) {}

    return EXIT_SUCCESS;
}
