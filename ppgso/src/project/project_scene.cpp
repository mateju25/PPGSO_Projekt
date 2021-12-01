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
#include "fish_spawn.h"
#include "fish.h"
#include "decorationPiller.h"

const unsigned int SIZE = 900;

/*!
 * Custom windows for our simple game
 */
class SceneWindow : public ppgso::Window {
private:
    float time;

    Scene scene;
    /*!
     * Reset and initialize the game scene
     * Creating unique smart pointers to objects that are stored in the scene object list
     */
    void initScene() {
        scene.objects.clear();

        scene.lightDirection = {0.1 , 1, 0.1};


        // Create submarine
        auto submarine = std::make_unique<Submarine>(scene);
        scene.objects.push_back(move(submarine));


        // Create a camera
        auto camera = std::make_unique<Camera>();
        scene.camera = move(camera);

        // Create terrain
        glm::vec3 position = {-322.116,-19,-148.765};
        glm::vec3 rotation = {3*ppgso::PI/2, 4.31239, 0};
        glm::vec3 scale = {10,10,10};
        auto piller1 = std::make_unique<DecorationPiller>("projekt/pillar.obj", position, rotation, scale);
        scene.objects.push_back(move(piller1));

        position = {-311.406,-19,-179.196};
        auto piller2 = std::make_unique<DecorationPiller>("projekt/pillar.obj", position, rotation, scale);
        scene.objects.push_back(move(piller2));

        position = {-316.716,24,-164};
        auto piller3 = std::make_unique<DecorationPiller>("projekt/pillar_top.obj", position, rotation, scale);
        scene.objects.push_back(move(piller3));

        position = {-174.406,-17.5,-89.4885};
        auto piller4 = std::make_unique<DecorationPiller>("projekt/pillar.obj", position, rotation, scale);
        scene.objects.push_back(move(piller4));

        position = {-250,-17.5,-55.865};
        auto piller5 = std::make_unique<DecorationPiller>("projekt/pillar.obj", position, rotation, scale);
        scene.objects.push_back(move(piller5));

        position = {-250,-17.5,-218.865};
        auto piller6 = std::make_unique<DecorationPiller>("projekt/pillar_broken.obj", position, rotation, scale);
        scene.objects.push_back(move(piller6));

        position = {-300,-17.5,-80.4};
        auto piller7 = std::make_unique<DecorationPiller>("projekt/pillar.obj", position, rotation, scale);
        scene.objects.push_back(move(piller7));

        position = {-165,-17.5,-106.631};
        auto piller8= std::make_unique<DecorationPiller>("projekt/pillar_broken.obj", position, rotation, scale);
        scene.objects.push_back(move(piller8));

        position = {-175,-17.5,-188};
        auto piller9= std::make_unique<DecorationPiller>("projekt/pillar.obj", position, rotation, scale);
        scene.objects.push_back(move(piller9));

        auto terrain1 = std::make_unique<Terrain>("projekt/terrain_01.obj");
        scene.objects.push_back(move(terrain1));

        auto terrain2 = std::make_unique<Terrain>("projekt/cave.obj");
        scene.objects.push_back(move(terrain2));

        auto terrain3 = std::make_unique<Terrain>("projekt/cave_mask.obj");
        scene.objects.push_back(move(terrain3));

        auto terrain4 = std::make_unique<Terrain>("projekt/walls.obj");
        scene.objects.push_back(move(terrain4));

        position = {-381.366,7.5,100.969};
        auto volcano1 = std::make_unique<Volcano>(false, position);
        scene.objects.push_back(move(volcano1));

        position = {-394.248,3.5,70.635};
        auto volcano2 = std::make_unique<Volcano>(true, position);
        scene.objects.push_back(move(volcano2));

        std::vector<glm::vec3> path_points = {
                {-240.98, -25, -137.31},
                {-240.98, 50, -137.31},
                {-103.918, 37 , -65.0874},
                {50, 0, -50},
                {50, 50, 50},
                {50, 50, 0},
                {150, 50, 0},
                {150, 0, 0}
        };

        auto fishfish = std::make_unique<fish_spawn>(path_points, 7, 40);
        scene.objects.push_back(move(fishfish));

        // Load images
        std::ifstream image_stream("HeightMap_main.png", std::ios::binary);
        std::vector<char> height_map_main_buffer(static_cast<std::size_t>(3840 * 2600));
        image_stream.read(height_map_main_buffer.data(), static_cast<std::streamsize>(height_map_main_buffer.size()));
        image_stream.close();

        std::cout << height_map_main_buffer.size() << std::endl;
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

        if (key == GLFW_KEY_1) {
            scene.camera->mode = Camera::FOLLOW;
        }

        if (key == GLFW_KEY_2) {
            scene.camera->mode = Camera::STATIONARY;
            scene.camera->position = {-174.1 , 24.2745, -39.553};
            scene.camera->submarinePos = {-222.458 , -10.9873, -110.905};
        }

        if (key == GLFW_KEY_3) {
            scene.camera->mode = Camera::STATIONARY;
            scene.camera->position = {-336.465, 23.604, 83.9555};
            scene.camera->submarinePos = {-371.641, 8.6871, 85.7647};
        }

        if (key == GLFW_KEY_4) {
            scene.camera->mode = Camera::STATIONARY;
            scene.camera->position = {153.992, 37.4656, 49.3311};
            scene.camera->submarinePos = {137.898, 29.6229, 5.43222};
        }

        if (key == GLFW_KEY_RIGHT) {
            if (scene.waterCurrent.x >= -0.02f)
                scene.waterCurrent.x -= 0.005f;
        }
        if (key == GLFW_KEY_LEFT) {
            if (scene.waterCurrent.x <= 0.02f)
                scene.waterCurrent.x += 0.005f;
        }
        if (key == GLFW_KEY_UP) {
            if (scene.waterCurrent.z >= -0.02f)
                scene.waterCurrent.z -= 0.005f;
        }
        if (key == GLFW_KEY_DOWN) {
            if (scene.waterCurrent.z <= 0.02f)
                scene.waterCurrent.z += 0.005f;
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
