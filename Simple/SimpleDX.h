#pragma once
#include "DXApp.h"
#include "Data.h"

class SimpleDX : public DXApp
{
public:
	SimpleDX(HINSTANCE hInstance);;
	virtual ~SimpleDX();
private:
	bool InitScene() override;
	void Update() override;
	void Render() override;
};

