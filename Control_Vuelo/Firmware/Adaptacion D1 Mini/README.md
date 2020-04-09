# Firmware de Control

## Versiones
Ecisten dos versiones del firmware:
-	Cohetino: Es un firmware de pruebas, programado en arduino y se esta usando para testear el funcionamiento de los modulos de los sensores. Esta version no es la definitiva, pero sirve para testear la placa base.
-	RTOS: Es el firmware definitivo, basado en freeRTOS, una tarea encargada de cada bloque del hardware, evitando de este modo que algun error en los drivers de los modulos bloqueen el funcionamiento de todo el controlador.

## Version RTOS
El proyecto de Eclipse para poder compilar y grabar el firmware para el esp8266 utilizando eclipse y el ESP8266_RTOS_SDK.

### Instalacion
Para que todo funcione bien, conviene poner tanto el toolchain como el sdk en home/usuario/esp:
#### Instalar dependencias:

```
sudo apt-get install gcc git wget make libncurses-dev flex bison gperf python python-serial
```
#### Instalar el IDE
Descargar e instalar [Eclipse IDE](https://www.eclipse.org/downloads/) que se va a usar para compilar el proyecto
#### Descargar el SDK
Se puede directamente clonar el repositorio del [ESP8266_RTOS_SDK](https://github.com/espressif/ESP8266_RTOS_SDK)
```
mkdir -p ~/esp
cd ~/esp
git clone https://github.com/espressif/ESP8266_RTOS_SDK.git
```

#### Descargar el Toolchain
Descargar el toolchain correspondiente segun la distribucion de linux que se tenga: 
* [Linux 32](https://dl.espressif.com/dl/xtensa-lx106-elf-linux32-1.22.0-92-g8facf4c-5.2.0.tar.gz)
* [Linux 64](https://dl.espressif.com/dl/xtensa-lx106-elf-linux64-1.22.0-92-g8facf4c-5.2.0.tar.gz)

Descomprimir con:
```
tar -xzf ~/Downloads/https://dl.espressif.com/dl/xtensa-lx106-elf-linux64-1.22.0-88-gde0bdc1-4.8.5.tar.gz
```

#### Importar el proyecto
[Instrucciones Eclipse](https://github.com/espressif/ESP8266_RTOS_SDK/blob/master/docs/en/get-started/eclipse-setup.rst)

#### Grabar el ESP desde Eclipse
Con todo configurado, se puede grabar el modulo directamente desde eclipse.Flash from Eclipse:

* Clic derecho sobre el proyecto en el Project Explorer
* Seleccionar Build Targets -> Create
* Ponemos como nombre flash dejando el resto de las opciones sin cambios
* Una vez hecho esto, se puede grabar con Shif+F9

#### Commit y Push desde Eclipse:
Si se importo el proyecto desde una copia local del repositorio, se puede hacer commit y push del proyecto desde eclipse:
* Clic derecho sobre el proyecto en el Project Explorer
* Seleccionar Team -> Commit...
* En el panel inferior aparece el cuadro de dialogo de Git Staging, asegurarse que todos los archivos que modificamos esten marcados para subirse
* Escribir un comentario sobre los cambios que se hicieron en Commit Message
* Presionar el boton Commit and Push, se abrira el cuadro de dialogo de loggin y se carga sube el proyecto.


### Estado del Firmware

Todavia no hace nada, es solo un ejemplo para poder configurar el IDE



