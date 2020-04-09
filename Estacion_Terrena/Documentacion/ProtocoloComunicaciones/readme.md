Pongo acá algo de info sobre los protocolos de comunicaciones que ya existen, a ver si podemos adoptar directamente uno que ya esté bien pulido

## MIL-STD-1553

Es el protocolo mas común es el y fue diseñado para su uso en aviación militar, pero ha terminado por utilizarse habitualmente en subsistemas embarcados de manejo de datos en vehículos espaciales, tanto militares como civiles. Proporciona una interfaz física de línea balanceada dual, una interfaz de red diferencial, multiplexación por división en el tiempo, protocolo de comando/respuesta half-duplex y hasta 31 terminales remotos. Una versión de MIL-STD-1553, que utiliza cableado óptico en lugar de eléctrico, es conocida como MIL-STD-1773.

El controlador maestro se encarga del control de toda comunicación en el bus, cualquier emisión o recepción se basa en un comando del maestro a un terminal. Por su parte las terminales se distinguen por una dirección (0 ~ 31) y a su vez cada terminal podría recibir datos ó entregar datos desde diferentes áreas de memoria. Cada área diferente de memoria dentro de un mismo terminal se identifica con un valor de 5 bits llamado subdirección (1~30) (los valores 0 y 31 quedan reservados para transacciones de tipo Mode Code).

La secuencia de palabras (la forma de la notación es <origen>.<tipo_de_palabra(destino)> y es una notación similar a la de los CSP), para la transferencia de datos del controlador maestro a un terminal es

    master.command(terminal) → terminal.status(master) → master.data(terminal) → master.command(terminal) → terminal.status(master)

y para comunicación de entre terminales es

    master.command(terminal_1) → terminal_1.status(master) → master.command(terminal_2) → terminal_2.status(master) → master.command(terminal_1) → terminal_1.data(terminal_2) → master.command(terminal_2) → terminal_2.status(master) 

[Fuente](https://es.wikipedia.org/wiki/MIL-STD-1553#Protocolo_de_bus "Wikipedia")


## SpaceWire
Fue desarrollado por la ESA y poco a poco se ha ido convirtiendo en el mas popular. Fue desarrollado específicamente para aplicaciones aeroespaciales. La norma define todo, y hay varias implementaciones libres en VHDL [ [1](http://publications.lib.chalmers.se/records/fulltext/157904.pdf) ] y C++[ [2](https://github.com/yuasatakayuki/SpaceWireRMAPLibrary) ]. Para mas info sobre el protocolo acá encontré un [Manual de Usuario](https://www.star-dundee.com/sites/default/files/SpaceWire%20User%27s%20Guide.pdf) y en la [Página Oficial](http://spacewire.esa.int/content/Home/HomeIntro.php) hay un montón de info para leer.

## CAN Bus
Otro bastante sencillo y que se puede adoptar facilmente es el protocolo CAN, el estandar define dos tipos de tramas para el envío de datos y es facil de adoptar:
Una trama de datos CAN puede ser de uno de los dos siguientes formatos:

* Formato base: con identificador de 11 bits.
* Formato extendido: con identificador de 29 bits.

El estándar define tambien varios tipos de tramas según sea el estado del dispositivo. Mas info:
* [Wikipedia](https://es.wikipedia.org/wiki/Bus_CAN#Tipos_de_trama)
* [Protocolo de comunicaciones CAN aplicado a sistemas satelitales y vehículos lanzadores](http://sedici.unlp.edu.ar/bitstream/handle/10915/21218/Documento_completo.pdf?sequence=1)
* [Un proyecto para implementar CAN en C](https://github.com/linux-can/can-utils)

## Otros Protocolos
Para aplicaciones menores, suelen usarse protocolos mas simples, encontré los protocolos ANSI/TIA/EIA-422-B y TIA/EIA-485-A basados en los buses rs422 y 485, pero no encontré mucha info sobre la aplicación.