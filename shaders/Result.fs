// Result Shading Fragment Shader (Texture Mix)
#version 330 core

out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D screenTexture;
uniform sampler2D BlurTexture;

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	//FragColor = texture(screenTexture,TexCoord)+vec4(1.0,1.0,1.0,1.0);
	FragColor = texture(screenTexture,TexCoord) + texture(BlurTexture,TexCoord);
}