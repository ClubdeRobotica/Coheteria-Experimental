# Sistema de telemetría y control de vuelo
El sistema de telemetría y control de vuelo estará compuesto por dos subsistemas: la electrónica de control y de sensado presente en el cohete y la estación en tierra. Ambos deberán mantener una comunicación ininterrumpida durante la misión, que permita el envío en tiempo real de los datos recabados por el cohete.

#### Integrantes
* Matías Afur
* Gaspar Santamarina
* Matías Bucca
* Santiago Rojas



## Especificaciones

### Cohete
La electrónica de a bordo estará desarrollada sobre un NodeMCU, encargado de recibir los datos multiplexados de los sensores, almacenarlos y enviarlos a la estación en tierra a través de una red WiFi.

#### Sensores
Para estimar la altura se usarán en conjunto:

* 2 Módulos acelerómetros
* 2 Barómetros

Además, en una etapa posterior, se añadirá:

* GPS
* Imagen

#### Logeo
* Módulo SD

#### Comunicación
Procolo propio sobre TCP/IP.

#### Sistema de recuperación
Buzzer activado al eyectar paracaidas.

#### Electrónica adicional
* Sistema de alimentación mediante baterías recargables.
* Desarrollo de un PCB que contenga al NodeMCU, junto con los demás componentes del sistema.


### Estación en tierra
La estación en tierra estará conformada por un Acces Point, junto con una Notebook corriendo un software encargado de establecer un socket TCP/IP al que se conectará el NodeMCU y que permita graficar/almacenar los datos enviados por este.

Además, deberá contar con un dispositivo conectado a través de USB que permita sensar la presión atmosférica para así calibrar el cohete antes del lanzamiento.




