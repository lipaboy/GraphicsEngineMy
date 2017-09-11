#version 110

// Shader parameters
uniform mat4 matrixWorldViewProjT;
uniform vec4 timeT;

// Vertex structure
attribute vec3 position;
attribute vec4 color;
attribute vec3 normal;

varying vec3 localPosition;
varying vec3 localNormal;


void main()
{
	gl_Position		= (timeT + vec4(position, 1.0)) * matrixWorldViewProjT;
	gl_FrontColor	= color;
	localPosition	= position + timeT.xyz;
	localNormal		= normal;
}