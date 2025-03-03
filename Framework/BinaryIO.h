#pragma once
#include <string>
#include <fstream>
#include <vector>
#include "Vertex.h"

namespace BinaryIO
{
	void WriteVertices(const std::string &path, const std::vector<Vertex> &vertices, const std::string &materialName);
	void ReadVertices(const std::string &path, std::vector<Vertex> &vertices, std::string &materialName);

	void WriteVector4s(const std::string &path, const std::vector<Vector4> &vertices);
	void ReadVector4s(const std::string &path, std::vector<Vector4> &vertices);

	void WriteVector3s(const std::string &path, const std::vector<Vector3> &vertices);
	void ReadVector3s(const std::string &path, std::vector<Vector3> &vertices);
};

