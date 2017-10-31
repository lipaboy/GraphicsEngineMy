#version 130

// Input vertex data, different for all executions of this shader.
//layout(location = 0) in vec3 vertexPosition_modelspace;
attribute vec3 position;

// Values that stay constant for the whole mesh.
uniform mat4 lightSpaceMatrix;

varying vec4 localPosition;

void main(){
    gl_Position =  vec4(position, 1) * lightSpaceMatrix;
    localPosition = gl_Position;
}
