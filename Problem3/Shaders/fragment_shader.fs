#version 400 core

in vec2 TexCoords;
in vec3 ourCol;

out vec4 color;

uniform sampler2D text1;
uniform int usetext;

void main(){
	if(usetext==0){
		color = texture(text1, TexCoords) * vec4(ourCol,1.0);
	}
	else{
		color = vec4(ourCol,1.0);
	}
}
