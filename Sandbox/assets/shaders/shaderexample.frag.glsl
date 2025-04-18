#version 450

#pragma shader_stage(fragment) // To be known as fragment when compiling with glslc. This is because it has .glsl ext, with .frag ext this isn't necessary

layout(location = 0) in vec3 fragColor; // same location as out of vertex shader
layout(location = 1) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor; // layout(location = 0) modifier specifies the index of the framebuffer

layout(binding = 1) uniform sampler2D texSampler;

// The main function is called for every fragment
void main()
{
    // The values for fragColor will be automatically interpolated for the fragments between the three vertices, resulting in a smooth gradient
    //outColor = vec4(fragColor, 1.0); // The color is written to this outColor variable that is linked to the first (and only) framebuffer at index 0
    //outColor = vec4(fragTexCoord, 0.0, 1.0);

    outColor = texture(texSampler, fragTexCoord);
    //outColor = texture(texSampler, fragTexCoord * 2.0);
    //outColor = vec4(fragColor * texture(texSampler, fragTexCoord).rgb, 1.0);
}