 
# Firmware Banco de Pruebas

Esta basado en los ejemplos de esp y la libreria para el HX711 de bogde: [https://github.com/bogde/HX711](https://github.com/bogde/HX711 "https://github.com/bogde/HX711"). Falta hacer una funcion de calibracion, se le deberia mandar desde el software una trama con el peso en gramos de una carga conocida.
- **SSID**: "BancoPruebasCdR"
- **PASS**: "cdr_coheteria2019"

------------

## Leer Datos por wifi:
Para leer los datos, conectarse a la red y entrar a la ip: 
- **IP para conexion**: 192.168.4.1
- **Puerto**: 80
- **Formato trama json**: *{ T: float, grs:float }*
El sistema manda un valor de tiempo y peso por http (en la practica mas o menos cada 1.2 segundos)
