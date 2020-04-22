#include <string>
#include "terrain.h"

Terrain::Terrain(/*const std::string& shaderFile = "./res/basicShader", const std::string& textureFile = "./res/bricks.jpg"*/)
	: m_Shader("./res/basicShader"), m_Texture("./res/grass_green_d.jpg")
{
	GenerateTerrain();
	m_Mesh.GenerateMesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
	//nextVertices = nullptr;
	//nextIndices = nullptr;
}

Terrain::~Terrain()
{

}

void Terrain::UpdateTerrainTexture(Camera& c)
{
	
}

//void Terrain::SetShader(std::string& shaderFile)
//{
//
//}
//
//void Terrain::SetTexture(std::string& textureFile)
//{
//
//}

//void Terrain::InitTerrain(std::string& shaderFile, std::string& textureFile)
//{
//	GenerateTerrain();
//	m_Mesh.GenerateMesh(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
//
//}

void Terrain::AddTextureMapElement(unsigned int texPos, Texture tex)
{
	//textures.push_back(tex);
	//textureMap.insert(std::pair<int, Texture&>(texPos, tex));
}

//Texture Terrain::GetTexture(unsigned int pos)
//{
//	//return textures[pos];
//}

void Terrain::Draw(Camera& c, Transform &t)
{
	m_Shader.Bind();
	m_Texture.Bind();
	m_Shader.Update(t, c);
	m_Mesh.Draw();
} 

void Terrain::UpdateVertices()
{

}

//void Terrain::GenerateTerrain()
void Terrain::GenerateTerrain()
{
	glm::vec3 points;
	glm::vec2 texCoords;
	glm::vec3 normals;
	int vertexCount = 0;
	int indicesCount = 0;

	 
	for (int y = -numVertices / 2; y < numVertices / 2; y++)
	{
		for (int x = -numVertices / 2; x < numVertices / 2; x++)
		{
			points = (glm::vec3((float)x, (float)y, 10));

			if (x % 2 == 0 && y % 2 == 0)
				texCoords = glm::vec2(0.f, 0.f);
			else if (x % 2 != 0 && y % 2 == 0)
				texCoords = glm::vec2(1.f, 0.f);
			else if (x % 2 == 0 && y % 2 != 0)
				texCoords = glm::vec2(0.f, 1.f);
			else
				texCoords = glm::vec2(1.f, 1.f);
			//texCoords = (glm::vec2((float)x, (float)y));

			normals = (glm::vec3(0, 0, -1));
			vertices[vertexCount].SetPos(points);
			vertices[vertexCount].SetTexCoord(texCoords);
			vertices[vertexCount].SetNormal(normals);
			vertexCount++;
		}
	}

	for (int y = 0; y < numVertices - 1; y++)
	{
		for (int x = 0; x < numVertices - 1; x++)
		{
			int bLeft = (y * numVertices) + x;
			int bRight = bLeft + 1;
			int tLeft = ((y + 1) * numVertices) + x;
			int tRight = tLeft + 1;
			indices[indicesCount++] = bLeft;
			indices[indicesCount++] = tLeft;
			indices[indicesCount++] = bRight;
			indices[indicesCount++] = tLeft;
			indices[indicesCount++] = tRight;
			indices[indicesCount++] = bRight;
		}
	}
}

void Terrain::UpdateTerrainTexture2(Camera& c)
{
	float xpos, ypos;
	float tempx, tempy;
	int texSize = 128;

	xpos = c.GetPos()->x;
	ypos = c.GetPos()->y;

	if (xpos < 0)
		tempx = (texSize - ((int)xpos % texSize)) + texSize;
	else
		tempx = texSize - ((int)xpos % texSize);

	if (ypos < 0)
		tempy = (texSize - ((int)ypos % texSize)) + texSize;
	else
		tempy = texSize = ((int)ypos % texSize);

	//if (tempx < 24 + 128 || tempy < 24 + 128)
	//{
	//	GenerateTerrain();
	//}
}