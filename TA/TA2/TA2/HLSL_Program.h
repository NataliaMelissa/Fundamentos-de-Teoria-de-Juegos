#pragma once
#include <GL/eglew.h>
#include <string>

using namespace std;

class HLSL_Program {
	//Atributos
	GLuint ProgramID;
	GLuint FragmentShaderID;
	GLuint VertexShaderID;

	void CompileShader(const string& ShaderPath, GLuint id);

	//M�todos
public:
	//Constructor
	HLSL_Program();

	//Destructor
	~HLSL_Program();

	int NumAttribute; //Variable que contiene el n�mero de atributos

	//Funci�n para agregar atributos
	void AddAttribute(const string AttributeNAme);

	//Funci�n para saber si se est� usando el shader
	void Use();

	void Unuse();

	//Funci�n para compilar los shaders
	void CompileShaders(const string& VertexShaderFilePath, const string& FragmentShaderFilePath);

	//Funci�n para vincular (linker) el shader con c++
	void LinkShader();

	//Funci�n para obtener la ubicaci�n del shader
	GLuint GetUniformLocation(const string& name);
};
