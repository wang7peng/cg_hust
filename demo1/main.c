#include <glad/glad.h>
#include <glfw3.h>
#include <stdio.h>

const size_t SCR_WIDTH = 960;
const size_t SCR_HEIGHT = 720;

int main(int argc, char* argv[]) {
  if (GLFW_FALSE == glfwInit()) {
    printf("GLFW environment have problem!\n");
    return -1;
  }

  // glfw version v3.3.8 in 2022
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* win =
      glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "opengl demo1", NULL, NULL);
  if (win == NULL) {
    printf("Failed to create GLFW window\n");
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(win);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    printf("Failed to initialize GLAD\n");
    return -1;
  }

  while (!glfwWindowShouldClose(win)) {
    // work1: change a background color
    glClearColor(0.52f, 0.18f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(win);
    glfwPollEvents();
  }

  glfwTerminate();  // free
  return 0;

  return 0;
}