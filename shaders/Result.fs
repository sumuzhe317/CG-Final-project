// Result Shading Fragment Shader (Texture Mix)
#version 330 core

out vec4 FragColor;

in vec2 TexCoord;

// texture samplers
uniform sampler2D screenTexture;
uniform sampler2D BloomTexture;
// uniform float exposure;

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	//FragColor = texture(screenTexture,TexCoord)+vec4(1.0,1.0,1.0,1.0);
	FragColor = texture(screenTexture,TexCoord) + texture(BloomTexture,TexCoord);
	//------------------------------------------------------------------------------
    // const float gamma = 2.2;
    // vec3 hdrColor = texture(screenTexture, TexCoord).rgb;      
    // vec3 bloomColor = texture(BloomTexture, TexCoord).rgb;
    // hdrColor += bloomColor; // additive blending
    // // tone mapping
    // vec3 result = vec3(1.0) - exp(-hdrColor * exposure);
    // // also gamma correct while we're at it       
    // result = pow(result, vec3(1.0 / gamma));
    // FragColor = vec4(result, 1.0f);
}