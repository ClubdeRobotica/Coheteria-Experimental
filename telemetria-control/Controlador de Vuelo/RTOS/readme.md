Controlador de tiempo real utilizando FreeRTOS:
El objetivo de este firmware, es generar un controlador de vuelo capaz de recabar todos los datos del vuelo del cohete y almacenarlos en un archivo, una vez recuperado, se podran recuperar los datos por medio de un servidor tcp.

Primeros pasos
Para comenzar a trabajar en el proyecto, se utilizaron dos SDK:
El primero es el oficial del esp. Que tiene todos los drivers y ejemplos para las funciones mas basicas del ESP8266. En la pagina
https://docs.espressif.com/projects/esp8266-rtos-sdk/en/latest/get-started/index.html#setup-toolchain
hay un instructivo para descargarlo y configurar el eclipse, es recomendable utilizar las mismas rutas que en el tutorial para minimizar las posibilidades de errores.
El segundo SDK, contiene los drivers para la mayoria de los modulos comerciales mas utilizados, se puede descargar de:
https://github.com/UncleRus/esp-idf-lib
Una vez clonado el repositorio, solo hay que modificar el Makefile en el eclipse agregando la linea:
EXTRA_COMPONENT_DIRS := /home/user/myprojects/esp/esp-idf-lib/components


Descripcion del firmware y objetivos:
El firmware se esta separado por modulos, uno para cada grupo de sensores, uno para el servidor tcp, un sistema de archivos y un modulo central que sera el encargado de la inicializacion del firmware y la sincronizacion de los modulos.
Modulo Acelerometros:
Encargado de medir la aceleracion en los tres ejes espaciales durante todo el vuelo. Tiene que ser capaz de detectar tanto el despegue como el aterrizaje y generar eventos cuando se terminen de medir los tres ejes.
Modulo Barometro:
Mide presion y temperatura todo el tiempo, en el estado inicial se tiene que calibrar a cero.
Modulo Sistema de Archivos:
En el inicio genera un archivo .json donde se van a guardar todos los datos del vuelo en formato json. Recive los valores enteros de los sensores y los organiza en un bloque json que es agregado al final del archivo.
Tiene que ser capaz de crear y borrar el archivo donde se almacenaran los datos. Asi como tambien de enviarlo al servidor web cuando sea requerido.
Modulo servidor tcp
Monta una api web con los metodos GET y POST, cuando recibe un comando GET devuelve el archivo json generado durante el vuelo, con post se pueden configurar algunos parametros a definir.
Tarea Principal:
Encargada de la sincronizacion, en el inicio configura todos los modulos y queda esperando a que los acelerometros detecten el despegue, desde ese momento comienza a tomar lecturas de los sensores cada 10 ms, estos valores son promediados y almacenados en el sistema de archivos cada 50 o 100 ms (definir).