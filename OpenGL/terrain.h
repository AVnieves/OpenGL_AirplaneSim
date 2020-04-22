#pragma once
#include "../source/mesh.h"
#include "../source/texture.h"
#include "../source/shader.h"
#include <map>
#include <vector>

class Terrain
{
public:
	Terrain(/*const std::string& shaderFile,const std::string& textureFile*/);
	~Terrain();
	void GenerateTerrain();
	void Draw(Camera& c, Transform& t);
	//void SetShader(std::string& shaderFile);
	//void SetTexture(std::string& textureFile);
	void AddTextureMapElement(unsigned int texPos, Texture tex);
	void UpdateVertices();
	//Texture GetTexture(unsigned int pos);
	void UpdateTerrainTexture(Camera&);
	void UpdateTerrainTexture2(Camera& c);

private:
	static const int numVertices = 128;
	static const int size = numVertices * numVertices;
	Vertex* vertPointer;
	Vertex vertices[size];
	unsigned int indices[(numVertices - 1) * (numVertices - 1) * 6];
	Vertex nextVertices[size];
	unsigned int nextIndices[(numVertices - 1) * (numVertices - 1) * 6];
	//Vertex verticesL[size];
	//unsigned int indicesL[(numVertices - 1) * (numVertices - 1) * 6];
	//Vertex verticesR[size];
	//unsigned int indicesR[(numVertices - 1) * (numVertices - 1) * 6];

	Mesh m_Mesh;
	Shader m_Shader;
	Texture m_Texture;
	//std::vector < std::pair<glm::vec3, Texture&>> textureMap;
	//std::map < int, Texture&> textureMap;
	//std::vector<Texture> textures;
	std::map < int, Vertex[size]> vertexMap;

};
