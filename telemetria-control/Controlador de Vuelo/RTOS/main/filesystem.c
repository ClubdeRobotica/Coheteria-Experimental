/* SPIFFS filesystem example.
   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <stdio.h>
#include <string.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include "esp_err.h"
#include "esp_log.h"
#include "esp_spiffs.h"
#include "filesystem.h"

static const char *FS_TAG = "filesystem.c";

void filesystem_main(void)
{
    ESP_LOGI(FS_TAG, "Initializing SPIFFS");

    esp_vfs_spiffs_conf_t conf = {
      .base_path = "/spiffs",
      .partition_label = NULL,
      .max_files = 5,
      .format_if_mount_failed = true
    };

    // Use settings defined above to initialize and mount SPIFFS filesystem.
    // Note: esp_vfs_spiffs_register is an all-in-one convenience function.
    esp_err_t ret = esp_vfs_spiffs_register(&conf);

    if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            ESP_LOGE(FS_TAG, "Failed to mount or format filesystem");
        } else if (ret == ESP_ERR_NOT_FOUND) {
            ESP_LOGE(FS_TAG, "Failed to find SPIFFS partition");
        } else {
            ESP_LOGE(FS_TAG, "Failed to initialize SPIFFS (%s)", esp_err_to_name(ret));
        }
        return;
    }

    size_t total = 0, used = 0;
    ret = esp_spiffs_info(NULL, &total, &used);
    if (ret != ESP_OK) {
        ESP_LOGE(FS_TAG, "Failed to get SPIFFS partition information (%s)", esp_err_to_name(ret));
    } else {
        ESP_LOGI(FS_TAG, "Partition size: total: %d, used: %d", total, used);
    }
}

/*
 * @brief Guarda los datos que llegan en DataToSave en el archivo, indicado en PathToSave
 * param:
 * 	DataToSave:		El buffer que se tiene que guardar
 * 	PathToSave:		La ubicacion del archivo donde se guardan los datos
 * 	ExistingFile:	Como esta explicado en el enum ExistingFile
 */
int SaveData (char *DataToSave, char *PathToSave, char NewFile){
 // Verificamos si el archivo existe
	struct stat st;
	if (stat(PathToSave, &st) == 0) {
		//El archivo existe, si se tiene que hacer un archivo nuevo:
		if(NewFile == EF_CreateAlways)
			unlink(PathToSave);
	}
	else{
		if(NewFile == EF_OnlyOpen)
	        return -1;
	}
    FILE* f = fopen(PathToSave, "w");
    if (f == NULL) {
        ESP_LOGE(FS_TAG, "Failed to open file for writing");
        return -1;
    }
    fseek(f, 1, SEEK_END);
    fprintf(f, DataToSave);
    fclose(f);
    ESP_LOGI(FS_TAG, DataToSave);
	return 0;
}


/*
 * Por ahora solamente abro el archivo para mostrar el contenido
 */
int LoadData(char *Path){
    FILE *f = fopen(Path, "r");
    if (f == NULL) {
        ESP_LOGE(FS_TAG, "Failed to open file for reading");
        return -1;
    }
    char line[64];
    fgets(line, sizeof(line), f);
    fclose(f);
    // strip newline
    char* pos = strchr(line, '\n');
    if (pos) {
        *pos = '\0';
    }
    ESP_LOGI(FS_TAG, "Read from file: '%s'", line);
    return 0;
}
