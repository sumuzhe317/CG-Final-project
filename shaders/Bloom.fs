// Blur Shading Fragment Shader (Gauss Blur)
#version 330 core

out vec4 FragColor;
// 输入纹理坐标, 用于定位当前TexCoord周围的纹理
in vec2 TexCoord;
// image为输入的纹理, horizontal决定进行水平模糊还是垂直模糊
uniform sampler2D image;
uniform bool horizontal;
// 高斯模糊是一个连续函数的计算, 在离散条件下可以选定一组sigma和半径r得到相应的权重系数, 此时半径为5
uniform float weight[5] = float[] (0.2270270270, 0.1945945946, 0.1216216216, 0.0540540541, 0.0162162162);

void main()
{
    // 获得像素间隔
    vec2 tex_offset = 1.0 / textureSize(image, 0);
    // TexCoord对应的原点
    vec3 result = texture(image, TexCoord).rgb * weight[0];
    // 水平模糊
    if(horizontal)
    {
        // 计算前后8点
        for(int i = 1; i < 5; ++i)
        {
        result += texture(image, TexCoord + vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
        result += texture(image, TexCoord - vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
        }
    }
    // 垂直模糊
    else
    {
        for(int i = 1; i < 5; ++i)
        {
            result += texture(image, TexCoord + vec2(0.0, tex_offset.y * i)).rgb * weight[i];
            result += texture(image, TexCoord - vec2(0.0, tex_offset.y * i)).rgb * weight[i];
        }
    }
    FragColor = vec4(result, 1.0);
}