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
#include <chrono>
#include <thread>
#include <ppgso/ppgso.h>
#include "camera.h"
#include "scene.h"
#include "terrain.h"
#include "submarine.h"
#include "volcano.h"
#include "walls.h"
#include "cave.h"
#include "caveMask.h"
#include "fish_spawn.h"

const unsigned int SIZE = 900;

/*!
 * Custom windows for our simple game
 */
class SceneWindow : public ppgso::Window {
private:
    float time;

    Scene scene;
    Submarine submarineScene;
    /*!
     * Reset and initialize the game scene
     * Creating unique smart pointers to objects that are stored in the scene object list
     */
    void initScene() {
        scene.objects.clear();

        scene.lightDirection = {0.1 , 1, 0.1};


        // Create submarine
        auto submarine = std::make_unique<Submarine>();
        scene.objects.push_back(move(submarine));


        // Create a camera
        auto camera = std::make_unique<Camera>();
        scene.camera = move(camera);

        // Create terrain
//        auto terrain_test = std::make_unique<Terrain>();
//        scene.objects.push_back(move(terrain_test));
        auto terrain1 = std::make_unique<Terrain>();
        scene.objects.push_back(move(terrain1));

        auto terrain2 = std::make_unique<Walls>();
        scene.objects.push_back(move(terrain2));

        auto terrain3 = std::make_unique<Cave>();
        scene.objects.push_back(move(terrain3));

//        auto terrain4 = std::make_unique<CaveMask>();
//        scene.objects.push_back(move(terrain4));

//        glm::vec3 position = {0,0,0};
//        auto volcano1 = std::make_unique<Volcano>(false, position);
//        scene.objects.push_back(move(volcano1));
//
//        position = {5,0,0};
//        auto volcano2 = std::make_unique<Volcano>(true, position);
//        scene.objects.push_back(move(volcano2));

        std::vector<glm::vec3> path_points = {
                {0, 0, 0},
                {0, 50, 0},
                {0, 50, 50},
                {50, 50, 50},
                {50, 50, 0},
                {150, 50, 0},
                {150, 0, 0}
        };

        auto fishfish = std::make_unique<fish_spawn>(path_points, 1, 10);
        scene.objects.push_back(move(fishfish));
    }

public:
    bool first_mouse = true;

    /*!
     * Construct custom game window
     */
    SceneWindow() : Window{"PODMORSKY SVET", SIZE, SIZE} {
        //hideCursor();
        glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);
//        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

    }

    /*!
     * Handle cursor position changes
     * @param cursorX Mouse horizontal position in window coordinates
     * @param cursorY Mouse vertical position in window coordinates
     */
    void onCursorPos(double cursorX, double cursorY) override {

    }

    /*!
     * Window update implementation that will be called automatically from pollEvents
     */
    void onIdle() override {
//        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        // Compute time delta
        float dt = (float) glfwGetTime() - time;
        time = (float) glfwGetTime();

        // Set gray background
        glClearColor(.5f, .5f, .5f, 0);
        // Clear depth and color buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
