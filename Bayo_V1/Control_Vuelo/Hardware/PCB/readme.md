# Controlador de Vuelo

## PCB Adaptacion Wemos D1 Mini
 
 ![](./PCB_Adaptacion_D1_Mini/Vistas 3D de la placa/Vista9.jpg)
 
 El primer objetivo de este pcb es tener una placa madre que contenga los sensores de presion y temperatura, acelerometros, conector para la bateria y buzzer.
 En esta primera version, para simplificar el desarrollo del firmware se armara un shield para el Wemos D1 Mini que quepa en el interior de un tubo de 50mm. De este modo, se puede ir probando el firmware con una protoboard y un Wemos D1 que sabemos que funciona bien.
 Caracteristicas del shield:
-  	 Conector para Wemos D1 Mini
-  	 Conector para Baterias
-  	 Acelerometro lineals de 3 ejes
-  	 Multiplexor analogico para seleccion del acelerometro
-  	 Sensor de presion y temperatura
-  	 Buzzer
 
## PCB ESP8266

 ![](https://circuits4you.com/wp-content/uploads/2016/12/ESP8266-Programming-Circuit.png)

 Una segunda version de la misma placa, integra en el PCB del mainboard el modulo ESP-07 y un header para conectar un puerto serie, mas el boton de reset y un jumper que permita bootear el esp8266 en modo flash.
 En esta version, se eliminan conectores y el Wemos D1, disminuyendo el peso total del controlador.
 Caracteristicas de la placa:
-  	 Conector para puerto serie
-  	 Switch Reset
-  	 Jumper de seleccion de modo de booteo
-  	 ESP8266 con conector para antena externa
-  	 Conector para Baterias
-  	 Acelerometro lineals de 3 ejes
-  	 Multiplexor analogico para seleccion del acelerometro
-  	 Sensor de presion y temperatura
-  	 Buzzer
 
