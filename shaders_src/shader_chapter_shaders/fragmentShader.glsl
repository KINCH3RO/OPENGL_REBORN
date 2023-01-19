#version 330 core
out vec4 FragColor;
in vec3 inFragColor;
void main() {
	FragColor = vec4(inFragColor, 1.0);
}
