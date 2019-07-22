# Sotware del Banco de Pruebas

## Detalles:

El software esta desarollado en python , por el momento hay que hacerle varias modificaciones como evitar el uso de variabes globales y agregarle mas funciones.

### Contenido de archivos:
* El archivo **banco_motores.py** contiene todo el programa en si con la parte gráfica.
* El archivo **coheteria.py** Contiene todas las bibliotecas empleadas en **banco_motores.py**

### Funciones a agregar:

* Posibilidad de reiniciar las mediciones.
* Guardado de datos adquiridos.
* Comunicacion serial con placa encargada de adquirir los datos de las mediciones y del incio de la ignición del motor.

##  Python y Bibliotecas:

### windows: 
Al instalar python ya incluye la biblioteca tkinter , lo unico que se necesita instalar es numpy y matplotlib por medio del la consola de comandos (cmd).
Desde la cmd deber realizar los comandos: 
``` markdown
cd 
```
Hasta ubicarse en la carpeta `cd:\Python27\Scripts>` y ahi escribir los siguientes comandos:
``` markdown
pip install matplotlib 
```
``` markdown
pip install numpy
```
### Linux Ubuntu - Mint - Debian:
Python se instala desde la terminal pormedio del comando :
``` markdown
sudo apt-get install python
```
A diferencia de windows en linux ,tkinter se debe instalar manualmente por medio del siguiente comando:
``` markdown
sudo apt-get install python-tk
```
Para instalar el comando pip de debe utilizar el comando:
``` markdown
sudo apt-get install pip
```
Luegode eso debe hacer instalar las bibliotecas numpy y matplotlib por medio de los comandos pip al igual que en windows:
``` markdown
pip install matplotlib 
```
``` markdown
pip install numpy
```

