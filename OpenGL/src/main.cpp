#include "common/common.h"
#include "context/context.h"

void OnFramebufferSizeChange(GLFWwindow* window, int width, int height) {
    auto context = (Context*)glfwGetWindowUserPointer(window);
	context->Reshape(width, height);
    spdlog::info("framebuffer size changed: ({} x {})", width, height);
}

void OnKeyEvent(GLFWwindow* window,
    int key, int scancode, int action, int mods) {
    SPDLOG_INFO("key: {}, scancode: {}, action: {}, mods: {}{}{}",
        key, scancode,
        action == GLFW_PRESS ? "Pressed" :
        action == GLFW_RELEASE ? "Released" :
        action == GLFW_REPEAT ? "Repeat" : "Unknown",
        mods & GLFW_MOD_CONTROL ? "C" : "-",
        mods & GLFW_MOD_SHIFT ? "S" : "-",
        mods & GLFW_MOD_ALT ? "A" : "-");
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void OnCursorPos(GLFWwindow* window, double x, double y) {
    auto context = (Context*)glfwGetWindowUserPointer(window);
    context->MouseMove(x, y);
}

void OnMouseButton(GLFWwindow* window, int button, int action, int modifier) {
    auto context = (Context*)glfwGetWindowUserPointer(window);
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    context->MouseButton(button, action, x, y);
}

int main(int argc, char* argv[])
{
    spdlog::info("Start application");

    if (!glfwInit())
    {
        const char* description;
        glfwGetError(&description);
        spdlog::error("GLFW init failed: {}", description);
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    spdlog::info("GLFW Create Window");
    auto window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, nullptr, nullptr);
    if (!window)
    {
        spdlog::error("GLFW window create failed");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // glad initialize
    if (!gladLoadGL()) {
        spdlog::error("Failed to initialize GLAD");
        return -1;
    }

    spdlog::info("GLAD initialized successfully");
    spdlog::info("OpenGL Version: {}", (const char*)glGetString(GL_VERSION));

    // Init Context
    auto context = Context::Create();
    if (!context)
    {
        spdlog::error("Context init failed");
        glfwTerminate();
        return -1;
    }
    glfwSetWindowUserPointer(window, context.get());

    // Window resize callback
    OnFramebufferSizeChange(window, WINDOW_WIDTH, WINDOW_HEIGHT);
    glfwSetFramebufferSizeCallback(window, OnFramebufferSizeChange);
    glfwSetKeyCallback(window, OnKeyEvent);
    glfwSetCursorPosCallback(window, OnCursorPos );
	glfwSetMouseButtonCallback(window, OnMouseButton);

    spdlog::info("GLFW Main Loop");
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
		context->ProcessInput(window);
        context->Render();
        glfwSwapBuffers(window);
    }

    context.reset();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}