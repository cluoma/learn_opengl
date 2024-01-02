#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

const float offset = 1.0 / 300.0;

vec4 kernel_effect(vec2 texCoords)
{
    vec2 offsets[9] = vec2[](
    vec2(-offset,  offset), // top-left
    vec2( 0.0f,    offset), // top-center
    vec2( offset,  offset), // top-right
    vec2(-offset,  0.0f),   // center-left
    vec2( 0.0f,    0.0f),   // center-center
    vec2( offset,  0.0f),   // center-right
    vec2(-offset, -offset), // bottom-left
    vec2( 0.0f,   -offset), // bottom-center
    vec2( offset, -offset)  // bottom-right
    );

    // sharpen
    float kernel[9] = float[](
    -1, -1, -1,
    -1,  9, -1,
    -1, -1, -1
    );
    // blur
//    float kernel[9] = float[](
//    1.0 / 16, 2.0 / 16, 1.0 / 16,
//    2.0 / 16, 4.0 / 16, 2.0 / 16,
//    1.0 / 16, 2.0 / 16, 1.0 / 16
//    );
    // edge detection
//    float kernel[9] = float[](
//    1,  1,  1,
//    1, -8,  1,
//    1,  1,  1
//    );

    vec3 sampleTex[9];
    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(screenTexture, texCoords.st + offsets[i]));
    }
    vec3 col = vec3(0.0);
    for(int i = 0; i < 9; i++)
    col += sampleTex[i] * kernel[i];

    return vec4(col, 1.0);
}

void main()
{
    vec2 tmpTexCoords = TexCoords * vec2(-1.0, 1.0);
    // no post-processing
//    FragColor = texture(screenTexture, tmpTexCoords);

    // grayscale
//    FragColor = texture(screenTexture, tmpTexCoords);
//    float average = 0.2126 * FragColor.r + 0.7152 * FragColor.g + 0.0722 * FragColor.b;
//    FragColor = vec4(average, average, average, 1.0);

    // kernel effect
    FragColor = kernel_effect(tmpTexCoords);
}