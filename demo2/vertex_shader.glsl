// 顶点着色器
// Desc: nothing to do
#version 430 core

layout (location = 0) in vec3 aPos;
void main() { // syntax like C
   gl_Position = vec4(aPos, 1.0); 
}
