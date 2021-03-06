#include "TextureComponent.h"

GLfloat interpolation = .5f;

TextureComponent::TextureComponent()
	: DrawableGameComponent()
{}

TextureComponent::TextureComponent(Application & application)
	: DrawableGameComponent(application)
{}

void TextureComponent::Initialize()
{
	mVertices =
	{
		// Positions          // Colors           // Texture Coords. When we specify texture coords. out of the [0, 1] range, OpenGL repeats the texture by default.
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f,   // Top Right = 0
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f,   // Bottom Right = 1
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // Bottom Left = 2
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 2.0f    // Top Left = 3
	};

	//Indices of the rectangle
	mIndices =
	{
		0, 1, 2,
		0, 2, 3
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(GLuint), &mIndices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(GLfloat), &mVertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	mShader = Shader("shaders/vertexshader.vert", "shaders/fragmentshader.frag");

	//---------- TEXTURES ----------//
	mTextureContainer.SetProgram(mShader.Program());
	mTextureContainer.BindTexture(GL_TEXTURE0);
	mTextureContainer.SetTextureParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
	mTextureContainer.SetTextureParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
	mTextureContainer.SetTextureParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	mTextureContainer.SetTextureParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	mTextureContainer.LoadTexture("res\\container.jpg");
	mTextureContainer.GenerateTexture(GL_RGB, GL_RGB, GL_UNSIGNED_BYTE);
	mTextureContainer.GenerateMipmaps();
	mTextureContainer.FreeImageData();
	mTextureContainer.UnbindTexture();

	mTextureAwesomeFace.SetProgram(mShader.Program());
	mTextureAwesomeFace.BindTexture(GL_TEXTURE1);
	mTextureAwesomeFace.SetTextureParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
	mTextureAwesomeFace.SetTextureParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
	mTextureAwesomeFace.SetTextureParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	mTextureAwesomeFace.SetTextureParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	mTextureAwesomeFace.LoadTexture("res\\awesomeface.png");
	mTextureAwesomeFace.GenerateTexture(GL_RGB, GL_RGB, GL_UNSIGNED_BYTE);
	mTextureAwesomeFace.GenerateMipmaps();
	mTextureAwesomeFace.FreeImageData();
	mTextureAwesomeFace.UnbindTexture();

	glUniform1f(glGetUniformLocation(mShader.Program(), "interpolation"), 1.0f);
}

void TextureComponent::Draw(float DeltaSeconds)
{
	glUseProgram(mShader.Program());

	mTextureContainer.BindTexture(GL_TEXTURE0);
	mTextureContainer.SetSampler2D("ourTexture");

	mTextureAwesomeFace.BindTexture(GL_TEXTURE1);
	mTextureAwesomeFace.SetSampler2D("ourTexture2");

	glUniform1f(glGetUniformLocation(mShader.Program(), "interpolation"), interpolation);

	glBindVertexArray(VAO);

	glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, nullptr);

	glBindVertexArray(0);
	glUseProgram(0);
}
