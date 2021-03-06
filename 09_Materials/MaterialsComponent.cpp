#include "MaterialsComponent.h"

MaterialsComponent::MaterialsComponent(Application& application, Camera& camera)
	: DrawableGameComponent(application, camera)
{}

void MaterialsComponent::Initialize()
{
	mVertices =
	{
		//FRONT FACE
		//Positions				
		0.5f,  0.5f, 0.5f,		0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f,		0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f,		0.0f, 0.0f, 1.0f,
		0.5f,  0.5f, 0.5f,		0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f,		0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f, 0.5f,		0.0f, 0.0f, 1.0f,

		//BACK FACE				
		0.5f,  0.5f, -0.5f,		0.0f, 0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,		0.0f, 0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,		0.0f, 0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,	0.0f, 0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,	0.0f, 0.0f, -1.0f,

		//RIGHT FACE			
		0.5f,  0.5f, -0.5f,		1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f,
		0.5f,  0.5f, -0.5f,		1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f,
		0.5f,  0.5f, 0.5f,		1.0f, 0.0f, 0.0f,

		//LEFT FACE
		-0.5f,  0.5f, -0.5f,	-1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,	-1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.5f,		-1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,	-1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.5f,		-1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, 0.5f,		-1.0f, 0.0f, 0.0f,

		//TOP FACE
		0.5f,  0.5f, -0.5f,		 0.0f, 1.0f, 0.0f,
		0.5f,  0.5f, 0.5f,		 0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f, 0.5f,		 0.0f, 1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,		 0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f, 0.5f,		 0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,	 0.0f, 1.0f, 0.0f,

		//BOTTOM FACE
		0.5f,  -0.5f, -0.5f,	0.0f, -1.0f, 0.0f,
		0.5f,  -0.5f, 0.5f,		0.0f, -1.0f, 0.0f,
		-0.5f,  -0.5f, 0.5f,	0.0f, -1.0f, 0.0f,
		0.5f,  -0.5f, -0.5f,	0.0f, -1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f,		0.0f, -1.0f, 0.0f,
		-0.5f,  -0.5f, -0.5f,	0.0f, -1.0f, 0.0f
	};

	//Generate VBOs and VAO.
	glGenVertexArrays(1, &mVAO);
	glGenBuffers(1, &mVBO);

	//Bind VAO and buffers, and fill in buffer data
	glBindVertexArray(mVAO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(GLfloat), &mVertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

	//Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	mShaderContainer = Shader("shaders/container.vert", "shaders/container.frag");
	mShaderLight = Shader("shaders/light.vert", "shaders/light.frag");

	mContainerTransform = glm::rotate(mContainerTransform, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	mLightTransform = glm::translate(glm::mat4(), lightPosition);
}

void MaterialsComponent::Draw(float DeltaSeconds)
{
	mShaderContainer.UseProgram();
	glBindVertexArray(mVAO);
	//Set up uniforms
	GLint modelLocation = glGetUniformLocation(mShaderContainer.Program(), "model");
	if (modelLocation == -1)
	{
		cout << "Model location = -1" << endl;
		return;
	}

	GLint viewLocation = glGetUniformLocation(mShaderContainer.Program(), "view");
	if (viewLocation == -1)
	{
		cout << "View location = -1" << endl;
		return;
	}

	GLint projectionLocation = glGetUniformLocation(mShaderContainer.Program(), "projection");
	if (projectionLocation == -1)
	{
		cout << "Projection location = -1" << endl;
		return;
	}


	GLint ambientFactorLocation = glGetUniformLocation(mShaderContainer.Program(), "ambientFactor");
	GLint lightPositionLocation = glGetUniformLocation(mShaderContainer.Program(), "light.position");
	GLint cameraPositionLocation = glGetUniformLocation(mShaderContainer.Program(), "cameraPosition");

	GLint matAmbientLocation = glGetUniformLocation(mShaderContainer.Program(), "material.ambient");
	GLint matDiffuseLocation = glGetUniformLocation(mShaderContainer.Program(), "material.diffuse");
	GLint matSpecularLocation = glGetUniformLocation(mShaderContainer.Program(), "material.specular");
	GLint matShineLocation = glGetUniformLocation(mShaderContainer.Program(), "material.shininess");
	glUniform3f(matAmbientLocation, 1.0f, 0.5f, 0.31f);
	glUniform3f(matDiffuseLocation, 1.0f, 0.5f, 0.31f);
	glUniform3f(matSpecularLocation, 0.5f, 0.5f, 0.5f);
	glUniform1f(matShineLocation, 32.0f);

	GLint lightAmbientLocation = glGetUniformLocation(mShaderContainer.Program(), "light.ambient");
	GLint lightDiffuseLocation = glGetUniformLocation(mShaderContainer.Program(), "light.diffuse");
	GLint lightSpecularLocation = glGetUniformLocation(mShaderContainer.Program(), "light.specular");
	glUniform3f(lightAmbientLocation, 0.2f, 0.2f, 0.2f);
	glUniform3f(lightDiffuseLocation, 0.5f, 0.5f, 0.5f); // Let�s darken the light a bit to fit the scene
	glUniform3f(lightSpecularLocation, 1.0f, 1.0f, 1.0f);


	//----- Uncomment this to make the light move in a circle.
	/*float time = glfwGetTime();
	float movementX = 8 * cos(time);
	float movementY = 8 * sin(time);

	mLightTransform = glm::translate(glm::mat4(), glm::vec3(movementX, 3.0f, movementY));
	lightPosition = glm::vec3(movementX, 4.0f, movementY);*/

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(mContainerTransform));
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(mCamera->GetViewMatrix()));
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(mCamera->GetProjectionMatrix()));
	
	glUniform1f(ambientFactorLocation, 0.1f);
	glUniform3f(lightPositionLocation, lightPosition.x, lightPosition.y, lightPosition.z);
	glm::vec3 camPos = mCamera->GetPosition();
	glUniform3f(cameraPositionLocation, camPos.x, camPos.y, camPos.z);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	mShaderLight.UseProgram();
	//Set up uniforms
	modelLocation = glGetUniformLocation(mShaderLight.Program(), "model");
	if (modelLocation == -1)
	{
		cout << "Model location = -1" << endl;
		return;
	}

	viewLocation = glGetUniformLocation(mShaderLight.Program(), "view");
	if (viewLocation == -1)
	{
		cout << "View location = -1" << endl;
		return;
	}

	projectionLocation = glGetUniformLocation(mShaderLight.Program(), "projection");
	if (projectionLocation == -1)
	{
		cout << "Projection location = -1" << endl;
		return;
	}

	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(mLightTransform));
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(mCamera->GetViewMatrix()));
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(mCamera->GetProjectionMatrix()));

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glUseProgram(0);
	glBindVertexArray(0);
}
