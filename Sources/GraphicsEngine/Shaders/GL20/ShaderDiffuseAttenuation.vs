#version 130

const int MAX_LIGHT_COUNT = 10;

// Shader parameters
uniform mat4 matrixWorldViewProjT;
uniform vec4 timeT;
uniform mat4 lightSpaceMatrix[MAX_LIGHT_COUNT];
uniform vec4 lightsCount;

// Vertex structure
attribute vec3 position;
attribute vec4 color;
attribute vec3 normal;

// local variables (between shaders)
varying vec3 localPosition;
varying vec3 localNormal;
varying vec4 FragPosLightSpace[MAX_LIGHT_COUNT];


void main()
{
        gl_Position		=   (timeT + vec4(position, 1.0)) * matrixWorldViewProjT;
	gl_FrontColor	= color;
	localPosition	= position + timeT.xyz;
	localNormal		= normal;

        for (int i = 0; float(i) < lightsCount.x; i++)
            FragPosLightSpace[i] =  vec4(localPosition, 1.0) * lightSpaceMatrix[i];
}
