#include "terrain2.h"


// Get's the size of the file in bytes.
inline int GetFileLength(std::istream& file)
{
	int pos = file.tellg();
	file.seekg(0, std::ios::end);
	int length = file.tellg();
	// Restore the position of the get pointer
	file.seekg(pos);

	return length;
}

// Convert data from the char buffer to a floating point value between 0..1
// depending on the storage value of the original data
// NOTE: This only works with (LSB,MSB) data storage.
inline float GetHeightValue(const unsigned char* data, unsigned char numBytes)
{
	switch (numBytes)
	{
	case 1:
	{
		return (unsigned char)(data[0]) / (float)0xff;
	}
	break;
	case 2:
	{
		return (unsigned short)(data[1] << 8 | data[0]) / (float)0xffff;
	}
	break;
	case 4:
	{
		return (unsigned int)(data[3] << 24 | data[2] << 16 | data[1] << 8 | data[0]) / (float)0xffffffff;
	}
	break;
	default:
	{
		assert(false);  // Height field with non standard pixel sizes
	}
	break;
	}

	return 0.0f;
}

inline float GetPercentage(float value, const float min, const float max)
{
	value = glm::clamp(value, min, max);
	return (value - min) / (max - min);
}

Terrain2::Terrain2(float heightScale, float blockScale) :
	m_Shader("./res/basicShader"), m_TerrainTexture("./res/grass.jpg")
{
	m_BlockScale = blockScale;
	m_HeightScale = heightScale;
	m_MaxHeight = 0;
	LoadHeightMap("./res/terrain0-16bbp-257x257.raw", 16, 257, 257);
	//m_Textures[0].LoadTexture("./res/grass.jpg");
	//m_Textures[1].LoadTexture("./res/rock.png");
	//m_Textures[2].LoadTexture("./res/snow.jpg");

	m_TerrainMesh.GenerateMesh(m_Vertices, sizeof(m_Vertices) / sizeof(m_Vertices[0]), m_IndexBuffer, sizeof(m_IndexBuffer) / sizeof(m_IndexBuffer[0]));
}

Terrain2::~Terrain2()
{

}

void Terrain2::GenerateIndexBuffer()
{
	if (m_HeightMapDimensions.x < 2 || m_HeightMapDimensions.y < 2)
	{
		return;
	}

	const unsigned int terrainWidth = m_HeightMapDimensions.x;
	const unsigned int terrainHeight = m_HeightMapDimensions.y;
	
	unsigned int indicesCount = 0;
	unsigned int numVertices = terrainWidth * terrainHeight;

	const unsigned int numTriangles = (terrainWidth - 1) * (terrainWidth - 1) * 2;

	//m_IndexBuffer.resize(numTriangles * 3);

	for (int y = 0; y < terrainHeight - 1; y++)
	{
		for (int x = 0; x < terrainWidth - 1; x++)
		{
			int bLeft = (y * terrainWidth) + x;
			int bRight = bLeft + 1;
			int tLeft = ((y + 1) * terrainWidth) + x;
			int tRight = tLeft + 1;
			m_IndexBuffer[indicesCount++] = bLeft;
			m_IndexBuffer[indicesCount++] = tLeft;
			m_IndexBuffer[indicesCount++] = bRight;
			m_IndexBuffer[indicesCount++] = tLeft;
			m_IndexBuffer[indicesCount++] = tRight;
			m_IndexBuffer[indicesCount++] = bRight;
		}
	}
}

void Terrain2::GenerateNormals()
{
	int indexSize = (numVertices - 1) * (numVertices - 1) * 6;

	for (unsigned int i = 0; i < indexSize; i += 3)
	{
		// Positions buffer
		glm::vec3 v0 = m_PositionBuffer[m_IndexBuffer[i + 0]];
		glm::vec3 v1 = m_PositionBuffer[m_IndexBuffer[i + 1]];
		glm::vec3 v2 = m_PositionBuffer[m_IndexBuffer[i + 2]];
		// Normal
		glm::vec3 normal = glm::normalize(glm::cross(v1 - v0, v2 - v0));
		// Normal buffer
		m_NormalBuffer[m_IndexBuffer[i + 0]] += normal;
		m_NormalBuffer[m_IndexBuffer[i + 1]] += normal;
		m_NormalBuffer[m_IndexBuffer[i + 2]] += normal;
	}

	const glm::vec3 UP(0.0f, 1.0f, 0.0f);
	for (unsigned int i = 0; i < m_NormalBuffer.size(); ++i)
	{
		m_NormalBuffer[i] = glm::normalize(m_NormalBuffer[i]);

#if ENABLE_SLOPE_BASED_BLEND
		float fTexture0Contribution = glm::saturate(glm::dot(m_NormalBuffer[i], UP) - 0.1f);
		m_ColorBuffer[i] = glm::vec4(fTexture0Contribution, fTexture0Contribution, fTexture0Contribution, m_ColorBuffer[i].w);
#endif

	}
}

void Terrain2::GenerateVertexBuffers()
{

}

void Terrain2::GenerateVertices()
{
	unsigned int size = m_HeightMapDimensions.x * m_HeightMapDimensions.y;

	for (int i = 0; i < size; i++)
	{
		m_Vertices[i].SetPos(m_PositionBuffer[i]);
		m_Vertices[i].SetTexCoord(m_Tex0Buffer[i]);
		m_Vertices[i].SetNormal(m_NormalBuffer[i]);
	}
}

void Terrain2::LoadHeightMap(const std::string& filename, unsigned char bitsPerPixel, unsigned int width, unsigned int height)
{
	std::ifstream ifs;
	ifs.open(filename, std::ifstream::binary);
	if (ifs.fail())
	{
		std::cerr << "Failed to open file: " << filename << std::endl;
		return;
	}

	const unsigned int bytesPerPixel = bitsPerPixel / 8;
	const unsigned int expectedFileSize = (bytesPerPixel * width * height);
	const unsigned int fileSize = GetFileLength(ifs);

	if (expectedFileSize != fileSize)
	{
		std::cerr << "Exptected file size does not match" << std::endl;
		return;
	}

	unsigned char* heightMap = new unsigned char[fileSize];
	ifs.read((char*)heightMap, fileSize);

	if (ifs.fail())
	{
		std::cerr << "An error occurred while reading from the height map file: " << filename << std::endl;
		ifs.close();
		delete[] heightMap;
		return;
	}
	ifs.close();

	unsigned int numVertices = width * height;
	m_PositionBuffer.resize(numVertices);
	//m_ColorBuffer.resize(numVertices);
	m_NormalBuffer.resize(numVertices);
	m_Tex0Buffer.resize(numVertices);
	//m_Vertices.resize(numVertices);

	m_HeightMapDimensions = glm::vec2(width, height);

	// Size of the terrain in world units
	float terrainWidth = (width - 1) * m_BlockScale;
	float terrainHeight = (height - 1) * m_BlockScale;

	float halfTerrainWidth = terrainWidth * 0.5f;
	float halfTerrainHeight = terrainHeight * 0.5f;

	for (unsigned int j = 0; j < height; ++j)
	{
		for (unsigned int i = 0; i < width; ++i)
		{
			unsigned int index = (j * width) + i;
			assert(index * bytesPerPixel < fileSize);
			float heightValue = GetHeightValue(&heightMap[index * bytesPerPixel], bytesPerPixel);
			if (heightValue * m_HeightScale > m_MaxHeight)
			{
				m_MaxHeight = heightValue * m_HeightScale;
			}

			float S = (i / (float)(width - 1));
			float T = (j / (float)(height - 1));

			float X = (S * terrainWidth) - halfTerrainWidth;
			float Y = (T * terrainHeight) - halfTerrainHeight;
			float Z = heightValue * m_HeightScale;

			// Blend 3 textures depending on the height of the terrain
			float tex0Contribution = 1.0f - GetPercentage(heightValue, 0.0f, 0.75f);
			float tex2Contribution = 1.0f - GetPercentage(heightValue, 0.75f, 1.0f);

			m_NormalBuffer[index] = glm::vec3(0);
			m_PositionBuffer[index] = glm::vec3(X, Y, Z);
#if ENABLE_MULTITEXTURE
			m_ColorBuffer[index] = glm::vec4(tex0Contribution, tex0Contribution, tex0Contribution, tex2Contribution);
#else
			//m_ColorBuffer[index] = glm::vec4(1.0f);
#endif
			m_Tex0Buffer[index] = glm::vec2(S, T);
		}
	}

	std::cout << "Terrain has been loaded!" << std::endl;
	delete[] heightMap;

	GenerateIndexBuffer();
	GenerateNormals();
	//GenerateVertexBuffers();
	GenerateVertices();

}

float Terrain2::GetMaxHeight()
{
	return m_MaxHeight;
}

void Terrain2::Draw(Camera& c, Transform& t)
{
	m_Shader.Bind();
	m_TerrainTexture.Bind();
	m_Shader.Update(t, c);
	m_TerrainMesh.Draw();
}