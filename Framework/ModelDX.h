#pragma once
#include <string>
#include <vector>
#include <d3d11_2.h>
#include "ObjReader.h"
#include <DirectXMath.h>
#include "DXUtil.h"
#include "BinaryIO.h"
using namespace DirectX;

class ModelDX
{
public:
	ModelDX();
	ModelDX(const std::string &objPath, const std::string &mtlPath, ID3D11Device1 *device, ID3DBlob* vertexShaderBuffer, const std::vector<D3D11_INPUT_ELEMENT_DESC> &layout, const XMMATRIX &matrix, bool binary = false);
	void Release();

	ID3D11Buffer *vertexBuffer;
	ID3D11InputLayout *inputLayout;
	unsigned long long vertexCount;
	Material material;
	ID3D11Buffer *modelMatrixBuffer;
};

