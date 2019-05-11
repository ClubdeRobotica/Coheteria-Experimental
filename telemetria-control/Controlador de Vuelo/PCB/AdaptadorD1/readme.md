# Adaptador D1

## PCB Adaptacion Wemos D1 Mini
 
 ![](https://github.com/ClubdeRobotica/Coheteria-Experimental/blob/master/telemetria-control/Controlador%20de%20Vuelo/PCB/AdaptadorD1/bosquejo.png)
 
 El objetivo de este pcb es poder conectar una placa de desarrollo wemos mini D1 a las placas de sensores que se van a colocar en los cohetes.
 Debe ser un shield con pines hembra en el medio para conectar el D1 Mini y en el exterior pines macho para conectar las placas de sensores como esta en la imagen PCBSensores.png, los conectores 1 y 2 son van se conectan al conector de la izquierda del mini d1 y los conectores 3 y 4 al de la derecha
 
 
## PCB Sensor Presion
 ![](https://github.com/ClubdeRobotica/Coheteria-Experimental/blob/master/telemetria-control/Controlador%20de%20Vuelo/PCB/AdaptadorD1/BatBmp.png)
 Un PCB del mismo tamano que el otro algo similar a la imagen, el espacio da justo para poner un sensor BMP180 (1) y el conector para la bateria (2). Lo ideal es que tenga las cuatro tiras de pines a los costados, pero se puede aliminar alguno en caso de que falte espacio.
 Lo unico a tener en cuenta es que ademas de la alimentacion, los pines SDA y SCL tiene que ir conectados con los pines D2 y D1 del Wemos.
 D2 -- SDA
 D1 -- SCL
