#version 330 core

in vec4 vertexColor;
in vec2 texCoord;

uniform sampler2D tex;
uniform sampler2D tex2;

out vec4 fragColor;

void main()
{   
    fragColor = texture(tex, texCoord) * 0.8  + texture(tex2, texCoord) * 0.2;
} 