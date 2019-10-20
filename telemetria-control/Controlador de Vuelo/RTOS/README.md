# Controlador de tiempo real utilizando FreeRTOS:
El objetivo de este firmware, es generar un controlador de vuelo capaz de recabar todos los datos del vuelo del cohete y almacenarlos en un archivo, una vez recuperado, se podran recuperar los datos por medio de un servidor tcp.

## Primeros pasos
Para comenzar a trabajar en el proyecto, se utilizaron dos SDK:
El primero es el oficial del esp. Que tiene todos los drivers y ejemplos para las funciones mas basicas del ESP8266. En la pagina
https://docs.espressif.com/projects/esp8266-rtos-sdk/en/latest/get-started/index.html#setup-toolchain
hay un instructivo para descargarlo y configurar el eclipse, es recomendable utilizar las mismas rutas que en el tutorial para minimizar las posibilidades de errores.

### Instalar dependencias:

```
sudo apt-get install gcc git wget make libncurses-dev flex bison gperf python python-serial
```
### Instalar el IDE
Descargar e instalar [Eclipse IDE](https://www.eclipse.org/downloads/) que se va a usar para compilar el proyecto
### Descargar el SDK
Se puede directamente clonar el repositorio del [ESP8266_RTOS_SDK](https://github.com/espressif/ESP8266_RTOS_SDK)
```
mkdir -p ~/esp
cd ~/esp
git clone https://github.com/espressif/ESP8266_RTOS_SDK.git
```

### Descargar el Toolchain
Descargar el toolchain correspondiente segun la distribucion de linux que se tenga: 
* [Linux 32](https://dl.espressif.com/dl/xtensa-lx106-elf-linux32-1.22.0-92-g8facf4c-5.2.0.tar.gz)
* [Linux 64](https://dl.espressif.com/dl/xtensa-lx106-elf-linux64-1.22.0-92-g8facf4c-5.2.0.tar.gz)

Descomprimir con:
```
tar -xzf ~/Downloads/https://dl.espressif.com/dl/xtensa-lx106-elf-linux64-1.22.0-88-gde0bdc1-4.8.5.tar.gz
```

### Importar el proyecto
[Instrucciones Eclipse](https://github.com/espressif/ESP8266_RTOS_SDK/blob/master/docs/en/get-started/eclipse-setup.rst)

### Grabar el ESP desde Eclipse
Con todo configurado, se puede grabar el modulo directamente desde eclipse.Flash from Eclipse:

* Clic derecho sobre el proyecto en el Project Explorer
* Seleccionar Build Targets -> Create
* Ponemos como nombre flash dejando el resto de las opciones sin cambios
* Una vez hecho esto, se puede grabar con Shif+F9

### Commit y Push desde Eclipse:
Si se importo el proyecto desde una copia local del repositorio, se puede hacer commit y push del proyecto desde eclipse:
* Clic derecho sobre el proyecto en el Project Explorer
* Seleccionar Team -> Commit...
* En el panel inferior aparece el cuadro de dialogo de Git Staging, asegurarse que todos los archivos que modificamos esten marcados para subirse
* Escribir un comentario sobre los cambios que se hicieron en Commit Message
* Presionar el boton Commit and Push, se abrira el cuadro de dialogo de loggin y se carga sube el proyecto.

## ESP-IDF Components library
El segundo SDK, contiene los drivers para la mayoria de los modulos comerciales mas utilizados, se puede descargar de:
https://github.com/UncleRus/esp-idf-lib
Una vez clonado el repositorio, solo hay que modificar el Makefile en el eclipse agregando la linea:
EXTRA_COMPONENT_DIRS := /home/user/myprojects/esp/esp-idf-lib/components


# Descripcion del firmware y objetivos:
El firmware se esta separado por modulos, uno para cada grupo de sensores, uno para el servidor tcp, un sistema de archivos y un modulo central que sera el encargado de la inicializacion del firmware y la sincronizacion de los modulos.
### Modulo Acelerometros:
Encargado de medir la aceleracion en los tres ejes espaciales durante todo el vuelo. Tiene que ser capaz de detectar tanto el despegue como el aterrizaje y generar eventos cuando se terminen de medir los tres ejes.
### Modulo Barometro:
Mide presion y temperatura todo el tiempo, en el estado inicial se tiene que calibrar a cero.
### Modulo Sistema de Archivos:
En el inicio genera un archivo .json donde se van a guardar todos los datos del vuelo en formato json. Recive los valores enteros de los sensores y los organiza en un bloque json que es agregado al final del archivo.
Tiene que ser capaz de crear y borrar el archivo donde se almacenaran los datos. Asi como tambien de enviarlo al servidor web cuando sea requerido.
### Modulo servidor tcp
Monta una api web con los metodos GET y POST, cuando recibe un comando GET devuelve el archivo json generado durante el vuelo, con post se pueden configurar algunos parametros a definir.
### Tarea Principal:
Encargada de la sincronizacion, en el inicio configura todos los modulos y queda esperando a que los acelerometros detecten el despegue, desde ese momento comienza a tomar lecturas de los sensores cada 10 ms, estos valores son promediados y almacenados en el sistema de archivos cada 50 o 100 ms (definir).
