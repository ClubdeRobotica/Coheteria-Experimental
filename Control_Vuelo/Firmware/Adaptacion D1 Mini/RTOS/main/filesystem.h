/*
 * filesystem.h
 *
 *  Created on: 24 oct. 2019
 *      Author: german
 */

#ifndef MAIN_FILESYSTEM_H_
#define MAIN_FILESYSTEM_H_

int fs_Init(void);
int fs_LoadData(char *Path);
int fs_SaveData (char *DataToSave, char *PathToSave, char NewFile);

enum ExistingFile{
	EF_CreateAlways,		//!< Siempre se crea un archivo nuevo
	EF_OnlyOpen,			//!< Solo escribe en un archivo existente
	EF_Append,				//!< Se escribe al final de un archivo existente o se crea uno nuevo
};

#endif /* MAIN_FILESYSTEM_H_ */
