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

	//Métodos
public:
	//Constructor
	HLSL_Program();

	//Destructor
	~HLSL_Program();

	int NumAttribute; //Variable que contiene el número de atributos

	//Función para agregar atributos
	void AddAttribute(const string AttributeNAme);

	//Función para saber si se está usando el shader
	void Use();

	void Unuse();

	//Función para compilar los shaders
	void CompileShaders(const string& VertexShaderFilePath, const string& FragmentShaderFilePath);

	//Función para vincular (linker) el shader con c++
	void LinkShader();

	//Función para obtener la ubicación del shader
	GLuint GetUniformLocation(const string& name);
};
