/*

    Copyright 2011 Etay Meiri

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef PARTICLE_SYSTEM_H
#define	PARTICLE_SYSTEM_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "ps_update_technique.h"
#include "random_texture.h"
using namespace glm;

class ParticleSystem
{
public:
    ParticleSystem(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);

    ~ParticleSystem();

    bool InitParticleSystem(const vec3& Pos);

    void Render(int DeltaTimeMillis, const vec3& CameraPos);



    void UpdateParticles(int DeltaTimeMillis);
    void RenderParticles( const vec3& CameraPos);

    bool m_isFirst;
    unsigned int m_currVB;
    unsigned int m_currTFB;
    GLuint m_particleBuffer[2];
    GLuint m_transformFeedback[2];
    PSUpdateTechnique m_updateTechnique;
    int m_time;
};

#endif	/* PARTICLE_SYSTEM_H */
