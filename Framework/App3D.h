#pragma once
#include <windows.h>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <iomanip>
#include "Util.h"
#include "Vertex.h"
#include "Vector.h"
#include "Material.h"
#include "Input.h"

class App3D
{
public:
	App3D(HINSTANCE hInstance);
	virtual ~App3D();

	bool benchmarking = false;
	bool processInput = true;
	bool update = true;
	bool saveDeviceInfo = false;
	int benchmarkFrameCount = 10000;
	std::string assetPath = "Assets/";
	std::string shaderPath;
	std::string binaryPath;
	std::string modelPath;
	Color bgColor;
	Input input;

	int Run();
	virtual LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

protected:
	double			mDeltaTime = 0;
	float			mFPS = 0;
	std::string		mBenchmarkResultName;
	std::string		mDeviceInfoFileName;
	HWND			mWindow;
	HINSTANCE		mInstance;
	unsigned int	mHeight;
	unsigned int	mWidth;
	std::string		mAppTitle;
	std::string		mWindowClass;
	unsigned long	mWindowStyle;

	virtual bool InitAPI() = 0;
	virtual bool InitScene() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void UpdateWindowTitle() = 0;
	virtual void SwapBuffer() = 0;
	virtual void SaveSnapshot(std::string file) = 0;
	virtual void SaveDeviceInfo(std::string file) = 0;

private:
	__int64			mPreviousCount = 0;
	__int64			mCurrentCount = 0;
	__int64			mFrequency = 0;
	float			mElapsedTime = 0;
	unsigned int	mDeltaFrameCount = 0;
	std::vector<float>	mFrameTimes;
	unsigned int	mFrameCount = 0;
	bool			mInLoop = false;

	float mUpdateTime = 0;
	float mRenderTime = 0;
	float mSwapBufferTime = 0;

	std::vector<float>	mUpdateTimes;
	std::vector<float>	mRenderTimes;
	std::vector<float>	mSwapBufferTimes;

	bool firstSnapshot = false;

	bool InitWindow();
	int MsgLoop();
	void StartTime();
	void UpdateDeltaTime();
	void UpdateTime();
	bool Benchmark();
};