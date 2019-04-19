import json
archivo=open('ej_json.json')
data=json.load(archivo)
tiempo=data["Tiempo"]
print tiempo
for sensores in data["Sensores"]:
	print sensores["name"],sensores["value"]