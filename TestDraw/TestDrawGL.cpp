#include "TestDrawGL.h"

TestDrawGL::TestDrawGL(HINSTANCE hInstance) : GLApp(hInstance)
{
	mAppTitle = "OpenGL Test Draw";
	mBenchmarkResultName = "gl_test_draw";
	bgColor = Color(0.1f, 0.1f, 0.1f, 1.0f);
}

TestDrawGL::~TestDrawGL()
{
	glDeleteProgram(shaderProgram);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
}

bool TestDrawGL::InitScene()
{
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	eye = glm::vec3(2.2f, 2.2f, 2.2f);
	right = glm::vec3(1.0f, 0.0f, 0.0f);
	center = glm::vec3(0.0f, 0.0f, 0.0f);

	BinaryIO::ReadVector4s(binaryPath + "point_cube_50.bin", verts);

	glClearColor(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_PROGRAM_POINT_SIZE);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	std::vector<GLuint> shaders;
	shaders.push_back(GLUtil::CreateShader(GL_VERTEX_SHADER, shaderPath + "TestDrawVert.glsl"));
	shaders.push_back(GLUtil::CreateShader(GL_FRAGMENT_SHADER, shaderPath + "TestDrawFrag.glsl"));
	shaderProgram = GLUtil::CreateProgram(shaders);
	for_each(shaders.begin(), shaders.end(), glDeleteShader);

	glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	glm::mat4 viewMatrix = glm::lookAt(eye, center, up);
	glm::mat4 projectionMatrix = glm::perspective(glm::radians(60.0f), 800.0f / 800.0f, 1.0f, 500.0f);

	modelMatrixIndex = glGetUniformLocation(shaderProgram, "modelMatrix");
	viewMatrixIndex = glGetUniformLocation(shaderProgram, "viewMatrix");
	projectionMatrixIndex = glGetUniformLocation(shaderProgram, "projectionMatrix");
	glProgramUniformMatrix4fv(shaderProgram, modelMatrixIndex, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glProgramUniformMatrix4fv(shaderProgram, viewMatrixIndex, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glProgramUniformMatrix4fv(shaderProgram, projectionMatrixIndex, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	glCreateVertexArrays(1, &vao);

	glCreateBuffers(1, &vbo);
	glNamedBufferData(vbo, sizeof(Vector4) * verts.size(), &verts[0], GL_STATIC_DRAW);

	glVertexArrayAttribBinding(vao, 0, 0);
	glVertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(float) * 4);

	glEnableVertexArrayAttrib(vao, 0);
	glVertexArrayAttribFormat(vao, 0, 4, GL_FLOAT, GL_FALSE, 0);

	return true;
}

void TestDrawGL::Update()
{
	if (processInput)
	{
		float rotAmount = 0.0f;
		glm::mat4 rotMatrix;
		if (input.right || input.left)
		{
			if (input.right)
				rotAmount = rotDelta;
			if (input.left)
				rotAmount = -rotDelta;
			rotMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotAmount), up);
		}
		else if (input.up || input.down)
		{
			if (input.up)
				rotAmount = -rotDelta;
			if (input.down)
				rotAmount = rotDelta;
			rotMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotAmount), right);
		}

		eye = glm::vec3(rotMatrix * glm::vec4(eye, 1.0f));
		right = glm::normalize(-glm::cross(up, (center - eye)));

		glm::mat4 viewMatrix = glm::lookAt(eye, center, up);
		glProgramUniformMatrix4fv(shaderProgram, viewMatrixIndex, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	}
}

void TestDrawGL::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(vao);
	glUseProgram(shaderProgram);
	
	for (int i = 0; i < verts.size(); ++i)
	{
		glDrawArrays(GL_POINTS, i, 1);
	}
}