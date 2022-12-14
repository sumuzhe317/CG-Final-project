#pragma once
#include "glad/glad.h"
#define GLCheckError() (glGetError() == GL_NO_ERROR)
#define ZERO_MEM(a) memset(a,0,sizeof(a))