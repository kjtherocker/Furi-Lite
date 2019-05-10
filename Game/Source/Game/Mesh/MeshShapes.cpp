#include "GamePCH.h"

Mesh* Mesh::CreateBox(vec2 size, bool flipx)
{
    VertexFormat verts[4];

    if( flipx == false )
    {
        verts[0] = VertexFormat( -size.x/2, -size.y/2, 0,  255,255,255,255,  0,0 );
        verts[1] = VertexFormat( -size.x/2,  size.y/2, 0,  255,255,255,255,  0,1 );
        verts[2] = VertexFormat(  size.x/2,  size.y/2, 0,  255,255,255,255,  1,1 );
        verts[3] = VertexFormat(  size.x/2, -size.y/2, 0,  255,255,255,255,  1,0 );
    }
    else
    {
        verts[0] = VertexFormat( -size.x/2, -size.y/2, 0,  255,255,255,255,  1,0 );
        verts[1] = VertexFormat( -size.x/2,  size.y/2, 0,  255,255,255,255,  1,1 );
        verts[2] = VertexFormat(  size.x/2,  size.y/2, 0,  255,255,255,255,  0,1 );
        verts[3] = VertexFormat(  size.x/2, -size.y/2, 0,  255,255,255,255,  0,0 );
    }

    unsigned int indices[6] = { 0,1,2, 0,2,3 };

    Mesh* pMesh = new Mesh();
    pMesh->Init( verts, 4, indices, 6, GL_STATIC_DRAW );

    return pMesh;
};

Mesh* Mesh::CreatePlane(vec2 Origin, ivec2 NumVertices, vec2 Worldsize, vec2 uv)
{

	int VerticeCount = NumVertices.x * NumVertices.y;
	VertexFormat* vertices = new VertexFormat[VerticeCount];


	vec2 Increment = vec2(Worldsize.x / (NumVertices.x - 1), Worldsize.y / (NumVertices.y - 1));

	vec2 uvIncrement = vec2(uv.x / (NumVertices.x - 1), uv.y / (NumVertices.y - 1));

	for (int x = 0; x < NumVertices.x; x++)
	{
		for (int y = 0; y < NumVertices.y; y++)
		{
			vertices[y*NumVertices.x + x] = VertexFormat(Origin.x + (Increment.x * x), 0, Origin.y + (Increment.y * y), 255, 255, 255, 255, Origin.x + (uvIncrement.x * x), Origin.y + (uvIncrement.y * y));
		}
	}

	unsigned int indiceCount = ((NumVertices.x - 1) * (NumVertices.y - 1)) * 6;

	unsigned int* Indices = new unsigned int[indiceCount];

	int CurrentVert = 0;

	for (int row = 0; row < NumVertices.x - 1; row++)
	{
		for (int col = 0; col < NumVertices.y - 1; col++)
		{
			int Index = col* NumVertices.x + row;

			Indices[CurrentVert] = Index;

			Indices[CurrentVert + 1] = Index + NumVertices.x;

			Indices[CurrentVert + 2] = Index + NumVertices.x + 1;

			Indices[CurrentVert + 3] = Index;

			Indices[CurrentVert + 4] = Index + NumVertices.x + 1;

			Indices[CurrentVert + 5] = Index + 1;

			CurrentVert += 6;
		}
	}

	Mesh* pMesh = new Mesh();


	glPointSize(5);
	pMesh->Init(vertices, VerticeCount, Indices, indiceCount, GL_STATIC_DRAW);



	delete[] vertices;
	delete[] Indices;

	return pMesh;
};

Mesh * Mesh::CreateFromObj(const char* objfilename)
{
    long length = 0;
    char* buffer = LoadCompleteFile(objfilename, &length);
    if (buffer == 0 || length == 0)
    {
        delete buffer;
        return 0;
    }
    char* next_token = 0;
    char* line = strtok_s(buffer, "\n", &next_token);


    std::vector<vec3>vectorVerts;
    std::vector<vec2>vectorUVs;
    std::vector<vec3>vectorNormals;
    std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;

    while (line)
    {
        OutputMessage("%s\n", line);

        //Here is where the business occurs
        if (line[0] == 'v' && line[1] == ' ')
        {

            vec3 verts;
            sscanf_s(line, "%*s %f %f %f", &verts.x, &verts.y, &verts.z);
            vectorVerts.push_back(verts);

        }

        else if (line[0] == 'v' && line[1] == 't')
        {
            vec2 uvs;
            sscanf_s(line, "%*s %f %f", &uvs.x, &uvs.y);
            vectorUVs.push_back(uvs);
        }

        else if (line[0] == 'v' && line[1] == 'n')
        {
            vec3 normals;
            sscanf_s(line, "%*s %f %f %f", &normals.x, &normals.y, &normals.z);
            vectorNormals.push_back(normals);
        }

        else if (line[0] == 'f')
        {
            unsigned int vertexIndex[3];
            unsigned int uvIndex[3];
            unsigned int normalIndex[3];
            sscanf_s(line, "%*s %d/%d/%d %d/%d/%d %d/%d/%d", &vertexIndex[0], &uvIndex[0], &normalIndex[0],
                &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            uvIndices.push_back(uvIndex[0]);
            uvIndices.push_back(uvIndex[1]);
            uvIndices.push_back(uvIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);

        }

        line = strtok_s(0, "\n", &next_token);
    }

    unsigned int VertexIndex = 0;
    unsigned int UVIndex = 0;
    unsigned int NormalIndex = 0;
    VertexFormat* verts = new VertexFormat[vertexIndices.size()];

    for (unsigned int i = 0; i < vertexIndices.size(); i++)
    {
        VertexIndex = vertexIndices[i];
        vec3 Pos = vectorVerts[VertexIndex - 1];
        verts[i].pos = Pos;
    }
    for (unsigned int i = 0; i < uvIndices.size(); i++)
    {
        UVIndex = uvIndices[i];
        vec2 uv = vectorUVs[UVIndex - 1];
        verts[i].uv = uv;
    }
    for (unsigned int i = 0; i < normalIndices.size(); i++)
    {
        NormalIndex = normalIndices[i];
        vec3 normal = vectorNormals[NormalIndex - 1];
        verts[i].normal = normal;
    }




    Mesh* pMesh = new Mesh();
    pMesh->Init(verts, vertexIndices.size(), 0, 0, GL_STATIC_DRAW);

    delete[] buffer;
    delete[] verts;

    return pMesh;

}

Mesh* Mesh::CreateCircle(vec3 size)
{
    VertexFormat verts[8];

    verts[0] = VertexFormat(-size.x / 2, -size.y / 2, 0, 255, 255, 255, 255, 0, 0);
    verts[1] = VertexFormat(-size.x / 2, size.y / 2, 0, 255, 255, 255, 255, 0, 1);
    verts[2] = VertexFormat(size.x / 2, size.y / 2, 0, 255, 255, 255, 255, 1, 1);
    verts[3] = VertexFormat(size.x / 2, -size.y / 2, 0, 255, 255, 255, 255, 1, 0);
    verts[4] = VertexFormat(-size.x / 4, -size.y / 4, 0, 255, 255, 255, 255, 0, 0);
    verts[5] = VertexFormat(-size.x / 4, size.y / 4, 0, 255, 255, 255, 255, 0, 1);
    verts[6] = VertexFormat(size.x / 4, size.y / 4, 0, 255, 255, 255, 255, 1, 1);
    verts[7] = VertexFormat(size.x / 4, -size.y / 4, 0, 255, 255, 255, 255, 1, 0);


    unsigned int indices[12] = { 0,2,1, 0,3,2, 4,6,5, 4,7,6 };

    Mesh* pMesh = new Mesh();
    pMesh->Init(verts, 8, indices, 12, GL_STATIC_DRAW);

    return pMesh;
};

Mesh* Mesh::CreateCube(vec3 size)
{
    VertexFormat verts[24];

    verts[0] = VertexFormat(-size.x / 2, -size.y / 2, 0, 255, 255, 255, 255, 0, 0);
    verts[1] = VertexFormat(-size.x / 2, size.y / 2, 0, 255, 255, 255, 255, 0, 1);   // Front Face
    verts[2] = VertexFormat(size.x / 2, size.y / 2, 0, 255, 255, 255, 255, 1 / 6.0f, 1);
    verts[3] = VertexFormat(size.x / 2, -size.y / 2, 0, 255, 255, 255, 255, 1 / 6.0f, 0);

    verts[4] = VertexFormat(-size.x / 2, -size.y / 2, -1, 255, 255, 255, 255, 1 / 6.0f, 0);
    verts[5] = VertexFormat(-size.x / 2, size.y / 2, -1, 255, 255, 255, 255, 1 / 6.0f, 1); // Back Face
    verts[6] = VertexFormat(size.x / 2, size.y / 2, -1, 255, 255, 255, 255, 2 / 6.0f, 1);
    verts[7] = VertexFormat(size.x / 2, -size.y / 2, -1, 255, 255, 255, 255, 2 / 6.0f, 0);

    verts[8] = VertexFormat(size.x / 2, size.y / 2, 0, 255, 255, 255, 255, 2 / 6.0f, 0); // Right Side
    verts[9] = VertexFormat(size.x / 2, -size.y / 2, 0, 255, 255, 255, 255, 2 / 6.0f, 1);
    verts[10] = VertexFormat(size.x / 2, -size.y / 2, -1, 255, 255, 255, 255, 3 / 6.0f, 1);
    verts[11] = VertexFormat(size.x / 2, size.y / 2, -1, 255, 255, 255, 255, 3 / 6.0f, 0);

    verts[12] = VertexFormat(-size.x / 2, size.y / 2, 0, 255, 255, 255, 255, 3 / 6.0f, 1);
    verts[13] = VertexFormat(-size.x / 2, -size.y / 2, 0, 255, 255, 255, 255, 3 / 6.0f, 0); // Left Side
    verts[14] = VertexFormat(-size.x / 2, size.y / 2, -1, 255, 255, 255, 255, 4 / 6.0f, 1);
    verts[15] = VertexFormat(-size.x / 2, -size.y / 2, -1, 255, 255, 255, 255, 4 / 6.0f, 0);

    verts[16] = VertexFormat(-size.x / 2, size.y / 2, 0, 255, 255, 255, 255, 4 / 6.0f, 1);
    verts[17] = VertexFormat(size.x / 2, size.y / 2, 0, 255, 255, 255, 255, 4 / 6.0f, 0); // Top
    verts[18] = VertexFormat(-size.x / 2, size.y / 2, -1, 255, 255, 255, 255, 5 / 6.0f, 1);
    verts[19] = VertexFormat(size.x / 2, size.y / 2, -1, 255, 255, 255, 255, 5 / 6.0f, 0);

    verts[20] = VertexFormat(-size.x / 2, -size.y / 2, 0, 255, 255, 255, 255, 5 / 6.0f, 1);
    verts[21] = VertexFormat(-size.x / 2, -size.y / 2, -1, 255, 255, 255, 255, 5 / 6.0f, 0); // Bottom
    verts[22] = VertexFormat(size.x / 2, -size.y / 2, 0, 255, 255, 255, 255, 1, 1);
    verts[23] = VertexFormat(size.x / 2, -size.y / 2, -1, 255, 255, 255, 255, 1, 0);



    unsigned int indices[36] = {
        0,1,2,     0,3,2,       // front face
        4,5,6,     4,7,6,       // back face
        9,8,10,    8,10,11,     // right face
        13,12,15,  15,12,14,    // left face
        16,17,18,  17,18,19,    // top face
        20,21,22,  23,22,21    // bottom face

    };

    Mesh* pCubeMesh = new Mesh();
    pCubeMesh->Init(verts, 24, indices, 36, GL_STATIC_DRAW);

    return pCubeMesh;

}

Mesh * Mesh::CreateInverseCube(vec3 size)
{
    VertexFormat verts[36];

    verts[0] = VertexFormat(-size.x / 2, -size.y / 2, size.z / 2, 255, 255, 255, 255, 0, 0);
    verts[1] = VertexFormat(-size.x / 2, size.y / 2, size.z / 2, 255, 255, 255, 255, 0, 1);
    verts[2] = VertexFormat(size.x / 2, size.y / 2, size.z / 2, 255, 255, 255, 255, 1, 1);
    verts[3] = VertexFormat(size.x / 2, -size.y / 2, size.z / 2, 255, 255, 255, 255, 1, 0);

    verts[4] = VertexFormat(-size.x / 2, -size.y / 2, -size.z / 2, 255, 255, 255, 255, 0, 0);
    verts[5] = VertexFormat(-size.x / 2, size.y / 2, -size.z / 2, 255, 255, 255, 255, 0, 1);
    verts[6] = VertexFormat(size.x / 2, size.y / 2, -size.z / 2, 255, 255, 255, 255, 1, 1);
    verts[7] = VertexFormat(size.x / 2, -size.y / 2, -size.z / 2, 255, 255, 255, 255, 1, 0);

    verts[8] = VertexFormat(-size.x / 2, -size.y / 2, -size.z / 2, 255, 255, 255, 255, 0, 0);
    verts[9] = VertexFormat(size.x / 2, -size.y / 2, -size.z / 2, 255, 255, 255, 255, 0, 1);
    verts[10] = VertexFormat(-size.x / 2, -size.y / 2, size.z / 2, 255, 255, 255, 255, 1, 1);
    verts[11] = VertexFormat(size.x / 2, -size.y / 2, size.z / 2, 255, 255, 255, 255, 1, 0);


    verts[12] = VertexFormat(size.x / 2, -size.y / 2, -size.z / 2, 255, 255, 255, 255, 1, 0);
    verts[13] = VertexFormat(size.x / 2, size.y / 2, -size.z / 2, 255, 255, 255, 255, 1, 1);
    verts[14] = VertexFormat(size.x / 2, -size.y / 2, size.z / 2, 255, 255, 255, 255, 0, 0);
    verts[15] = VertexFormat(size.x / 2, size.y / 2, size.z / 2, 255, 255, 255, 255, 0, 1);

    verts[16] = VertexFormat(-size.x / 2, -size.y / 2, -size.z / 2, 255, 255, 255, 255, 0, 0);
    verts[17] = VertexFormat(size.x / 2, -size.y / 2, -size.z / 2, 255, 255, 255, 255, 1, 0);
    verts[18] = VertexFormat(-size.x / 2, -size.y / 2, size.z / 2, 255, 255, 255, 255, 0, 1);
    verts[19] = VertexFormat(size.x / 2, -size.y / 2, size.z / 2, 255, 255, 255, 255, 1, 1);

    verts[20] = VertexFormat(-size.x / 2, -size.y / 2, size.z / 2, 255, 255, 255, 255, 0, 0);
    verts[21] = VertexFormat(-size.x / 2, -size.y / 2, size.z / 2, 255, 255, 255, 255, 0, 1);
    verts[22] = VertexFormat(-size.x / 2, size.y / 2, -size.z / 2, 255, 255, 255, 255, 1, 1);
    verts[23] = VertexFormat(-size.x / 2, size.y / 2, -size.z / 2, 255, 255, 255, 255, 1, 0);

    //unsigned int indices[36] = {/*Frontsquare*/  20,23,22, 20,21,22,/*Backsquare*/
    //    16,17,19, 16,18,19, /*RightSquare*/  13,15,14,  13,12,14, /*BottomSquare*/  4,5,6,  4,7,6, /*LeftSquare*/
    //    0,3,2,  0,2,1 };

    unsigned int indices[36] = {/*Frontsquare*/  0,2,1, 0,3,2,/*Backsquare*/
        4,7,6, 4,5,6, /*RightSquare*/  13,12,14,  13,15,14, /*BottomSquare*/ 16,18,19, 16,17,19, /*LeftSquare*/
        20,21,22,  20,23,22 };

    Mesh* pMesh = new Mesh();
    pMesh->Init(verts, 24, indices, 36, GL_STATIC_DRAW);

    return pMesh;
}
