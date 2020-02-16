#include <iostream>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

const int WIDTH = 2048;
const int HEIGHT = 1152;

class HelloTriangleApplication {
    public:
        void run();
    private:
        GLFWwindow* window;
        VkInstance instance;

        void initWindow();
        void initVulkan();
        void mainLoop();
        void createInstance();
        void cleanup();
};