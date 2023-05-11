#include "IOManager.h"
#include "Error.h"
#include <fstream> //Leer archivos

bool IOManager::ReadFileToBuffer(string FilePath, vector<unsigned char>& buffer) {
	ifstream file(FilePath, ios::binary); //Leer el archivo

	//Validar que el archivo se ley� correctamente
	if (file.fail()) { //Fall� el archivo
		FatalError(FilePath.c_str()); //Mostrar la ruta que est� fallando
		return false;
	}

	file.seekg(0, ios::end);

	int FileSize = file.tellg(); //Tama�o del archivo

	FileSize -= file.tellg();

	buffer.resize(FileSize);

	file.read((char*)&(buffer[0]), FileSize); //Leer el archivo
	file.close(); //Cerrar el archivo

	return true;
}
