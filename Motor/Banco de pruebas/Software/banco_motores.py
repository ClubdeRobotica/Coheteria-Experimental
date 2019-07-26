from coheteria import *
from com import *
import json
import socket
import sys
std=0
stde=1
port_addres=0
ip_addres=""
def graficar():
    global std
    global stde
    s=[]
    secc=[]
    while stde==1:
        if std==1:
            # TODO: Aca creo que esta queriendo leer el segundo dato y el modulo todavia no se lo envio
            inter=str(banco_hard.datos())
            try:
                inter=json.loads(inter)
                s.append(inter['T'])
                secc.append((inter['grs']*9.81)/1000)
                a.cla()
                a.plot(s,secc)
                canvas.draw()
            except:
                print inter
            banco_hard.respond()
def cronometro():
    global std
    global stde
    ms=0
    sec=0
    minut=0
    while stde==1 :
        if std==1:
            sleep(0.01)
            ms+= 1
            if ms>99:
                sec+=1
                ms=0
            if sec>60:
                minut+=1
                sec=0
            if minut>60:
                minut=0                
            cron['text'] = str(str(minut).zfill(2)+":"+str(sec).zfill(2)+":"+str(ms).zfill(2))
    

def start():
    global std
    global ip_addres
    global port_addres
    global banco_hard
    if port_addres=="" or port_addres==0:
        messagebox.showinfo(message="No se cofiguro ninguna ip o puerto dirigase a las configuraciones", title="Conexion")
    else: 
        banco_hard=com_lan(ip_addres,port_addres)
        inis.config(state="disabled")
        stopb.config(state="normal")
        std=1
def stop():
    global std
    stde=0
    std=0
    inis.config(state="normal")
    stopb.config(state="disabled")
def _quit():
    global stde
    stde=0
    root.quit()     
    root.destroy()  
def config():
    global ip_addres
    global port_addres
    def accept():
        global ip_addres
        global port_addres
        ip_addres=ent1.get()
        port_addres=int(ent2.get())
        configwind.destroy()
    configwind=Tk()
    configwind.title("configuraciones")
    label=Label(configwind,text="IP").pack()
    ent1=Entry(configwind)
    ent1.pack()
    label=Label(configwind,text="PORT").pack()
    ent2=Entry(configwind)
    ent2.pack()
    butt=Button(configwind,text="Configurar",command=accept)
    butt.pack()
def on_key_event(event):
    print('you pressed %s' % event.key)
    key_press_handler(event, canvas, toolbar)





#--------------------Inicializacion-------------

root =Tk()
root.title("Banco de Motores")
root.configure(bg="#484848")
#---------------------Menu superior------------
menubar=Menu(root,relief="flat",bg="#303030",fg="#ffffff")
filemenu = Menu(menubar, tearoff=0)
filemenu.add_command(label="Nuevo")
filemenu.add_command(label="Guardar")
menubar.add_cascade(label="Archivo", menu=filemenu)
filemenu = Menu(menubar, tearoff=0)
filemenu.add_command(label="Configuracion",command= config)
menubar.add_cascade(label="Opciones", menu=filemenu)
filemenu = Menu(menubar, tearoff=0)
filemenu.add_command(label="Informacion")
menubar.add_cascade(label="Ayuda", menu=filemenu)
root.config(menu=menubar)

f = Figure(figsize=(10, 4), dpi=100)
a = f.add_subplot(111)
a.set_xlabel('Tiempo[S] ')
a.set_ylabel(u'Fuerza[N]')

#-----------------------titulos---------------------
#tittle=Label(root,text="Parametros")
#tittle.grid(column=0,row=0)
#tittle2=Label(root,text="Grafica")
#tittle2.grid(column=1,row=0)

#:---------------------Paneles----------------------
panelg=Frame(root)
panelg.pack(side="top",expand=1,fill="both")
panel1=LabelFrame(panelg,text="Medidas principales",bg="#696969",fg="#ffffff")
panel1.pack(side="left",fill="both")
panel2=LabelFrame(panelg,text="Graficos",bg="#696969",fg="#ffffff")
panel2.pack(side="right",fill="y")
panel3=LabelFrame(root,text="Controles",bg="#303030",fg="#ffffff")
panel3.pack(side="bottom",fill="x")
#----------------------Canvas-----------------------
canvas = FigureCanvasTkAgg(f, master=panel2)
canvas.draw()
canvas.get_tk_widget().pack(side=TOP, fill=BOTH, expand=1)

toolbar = NavigationToolbar2TkAgg(canvas, panel2)
toolbar.update()
canvas._tkcanvas.pack(side=TOP, fill=BOTH, expand=1)

canvas.mpl_connect('key_press_event', on_key_event)
#---------------------Botones----------------------
button = Button(panel3, text='Salir', command=_quit,width=10,height=2,bg="#d3df00")
button.grid(column=2,row=0,sticky="e")
inis= Button(panel3,text="Iniciar",width=10,height=2,command=start,bg="#3fc900")
inis.grid(column=0,row=0,sticky="w")
stopb= Button(panel3,text="Parar",width=10,height=2,command=stop,state=DISABLED,bg="#c90000")
stopb.grid(column=1,row=0,sticky="w")

#--------------------- Panel 1---------------------
lab1=Label(panel1,text="Tiempo de prueba",font=("Courier", 20),bg="#696969",fg="#ffffff")
lab1.grid(column=0,row=0,columnspan=2)
cron=Label(panel1,text="00:00:00",font=("Courier", 44),bg="#696969",fg="#ffffff")
cron.grid(column=0,row=1,columnspan=2)
lab1=Label(panel1,text="Fuerza maxima: ",bg="#696969",fg="#ffffff")
lab1.grid(column=0,row=2)
labelf=Label(panel1,text="000 N",width=30,bg="#696969",fg="#ffffff")
labelf.grid(column=1,row=2)
t = threading.Thread(target=cronometro)
t.start()
t2 = threading.Thread(target=graficar)
t2.start()
root.mainloop()
