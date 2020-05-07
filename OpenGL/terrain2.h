#pragma once
/*
	This code was adapted from the following source.

	Jonathan Dummer
	2007-07-26-10.36

	Simple OpenGL Image Library

	Public Domain
	using Sean Barret's stb_image as a base

	Thanks to:
	* Sean Barret - for the awesome stb_image
	* Dan Venkitachalam - for finding some non-compliant DDS files, and patching some explicit casts
	* everybody at gamedev.net
*/

#include "source/mesh.h"
#include "source/texture.h"
#include "source/shader.h"
#include <string>
#include <fstream>
#include <istream>
#include <iostream>

class Terrain2
{
public:
	Terrain2(float, float);
	~Terrain2();

	void LoadHeightMap(const std::string& filename, unsigned char bpp, unsigned int w, unsigned int h);
	void LoadTexture(const std::string& filename, unsigned int textureStage = 0);

	float GetHeight(const glm::vec3& position);

	void Render();
	float GetMaxHeight();
	void Draw(Camera& c, Transform& t);


private:
	static const int numVertices = 257;
	static const int size = numVertices * numVertices;
	std::vector<glm::vec3> m_PositionBuffer;
	std::vector<glm::vec3> m_NormalBuffer;
	std::vector<glm::vec2> m_Tex0Buffer;
	//std::vector<GLuint> m_IndexBuffer;
	//std::vector<Vertex> m_Vertices;
	Vertex m_Vertices[size];
	unsigned int m_IndexBuffer[(numVertices - 1) * (numVertices - 1) * 6];

	Mesh m_TerrainMesh;
	Shader m_Shader;
	//Texture m_Texture;
	//Vertex m_Vertices[size];

	glm::vec2 m_HeightMapDimensions;
	float m_BlockScale;
	float m_HeightScale;

	static const unsigned int m_NumTextures = 3;
	//Texture m_Textures[m_NumTextures];
	Texture m_TerrainTexture;
	float m_MaxHeight;

protected:
	void GenerateIndexBuffer();
	void GenerateNormals();
	void GenerateVertexBuffers();
	void GenerateVertices();
	void RenderNormals();

};
