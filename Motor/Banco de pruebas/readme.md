# Banco de pruebas

El objetivo de este bloque es desarrollar un banco de pruebas de bajo coste y fácil de replicar, que pueda ser replicado por cualquiera sin necesidad de muchos conocimientos de electrónica. Permitiendo poner toda la atención en el desarrollo de motores.

![Boceto banco de pruebas](https://github.com/ClubdeRobotica/Coheteria-Experimental/blob/Bayo_V1/Documentacion/Avance_lProyecto/Imagenes/Banco3d.png)

En la imagen se muestra un boceto de la estructura mecanica del banco, se trata de un sistema de rieles con un soporte para fijar el motor y una celda de carga en uno de sus extremos para tomar el valor de la fuerza instantanea generada por el motor.

El conectarlo a la energia, el banco monta una red WiFi a la cual se puede acceder desde cualquier PC. Una vez conectado a la red se ejecuta el software de adquisición de datos desde el que se puede controlar la ignicion del motor y se visualizan los datos en tiempo real.


## Software
El software de adquisicion esta programado en python y es multiplataforma, sólo requiere tener python instalado para correr.
![Software de adquisicion de datos](https://github.com/ClubdeRobotica/Coheteria-Experimental/blob/Bayo_V1/Documentacion/Avance_lProyecto/Imagenes/SoftBanco.png)

## Placa electrónica

La electrónica del banco esta basada en la placa Weemos D1 que integra un modulo WiFi ESP8266 dentro de una placa de desarrollo con formato de Arduino UNO. Se agrega un shield con un relé que controla la ignición del motor y un conector para el conversor A/D HX711.

![Shield Celda de Carga](https://github.com/ClubdeRobotica/Coheteria-Experimental/blob/Bayo_V1/Motor/Banco%20de%20pruebas/Hardware/Shield-celda-carga/Vistas%203D/Vista%203.jpg)


### Estado
[![WVideo de la prueba](https://img.youtube.com/vi/06_TuqDqlls/hqdefault.jpg)](https://youtu.be/06_TuqDqlls)

En el video se muetra una prueba del banco y los datos de fuerza y tiempo en tiempo real, los datos son guardados en un archivo de tipo CSV.

![Salida del Software](https://github.com/ClubdeRobotica/Coheteria-Experimental/blob/Bayo_V1/Documentacion/Avance_lProyecto/Pruebas/SalidaSoft.png)

![Archivo Generado](https://github.com/ClubdeRobotica/Coheteria-Experimental/blob/Bayo_V1/Documentacion/Avance_lProyecto/Pruebas/SalidaCSV.png)

#### Para agregar
##### Software:
* Se cuelga si al hacer clic en iniciiar la pc no esta conectada al banco.
* Falta agregar una opcion que permita seleccionar la ruta y el nombre del archivo csv donde se guardan los datos.

##### Firmware:
* Se deberia agregar una opcion de calibracion.

