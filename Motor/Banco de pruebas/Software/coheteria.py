import matplotlib
matplotlib.use('TkAgg')
from matplotlib import style
style.use('ggplot')
import matplotlib.animation as animation
from numpy import arange, sin, pi
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2TkAgg
from matplotlib.backend_bases import key_press_handler
from matplotlib.figure import Figure
from Tkinter import *
import sys
from time import *
import threading
from tkinter import messagebox