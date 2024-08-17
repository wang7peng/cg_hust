#include <glad/glad.h>
#include <glfw3.h>
#include <stdio.h>
#include <string.h>

const size_t SCR_WIDTH = 640;
const size_t SCR_HEIGHT = 500;

const char* File_GLSL_shader = "../vertex_shader.glsl";
const char* File_GLSL_fragment = "../fragment_shader.glsl";

// 功能: 将源码文件内容按格式读入到字符串中, 包括行尾的 \n
void readFile(const char* fileName, char* content);

// point
const float triangle_vertex[][3] = {
    {-0.5f, -0.5f, 0.0f},
    {0.5f, -0.5f, 0.0f},
    {0.0f, 0.5f, 0.0f},
};

int main(int argc, char* argv[]) {
  if (GLFW_FALSE == glfwInit()) {
    printf("GLFW environment have problem!\n");
    return -1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  auto GLFWwindow* win =
      glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "triangle", NULL, NULL);
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

  glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

  GLuint vertex_buffer_object;
  glGenBuffers(1, &vertex_buffer_object);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);

  GLuint vertex_array_object;
  glGenVertexArrays(1, &vertex_array_object);
  glBindVertexArray(vertex_array_object);

  glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertex), triangle_vertex,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  char content_vertex[500] = "";
  char content_fragment[500] = "";
  int success = 0;
  char info_log[512];

  // 常量指针
  const char* source = content_vertex;
  readFile(File_GLSL_shader, content_vertex);

  int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &source, NULL);
  glCompileShader(vertex_shader);

  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
    printf("ERROR: shader [vertex] compilation failed: %s\n", info_log);
  }

  source = content_fragment;
  readFile(File_GLSL_fragment, content_fragment);
  int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &source, NULL);
  glCompileShader(fragment_shader);

  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
    printf("ERROR: shader [Fragment] compilation failed: %s\n", info_log);
  }

  int shader_program = glCreateProgram();
  glAttachShader(shader_program, vertex_shader);
  glAttachShader(shader_program, fragment_shader);
  glLinkProgram(shader_program);

  glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shader_program, 512, NULL, info_log);
    printf("ERROR: shader [program] Linking failed: %s\n", info_log);
  }

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);

  while (!glfwWindowShouldClose(win)) {
    glClearColor(0.52f, 0.18f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shader_program);
    glBindVertexArray(vertex_array_object);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

    glfwSwapBuffers(win);
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &vertex_array_object);
  glDeleteBuffers(1, &vertex_buffer_object);

  glfwTerminate();  // free

  return 0;
}

void readFile(const char* fileName, char* content) {
  int lenLine = 0;
  char dataLine[180];
  FILE* fp = NULL;

  if ((fp = fopen(fileName, "r")) == NULL) {
    printf("can't find source file: %s.\n", fileName);
  } else {
    printf("start get the source of %s\n", fileName);
  }

  while (fgets(dataLine, 180, fp)) {
    lenLine = strlen(dataLine);

    if ('\n' == dataLine[lenLine - 1]) {
      dataLine[lenLine] = '\0';  // 每行的 \n 都要保留下来
    }
    // 最后一行可能没有 \n, 上面的判断可能顾及不到
    if (dataLine[0] == '}') {
      dataLine[lenLine++] = '\0';
    }

    if (dataLine[0] == '/' || lenLine == 1) {
      continue;
    }
    strcat(content, dataLine);
  }

  printf("get ok, content: \n%s", content);
  fclose(fp);
}
