from coheteria import *
from com import *
import json
std=0
stde=1

def graficar():
    global std
    global stde
    s=[]
    secc=[]
    while stde==1:
        if std==1:
            inter=str(banco_hard.datos())
            inter=json.loads(inter)
            s.append(inter['T'])
            secc.append(inter['grm'])
            a.cla()
            a.plot(secc,s)
            canvas.draw()
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
def on_key_event(event):
    print('you pressed %s' % event.key)
    key_press_handler(event, canvas, toolbar)
#---------------------comunicacion-------------
banco_hard=com_lan("localhost",8000)


#--------------------Inicializacion-------------
root =Tk()
root.title("Banco de Motores")
root.configure(bg="#484848")
#---------------------Menu superior------------
menubar=Menu(root,relief="flat",bg="#ffffff")
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
panel1=LabelFrame(panelg,text="Medidas principales")
panel1.pack(side="left",fill="both")
panel2=LabelFrame(panelg,text="Graficos")
panel2.pack(side="right",fill="y")
panel3=LabelFrame(root,text="Controles")
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
button = Button(panel3, text='Salir', command=_quit,width=10,height=2)
button.grid(column=2,row=0,sticky="e")
inis= Button(panel3,text="Iniciar",width=10,height=2,command=start)
inis.grid(column=0,row=0,sticky="w")
stopb= Button(panel3,text="Parar",width=10,height=2,command=stop,state=DISABLED)
stopb.grid(column=1,row=0,sticky="w")

#--------------------- Panel 1---------------------
lab1=Label(panel1,text="Tiempo de prueba",font=("Courier", 20))
lab1.grid(column=0,row=0,columnspan=2)
cron=Label(panel1,text="00:00:00",font=("Courier", 44))
cron.grid(column=0,row=1,columnspan=2)
lab1=Label(panel1,text="Fuerza maxima: ")
lab1.grid(column=0,row=2)
labelf=Label(panel1,text="000 N",width=30)
labelf.grid(column=1,row=2)
t = threading.Thread(target=cronometro)
t.start()
t2 = threading.Thread(target=graficar)
t2.start()
root.mainloop()
