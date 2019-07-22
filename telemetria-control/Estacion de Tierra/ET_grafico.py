# coding=utf-8
from Tkinter import *
import socket
import threading
import ast
flag=False
class lan:
    def init(self):
        self.ser = socket.socket(socket.AF_INET, socket.SOCK_STREAM)           #instanciamos un objeto para trabajar con el socket
        self.ser.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.archivo = open("data.txt", "w")
    def launch(self):
        
        PUERTO=8050                                                      #Aceptamos conexiones entrantes con el metodo listen. Por parámetro las conexiones simutáneas.
        self.ser.bind(("",PUERTO))                                             #Puerto y servidor que debe escuchar
        self.ser.listen(1)   
        salida=str("Servidor en: "+ socket.gethostbyname(socket.gethostname())+" puerto: "+str(PUERTO)+"\n")
        text.insert("end",salida )
        salida=str("Esperando conexion\n")
        text.insert("end",salida )
        cli, addr = self.ser.accept()                                         #Instanciamos un objeto cli (socket cliente) para recibir dato
        self.client=cli
        salida= "Recibo conexion de la IP: " + str(addr[0]) + " Puerto: " + str(addr[1])+"\n"
        text.insert("end",salida)
        
        while True:

 
            try:
                recibido = self.client.recv(1024)#Recibimos el mensaje, con el metodo recv recibimos datos. Por parametro la cantidad de bytes para recibir
                text.insert("end",str(recibido)+"\n" )                                            #Si se reciben datos nos muestra la IP y el mensaje recibido
                text.see("end")
                self.archivo.write(str(recibido)+"\n")
                self.client.send("ok")                        
            except:
                text.insert("end","conexion perdida\n" ) 
                self.client.close()
                cli, addr = self.ser.accept()
                self.client=cli
                salida= "Recibo conexion de la IP: " + str(addr[0]) + " Puerto: " + str(addr[1])+"\n"
                text.insert("end",salida )
                text.see("end")
 
    def end(self):
        try:
            self.client.close()
            self.ser.shutdown(socket.SHUT_RDWR)	
            self.ser.close()
            self.archivo.close()
            text.insert("end","Conexiones cerradas\n")
        except:
            self.ser.close()
            self.archivo.close()
        

def state():
    global nose
    global flag
    if flag:
        flag= False
        nose.end()
        button.configure(text="Iniciar")
    else:
        flag= True
        nose.init()
        t = threading.Thread(target=nose.launch)
        t.start()
        button.configure(text="Parar")
nose=lan()
window=Tk()
window.title("ET")
#---------------------Menu superior------------
menubar=Menu(window,relief="flat")
filemenu = Menu(menubar, tearoff=0)
filemenu.add_command(label="Nuevo")
filemenu.add_command(label="Guardar")
menubar.add_cascade(label="Archivo", menu=filemenu)
filemenu = Menu(menubar, tearoff=0)
filemenu.add_command(label="Configuracion")
menubar.add_cascade(label="Opciones", menu=filemenu)
filemenu = Menu(menubar, tearoff=0)
filemenu.add_command(label="Informacion")
menubar.add_cascade(label="Ayuda", menu=filemenu)
window.config(menu=menubar)
#:---------------------Paneles----------------------
panelg=Frame(window)
panelg.pack(side="top",expand=1,fill="both")
panel1=LabelFrame(panelg,text="Straming")
panel1.pack(side="left",fill="both")
panel2=LabelFrame(panelg,text="informacion")
panel2.pack(side="right",fill="both",expand="yes")
panel3=LabelFrame(window,text="Control")
panel3.pack(side="bottom",fill="x")
#:---------------------Streaming----------------------
text = Text(panel1,bg="BLACK",fg="WHITE")
scroll = Scrollbar(panel1, command=text.yview, orient=VERTICAL )
scroll.config(command=text.yview)
text.configure(yscrollcommand=scroll.set)
text.pack(side=LEFT,fill=BOTH, expand='YES')
scroll.pack(side=RIGHT, fill=BOTH)
#:---------------------Data----------------------
tittle=Label(panel2,text="Datos procesados",font=("Courier", 20))
tittle.grid(row=0,column=0,columnspan=2)

tittle=Label(panel2,text="Max presion: ")
tittle.grid(row=1,column=0,sticky='w')
h_pressure=Label(panel2,text="000000")
h_pressure.grid(row=1,column=1)
tittle=Label(panel2,text="Pa")
tittle.grid(row=1,column=2,sticky='e')

tittle=Label(panel2,text="Min presion: ")
tittle.grid(row=2,column=0,sticky='w')
l_pressure=Label(panel2,text="000000")
l_pressure.grid(row=2,column=1)
tittle=Label(panel2,text="Pa")
tittle.grid(row=2,column=2,sticky='e')

tittle=Label(panel2,text="Max temperatura: ")
tittle.grid(row=3,column=0,sticky='w')
h_temperature=Label(panel2,text="000")
h_temperature.grid(row=3,column=1)
tittle=Label(panel2,text="ºC")
tittle.grid(row=3,column=2,sticky='e')

tittle=Label(panel2,text="Min temperatura: ")
tittle.grid(row=4,column=0,sticky='w')
l_temperature=Label(panel2,text="000")
l_temperature.grid(row=4,column=1)
tittle=Label(panel2,text="ºC")
tittle.grid(row=4,column=2,sticky='e')

tittle=Label(panel2,text="Altura estimada: ")
tittle.grid(row=5,column=0,sticky='w')
height=Label(panel2,text="0000")
height.grid(row=5,column=1)
tittle=Label(panel2,text="M")
tittle.grid(row=5,column=2,sticky='e')
#:---------------------Control----------------------
button=Button(panel3,text="Iniciar",command=state,width=10,height=2)
button.grid(column=0,row=0)


window.mainloop()
