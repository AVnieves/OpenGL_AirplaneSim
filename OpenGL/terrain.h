#pragma once
#include "../source/mesh.h"
#include "../source/texture.h"
#include "../source/shader.h"

class Terrain
{
public:
	Terrain(/*const std::string& shaderFile,const std::string& textureFile*/);
	~Terrain();
	void GenerateTerrain();
	void Draw(Camera& c, Transform& t);
	//void SetShader(std::string& shaderFile);
	//void SetTexture(std::string& textureFile);

private:
	static const int numVertices = 128;
	static const int size = numVertices * numVertices;
	Vertex vertices[size];
	unsigned int indices[(numVertices - 1) * (numVertices - 1) * 6];
	Mesh m_Mesh;
	Shader m_Shader;
	Texture m_Texture;
};
