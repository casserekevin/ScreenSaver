#version 460

in vec2 vertexTextureCoordinate;
in vec4 vertexColor;

out vec4 fColorOut;

uniform sampler2D texture0;

void main(){
	fColorOut = texture(texture0, vertexTextureCoordinate) * vertexColor;
}
