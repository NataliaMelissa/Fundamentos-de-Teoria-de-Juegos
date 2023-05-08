#include "HLSL_Program.h"
#include "Error.h"
#include <vector>
#include <iostream>
#include <fstream> //leer archivos

using namespace std;

//Constructor
HLSL_Program::HLSL_Program() {
	ProgramID = 0;
	VertexShaderID = 0;
	FragmentShaderID = 0;
	NumAttribute = 0;
}

//Destructor
HLSL_Program::~HLSL_Program() {}

//Funci�n para compilar la informaci�n del shader
void HLSL_Program::CompileShader(const string& ShaderPath, GLuint id) {
	string FileContent; //Contenido del archivo
	string line; //l�nea del archivo
	GLint Compiled = 0; //Variable para saber si el shader se ha compilado o no

	ifstream ShaderFile(ShaderPath); //Obtener la ruta del archivo del Shader

	//Validar si se pudo abrir el archivo del Shader
	if (ShaderFile.fail()) {//Termin� en error
		FatalError("Couldn't open " + ShaderPath);
	}

	//Si todo sale bien, leer el arcivo
	while (getline(ShaderFile, line)) {
		FileContent += line + "\n";
	}

	ShaderFile.close(); //Cerrar el archivo

	const char* contents = FileContent.c_str();

	//Compilar el shader
	glShaderSource(id, 1, &contents, nullptr); //Pasar el contenido del shader a memoria
	glCompileShader(id); //Compilar el shader
	glGetShaderiv(id, GL_COMPILE_STATUS, &Compiled); //Saber si compil� el shader o no

	//Validar si se compil� el shader
	if (Compiled == GL_FALSE) { //El shader no se compil�
		GLint MaxLenght = 0; //Tama�o del Log de compilaci�n del shader

		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &MaxLenght); //Saber cu�nto va a pesar el Log

		vector<GLchar> InfoLog(MaxLenght); //Vector que contiene la informaci�n de compilaci�n

		glGetShaderInfoLog(id, MaxLenght, &MaxLenght, &InfoLog[0]); //Obtener la informaci�n de compilaci�n del Log del Shader

		FatalError("Shader couldn't be compiled " + printf("%s", &(InfoLog[0]))); //Imprimir el error

		glDeleteShader(id); //Borra el shader que creaste que termin� en error
		return;
	}
}

//M�todo: Funci�n para obtener atributos
void HLSL_Program::AddAttribute(const string AttributeName) {
	glBindAttribLocation(ProgramID, NumAttribute++, AttributeName.c_str()); //Agregar los atributos al programa
}

//M�todo: Funci�n para usar un programa
void HLSL_Program::Use() {
	glUseProgram(ProgramID); 

	for (int i = 0; i < NumAttribute; i++) {
		glEnableVertexAttribArray(i);
	}
}

//M�todo: Funci�n para dejar de usar un programa
void HLSL_Program::Unuse() {
	glUseProgram(0);

	for (int i = 0; i < NumAttribute; i++) {
		glDisableVertexAttribArray(i);
	}
}

//M�todo: Funci�n para compilar los shaders
void HLSL_Program::CompileShaders(const string& VertexShaderFilePath, const string& FragmentShaderFilePath) {
	ProgramID = glCreateProgram(); //Int�rprete
	VertexShaderID = glCreateShader(GL_VERTEX_SHADER); //Crear el VertexShaderID

	//Comprobar que se crearon los objetos se crearon correctamente
	if (VertexShaderID == 0) { //Termin� en error si pas� el condicional
		FatalError("Error creating Vertex Shader");
	}

	FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	//Comprobar que se cre� bien el FragmentShaderID
	if (FragmentShaderID == 0) { //Termin� en error
		FatalError("Error creating Fragment Shader");
	}

	//Compilar los shaders creados
	CompileShader(VertexShaderFilePath, VertexShaderID); //Shader VertexShaderID
	CompileShader(FragmentShaderFilePath, FragmentShaderID); //Shader FragmentShaderID
}

//M�todo: Funci�n para vincular/linker del shader con c++
void HLSL_Program::LinkShader() {
	GLint Linked = 0; //Variable para saber si el programa se vincul� o no

	//Vincular los shaders al programa
	glAttachShader(ProgramID, VertexShaderID); //VertexShaderID
	glAttachShader(ProgramID, FragmentShaderID); //FragmentShaderID

	glLinkProgram(ProgramID); //Vincular el programa

	glGetProgramiv(ProgramID, GL_LINK_STATUS, (int*) &Linked); //Saber si se vincul� el shader al programa o no

	//Validar si se vincul� el shader con el programa
	if (Linked == GL_FALSE) {
		GLint MaxLenght = 0; //Variable que tendr� el tama�o del log

		glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &MaxLenght); //Obtener el tama�o del log

		vector<GLchar> InfoLog(MaxLenght); //Vector que contiene la informaci�n de compilaci�n

		glGetProgramInfoLog(ProgramID, MaxLenght, &MaxLenght, &InfoLog[0]); //Obtener la informaci�n de compilaci�n del Log del Programa

		glDeleteProgram(ProgramID); //Borra el programa que creaste que termin� en error

		FatalError("Shader couldn't link to the program " + printf("%s", &(InfoLog[0]))); //Imprimir el error

		//Borrar los shaders que se intentaron vincular
		glDeleteShader(VertexShaderID); //Borrar el shader VertexShaderID 
		glDeleteShader(FragmentShaderID); //Borrar el shader FragmentShaderID
		return;
	}

	//Desvincular los shaders con el programa
	glDetachShader(ProgramID, VertexShaderID); //VertexShaderID
	glDetachShader(ProgramID, FragmentShaderID); //FragmentShaderID


	//Borrar los shaders que se intentaron vincular
	glDeleteShader(VertexShaderID); //Borrar el shader VertexShaderID 
	glDeleteShader(FragmentShaderID); //Borrar el shader FragmentShaderID
}

//M�todo: Funci�n para obtener la ubicaci�n del shader
GLuint HLSL_Program::GetUniformLocation(const string& name) {
	GLuint location = glGetUniformLocation(ProgramID, name.c_str()); //Encontrar la unicaci�n de un programa en espec�fico

	//Validar que se encontr� la ubicaci�n 
	if (location == GL_INVALID_INDEX) { //Termin� en error
		FatalError("Uniform " + name + " not found");
	}

	return location;
}

