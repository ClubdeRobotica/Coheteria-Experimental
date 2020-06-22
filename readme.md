# Vectores experimentales

## Introducción:
Es un proyecto orientado principalmente al estudio de la construccion de cohetes para el lanzamiento de nano satelites. Como incio del proyecto lo que se busca es generar la tecnologia y documentacion necesaria para poder realizar lanzamientos de cansat ( un pequeño satélite del tamaño de una lata de gaseosa). Por otro lado se busca generar mayor interes en las actividades espaciales que son muy pocas difundidas y asi ayudar con el progreso tecnológico.



## Objetivos

El objetivo principal de este proyecto, es lograr desarrollar un pequeño lanzador, que se pueda replicar facilmente y que sea capaz de llevar un cansat a una altura de unos 500 a 1000 metros.
Dividimos al proyecto en dos fases principales, con la primera nos planteamos generar todas las herramientas necesarias para el desarrollo de cohetes, y en la segunda se comienza a desarrollar cohetes y motores.
Dado que este proyecto está apuntado a ser desarrollado por estudiantes sin niguna experiencia previa en coheteria, se planea generar un entorno de desarrollo completo, para que sea posible evaluar los dferentes diseños, tanto de motores como de cohetes.

## Primera Fase
Para poder resolver todos los problemas que surjan a la hora de armar y lanzar un cohete desde cero, se plantean dos bloques de telemetria:
- Kit de Desarrollo de Motores, compuesto por:
 - Un kit de desarrollo para motores de azucar, que permita medir el empuje generado por las distintos propelentes, para poder experimentar con distintos motores sin necesidad de tener que ir al campo a probarlo en un cohete.
 - Una estacion terrena para el controlador de vuelo, es un software que se conecta al controlador de vuelo y permite descargar todos los datos almacenados durante el vuelo y generar graficos que permitan visualizar mas clararamente los datos.
- Kit de Desarrollo para Cohetes, compuesto por:
 - Controlador de vuelo electrónico, capaz de adquirir todos los datos del vuelo y guardarlos en una memoria para su posterior análisis.
 - Una estacion de control para el banco de pruebas, se trata simplemente de un software capaz de conectarse al banco y desde el cual se puedan visualizar todos los datos generados durante la prueba.

Como un anexo para esta fase, se añade el desarrollo de una plataforma para el lanzamiento de los cohetes.

### Kit de Desarrollo de Motores

<img src="https://github.com/ClubdeRobotica/Coheteria-Experimental/blob/Bayo_V1/Documentacion/Avance_lProyecto/Imagenes/Banco3d.png" width="250">  <img src="https://github.com/ClubdeRobotica/Coheteria-Experimental/blob/Bayo_V1/Documentacion/Avance_lProyecto/Imagenes/SoftBanco.png" width="250"> 

El kit de desarrollo para motores de baja potencia, esta compuesto por un sistema mecanico donde se montan los motores y la electrónica necesaria para el analisis del empuje y un sistema informatico para controlar las pruebas. Este kit se encuentra en la etapa final del desarrollo y se puede ver en la [pagina del banco de pruebas](https://github.com/ClubdeRobotica/Coheteria-Experimental/tree/Bayo_V1/Motor/Banco%20de%20pruebas)

#### Sistema mecánico
El sistema mecánico, fabricado con perfiles de aluminio es simplemente una plataforma deslizante y un montaje para una celda de carga. La electronica implicada en este banco es la mas sencilla puesto que se trata simplemente de una placa Wemos D1, con un firmware de arduino que nos permite activar un relay para encender el motor y tomar mediciones de la celda de carga por WiFi.

#### Sistema informático
Está desarrollado en python y ademas de conectarse al banco de pruebas, nos muestra un grafico sencillo de empuje/tiempo.

### Kit de Desarrollo de Cohetes
<img src="https://clubderobotica.github.io/images/pic07b.jpg" width="350">
Se trata como se dijo antes de una placa de telemetria que durante el vuelo va tomando a intervalos regulares, mediciones de presión, temperatura y aceleración y almacenandolos en un archivo que al finalizar el vuelo se puede descargar para su analisis. Adicionalmente se agrega un buzzer, que previo al despegue idica los distintos estados del sistema por medio de distintas combinaciones sonoras y al final del mismo, genera una alarma para facilitar su recuperacion en caso de caer en terreno accidentado.

#### Sistema Electrónico
La placa esta basada en un ESP8266 (en una primera fase en Wemos D1 mini, para simplificar el desarrollo) con un firmware de tiempo real basado en freeRTOS.
Consta de:
- Placa principal: Wemos D1 mini, modificada para mayor alcance del WiFi.
- Sensor de presion y temperatura BMP180
- Acelerómetro de tres ejes ADXL345
- Buzzer
- Bateria de 3.6V

Al iniciar, activa un AP WiFi y un servidor web al que se puede acceder desde una pc, para configurar las condiciones iniciales, o activar el modo de vuelo. Una vez activado el modo de vuelo, el sistema apaga el AP y queda a la espera del despegue, que es detectado por medio de los acelerometros. Una vez iniciado el vuelo, se toman mediciones a intervalos regulares programables de 10, 50, 100 o 500 ms segun se haya configurado y se almacenan los datos en un archivo. Luego de transcurridos un segundo sin detectar variaciones en los sensores, se supone que se ha tocado tierra nuevamente, se detienen las mediciones y se inicia el modo recuperación en el cual se activa nuevamente el AP y se hace sonar el buzzer.

#### Sistema Informatico
Es un software desarrollado en Python, que permite controlar tanto la plataforma de lanzamiento para iniciar el vuelo como graficar los datos del vuelo para su visualizacion.

## Estructura del repo:

 ![Estructura del repo](Documentacion/Avance_lProyecto/arboldearchivos/Coheteria.jpg?raw=true "Arbol")


## Como Participar
Buena parte del desarrollo del proyecto, puede hacerse de manera remota, por lo que no es necesario estar presente en las reuiones de trabajo.
Para participar se puede enviar un correo electrónico a cualquiera de los administradores del proyecto, o por medio del formulario de contacto de la pagina del [Club de Robótica](https://clubderobotica.github.io/).
