# Sistema de telemetría y control de vuelo



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




