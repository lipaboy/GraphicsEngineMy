﻿#pragma once
#include "Mesh.h"
#include <vector>
#include "GraphicsEngine/Vector3.h"


//struct TriangleInObjFile
//{
//	int v1Idx, t1Idx, n1Idx;
//	int v2Idx, t2Idx, n2Idx;
//	int v3Idx, t3Idx, n3Idx;
//};
//
//class MeshObjFile : public Mesh
//{
//public:
//	MeshObjFile(LPCWSTR pFilepath);
//
//	virtual void Init();
//	virtual void Deinit();
//
//private:
//	LPCWSTR m_pFilepath;
//
//	void ReadAllTriangles();
//	bool ReadVector3(const std::string & line, Vector3 & vec);
//	bool ReadVector2(const std::string & line, D3DXVECTOR2 & vec);
//	bool ReadTriangle(const std::string & line, TriangleInObjFile & triangle);
//
//	std::vector<Vector3>		m_vertices;
//	std::vector<Vector3>		m_normals;
//	std::vector<D3DXVECTOR2>		m_textCoords;
//	std::vector<int>				m_indices;
//	std::vector<TriangleInObjFile>	m_triangles;
//};
