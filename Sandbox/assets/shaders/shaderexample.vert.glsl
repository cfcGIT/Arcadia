#version 450

#pragma shader_stage(vertex) // To be known as vertex when compiling with glslc. This is because it has .glsl ext, with .vert ext this isn't necessary

// We're going to reference this binding in the descriptor layout
layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
} ubo;

// Vertex shader inputs can specify the attribute index (location = attribute index) that the particular input uses
// It is important to know that some types, like dvec3 64 bit vectors, use multiple slots. That means that the index after it must be at least 2 higher. More info: https://www.khronos.org/opengl/wiki/Layout_Qualifier_(GLSL)
layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 fragTexCoord;

// The main function is invoked for every vertex
void main()
{
    // gl_VertexIndex contains the index of the current vertex. This is usually an index into the vertex buffer
    gl_Position = ubo.proj * ubo.view * ubo.model * vec4(inPosition, 1.0);
    // gl_Position functions as the output
    fragColor = inColor;
    fragTexCoord = inTexCoord;
}