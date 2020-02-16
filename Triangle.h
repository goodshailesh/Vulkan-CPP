#pragma once
#include <iostream>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string.h>
// Commenting it out since "#include <optional>"" is still not suported in this version of GCC - missing
// libstdc++ which is part of C++2a - https://en.cppreference.com/w/cpp/compiler_support
//#include <optional>
#include <experimental/optional>

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif


const int WIDTH = 2048;
const int HEIGHT = 1152;
const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};
struct QueueFamilyIndices {
    std::experimental::optional<uint32_t> graphicsFamily;
    std::experimental::optional<uint32_t> presentFamily;
    bool isComplete() {
        // Commenting it out since "#include <optional>" is still not suported in this version of GCC - missing        // libstdc++ which is part of C++2a - https://en.cppreference.com/w/cpp/compiler_support
        // https://stackoverflow.com/questions/4600295/what-is-the-meaning-of-operator-bool-const
        //return graphicsFamily.has_value() && presentFamily.has_value();
        return (graphicsFamily && presentFamily) ;
    }
};


class HelloTriangleApplication {
    public:
        void run() {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }
    private:
        GLFWwindow* window;
        VkInstance instance;
        VkDebugUtilsMessengerEXT debugMessenger;
        VkSurfaceKHR surface;
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        VkDevice device;
        VkQueue graphicsQueue;
        VkQueue presentQueue;


        void initWindow() {
            glfwInit();

            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
            glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

            window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
        }

        void initVulkan();

        void mainLoop();

        void cleanup();

        void createInstance();

        void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

        void setupDebugMessenger();

        void createSurface();

        void pickPhysicalDevice();

        void createLogicalDevice();

        bool isDeviceSuitable(VkPhysicalDevice device);

        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

        std::vector<const char*> getRequiredExtensions();

        bool checkValidationLayerSupport() ;


        VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);

        void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

};


// NON Class member
static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
    std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
    return VK_FALSE;
}