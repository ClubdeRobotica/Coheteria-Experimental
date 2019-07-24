import socket

import socket

class com_lan:
	def __init__(self,Host,PORT):

		self.obj = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		self.obj.connect((Host,PORT))

	def datos(self):
		return self.obj.recv(1024)
	def respond(self):
		self.obj.send("ok")

	def __del__(self):
		self.obj.close()
 
    

