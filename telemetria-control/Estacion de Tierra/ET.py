# coding=utf-8
import socket
<<<<<<< HEAD
#instanciamos un objeto para trabajar con el socket
ser = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
#Puerto y servidor que debe escuchar

ser.bind(("localhost", 8050))
#Aceptamos conexiones entrantes con el metodo listen. Por parámetro las conexiones simutáneas.
ser.listen(1)
#Instanciamos un objeto cli (socket cliente) para recibir datos
cli, addr = ser.accept()
=======
PUERTO=8050

#instanciamos un objeto para trabajar con el socket
ser = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
#Puerto y servidor que debe escuchar
ser.bind(("",PUERTO))
#Aceptamos conexiones entrantes con el metodo listen. Por parámetro las conexiones simutáneas.
ser.listen(1)
#Instanciamos un objeto cli (socket cliente) para recibir datos

archivo = open("data.txt", "w")
print "Servidor en: "+ socket.gethostbyname(socket.gethostname())+" puerto: "+str(PUERTO)
print "Esperando conexion"
cli, addr = ser.accept()
print "Recibo conexion de la IP: " + str(addr[0]) + " Puerto: " + str(addr[1])
>>>>>>> 343635a253366289d7f69698db82c430279c58e1
while True:

    #Recibimos el mensaje, con el metodo recv recibimos datos. Por parametro la cantidad de bytes para recibir
    recibido = cli.recv(1024)
<<<<<<< HEAD

    #Si se reciben datos nos muestra la IP y el mensaje recibido
    print "Recibo conexion de la IP: " + str(addr[0]) + " Puerto: " + str(addr[1])
    print recibido

#Cerramos la instancia del socket cliente y servidor
cli.close()
ser.close()
print("Conexiones cerradas")
=======
    #Si se reciben datos nos muestra la IP y el mensaje recibido
    print recibido
    if recibido == "end":
        break
    archivo.write(str(recibido)+"\n") 
#Cerramos la instancia del socket cliente y servidor
cli.close()
ser.close()
print("Conexiones cerradas")
archivo.close()
>>>>>>> 343635a253366289d7f69698db82c430279c58e1
