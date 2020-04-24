EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr User 9843 5906
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_Module:Arduino_UNO_R3 A1
U 1 1 5E88D4B5
P 5750 2050
F 0 "A1" H 5500 3100 50  0000 C CNN
F 1 "Arduino_UNO_R3" H 5250 3000 50  0000 C CNN
F 2 "Module:Arduino_UNO_R3" H 5750 2050 50  0001 C CIN
F 3 "https://www.arduino.cc/en/Main/arduinoBoardUno" H 5750 2050 50  0001 C CNN
	1    5750 2050
	-1   0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x04 J3
U 1 1 5E896121
P 8950 2300
F 0 "J3" H 9030 2246 50  0000 L CNN
F 1 "Conn_01x04" H 9030 2201 50  0001 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Horizontal" H 8950 2300 50  0001 C CNN
F 3 "~" H 8950 2300 50  0001 C CNN
	1    8950 2300
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 J1
U 1 1 5E898B2F
P 1350 2550
F 0 "J1" H 1350 2650 50  0000 C CNN
F 1 "Conexion bateria" H 1350 2350 50  0000 C CNN
F 2 "TerminalBlock_Altech:Altech_AK300_1x02_P5.00mm_45-Degree" H 1350 2550 50  0001 C CNN
F 3 "~" H 1350 2550 50  0001 C CNN
	1    1350 2550
	-1   0    0    1   
$EndComp
$Comp
L Device:Battery_Cell BT1
U 1 1 5E899902
P 1000 2550
F 0 "BT1" H 750 2650 50  0000 L CNN
F 1 "12V" H 750 2550 50  0000 L CNN
F 2 "" V 1000 2610 50  0001 C CNN
F 3 "~" V 1000 2610 50  0001 C CNN
	1    1000 2550
	1    0    0    -1  
$EndComp
$Comp
L Relay:FINDER-32.21-x000 K1
U 1 1 5E8A391F
P 3900 2450
F 0 "K1" H 4400 2300 50  0000 C CNN
F 1 "Rele 12V-360mW" H 4450 2200 50  0000 C CNN
F 2 "Relay_THT:Relay_HF7FD" H 5170 2420 50  0001 C CNN
F 3 "https://gfinder.findernet.com/assets/Series/355/S32EN.pdf" H 3900 2450 50  0001 C CNN
	1    3900 2450
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N4007 D2
U 1 1 5E8AB676
P 3250 2450
F 0 "D2" V 3250 2250 50  0000 L CNN
F 1 "1N4007" V 3350 2150 50  0000 L CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 3250 2275 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 3250 2450 50  0001 C CNN
	1    3250 2450
	0    1    1    0   
$EndComp
$Comp
L Transistor_BJT:BC337 Q1
U 1 1 5E8AEEB1
P 3800 3100
F 0 "Q1" H 3991 3146 50  0000 L CNN
F 1 "BC337" H 3991 3055 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92L_Wide" H 4000 3025 50  0001 L CIN
F 3 "https://diotec.com/tl_files/diotec/files/pdf/datasheets/bc337.pdf" H 3800 3100 50  0001 L CNN
	1    3800 3100
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3700 2050 3250 2050
Wire Wire Line
	3700 2750 3700 2850
Wire Wire Line
	3250 2300 3250 2050
Wire Wire Line
	3250 2600 3250 2850
Wire Wire Line
	3250 2850 3700 2850
Connection ~ 3700 2850
Wire Wire Line
	3700 2850 3700 2900
Wire Wire Line
	3700 2050 3700 2150
$Comp
L Connector:Screw_Terminal_01x03 J2
U 1 1 5E8BDE72
P 4100 1350
F 0 "J2" V 4200 1400 50  0000 R CNN
F 1 "Screw_Terminal_01x03" V 3973 1162 50  0001 R CNN
F 2 "TerminalBlock_Altech:Altech_AK300_1x03_P5.00mm_45-Degree" H 4100 1350 50  0001 C CNN
F 3 "~" H 4100 1350 50  0001 C CNN
	1    4100 1350
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4200 2150 4200 1550
Wire Wire Line
	7600 750  5550 750 
Wire Wire Line
	5550 750  5550 1050
Wire Wire Line
	1000 2650 1000 2800
Wire Wire Line
	1000 2800 1650 2800
Wire Wire Line
	1000 2350 1000 2050
$Comp
L Device:LED D1
U 1 1 5E8E1758
P 2600 2300
F 0 "D1" V 2547 2378 50  0000 L CNN
F 1 "LED" V 2638 2378 50  0000 L CNN
F 2 "LED_THT:LED_D5.0mm" H 2600 2300 50  0001 C CNN
F 3 "~" H 2600 2300 50  0001 C CNN
	1    2600 2300
	0    1    1    0   
$EndComp
Connection ~ 3250 2050
$Comp
L Device:R R1
U 1 1 5E8E8A55
P 2600 2650
F 0 "R1" H 2670 2696 50  0000 L CNN
F 1 "560" H 2670 2605 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 2530 2650 50  0001 C CNN
F 3 "~" H 2600 2650 50  0001 C CNN
	1    2600 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	2600 2150 2600 2050
Connection ~ 2600 2050
Wire Wire Line
	2600 2050 3250 2050
Wire Wire Line
	2600 2450 2600 2500
Wire Wire Line
	2600 2800 2600 2850
Wire Wire Line
	2600 2850 3250 2850
Connection ~ 3250 2850
NoConn ~ 5250 1450
NoConn ~ 5250 1650
NoConn ~ 5250 1850
NoConn ~ 5650 1050
NoConn ~ 5850 1050
NoConn ~ 6250 1850
NoConn ~ 6250 1950
NoConn ~ 6250 2050
NoConn ~ 6250 2150
NoConn ~ 6250 2350
NoConn ~ 6250 2550
NoConn ~ 6250 2650
NoConn ~ 6250 2750
NoConn ~ 6250 2450
NoConn ~ 5650 3150
NoConn ~ 5750 3150
NoConn ~ 5250 2850
NoConn ~ 5250 2750
NoConn ~ 5250 2550
NoConn ~ 5250 2450
NoConn ~ 5250 2350
NoConn ~ 5250 2250
NoConn ~ 5250 2150
$Comp
L power:GND #PWR0101
U 1 1 5E8C641D
P 1000 3100
F 0 "#PWR0101" H 1000 2850 50  0001 C CNN
F 1 "GND" H 1005 2927 50  0000 C CNN
F 2 "" H 1000 3100 50  0001 C CNN
F 3 "" H 1000 3100 50  0001 C CNN
	1    1000 3100
	1    0    0    -1  
$EndComp
$Comp
L power:+12V #PWR0102
U 1 1 5E8C81F6
P 1000 1900
F 0 "#PWR0102" H 1000 1750 50  0001 C CNN
F 1 "+12V" H 1015 2073 50  0000 C CNN
F 2 "" H 1000 1900 50  0001 C CNN
F 3 "" H 1000 1900 50  0001 C CNN
	1    1000 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	1000 1900 1000 2050
Connection ~ 1000 2050
Wire Wire Line
	1000 2800 1000 3100
Connection ~ 1000 2800
Wire Wire Line
	4000 1550 4000 2150
Wire Wire Line
	4100 2750 4400 2750
Wire Wire Line
	4400 2750 4400 1750
Wire Wire Line
	4400 1750 4100 1750
Wire Wire Line
	4100 1750 4100 1550
$Comp
L Connector_Generic:Conn_01x02 J4
U 1 1 5E8DE260
P 2000 2450
F 0 "J4" H 1950 2550 50  0000 L CNN
F 1 "Alimentacion Arduino" H 1700 2250 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 2000 2450 50  0001 C CNN
F 3 "~" H 2000 2450 50  0001 C CNN
	1    2000 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	1000 2050 1650 2050
Wire Wire Line
	1550 2550 1650 2550
Wire Wire Line
	1650 2550 1650 2800
Connection ~ 1650 2800
Wire Wire Line
	1550 2450 1650 2450
Wire Wire Line
	1650 2450 1650 2050
Connection ~ 1650 2050
Wire Wire Line
	1650 2050 2600 2050
Wire Wire Line
	1800 2450 1650 2450
Connection ~ 1650 2450
Wire Wire Line
	1800 2550 1650 2550
Connection ~ 1650 2550
Wire Wire Line
	1650 2800 2200 2800
Text Label 8250 2300 0    50   ~ 0
SCK
Text Label 8250 2400 0    50   ~ 0
DT
Text Label 8250 2200 0    50   ~ 0
+5V
Text Label 8250 2500 0    50   ~ 0
GND
Wire Wire Line
	6600 2300 8750 2300
Wire Wire Line
	6500 2400 8750 2400
Wire Wire Line
	7600 750  7600 2200
Wire Wire Line
	7600 2200 8750 2200
Wire Wire Line
	7600 2500 8750 2500
Wire Wire Line
	6500 1650 6250 1650
Wire Wire Line
	6500 1650 6500 2400
Wire Wire Line
	6250 1750 6600 1750
Wire Wire Line
	6600 1750 6600 2300
NoConn ~ 6250 1450
NoConn ~ 6250 1550
Wire Wire Line
	6350 2250 6250 2250
$Comp
L Device:R R2
U 1 1 5E9BED75
P 4500 3100
F 0 "R2" V 4350 3200 50  0000 L CNN
F 1 "10k" V 4450 3200 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 4430 3100 50  0001 C CNN
F 3 "~" H 4500 3100 50  0001 C CNN
	1    4500 3100
	0    1    1    0   
$EndComp
Wire Wire Line
	4350 3100 4150 3100
$Comp
L Device:R R3
U 1 1 5EA24D64
P 4150 3300
F 0 "R3" H 4050 3250 50  0000 C CNN
F 1 "10k" H 4050 3350 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 4080 3300 50  0001 C CNN
F 3 "~" H 4150 3300 50  0001 C CNN
	1    4150 3300
	-1   0    0    1   
$EndComp
Wire Wire Line
	4650 3100 4950 3100
Wire Wire Line
	4950 3100 4950 3200
Wire Wire Line
	4950 3200 6350 3200
Wire Wire Line
	6350 3200 6350 2250
$Comp
L Device:CP C1
U 1 1 5EA27D46
P 4150 3700
F 0 "C1" H 4268 3746 50  0000 L CNN
F 1 "100uf" H 4268 3655 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D6.3mm_P2.50mm" H 4188 3550 50  0001 C CNN
F 3 "~" H 4150 3700 50  0001 C CNN
	1    4150 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4150 3850 5850 3850
Wire Wire Line
	7600 2500 7600 3850
Wire Wire Line
	5850 3150 5850 3850
Connection ~ 5850 3850
Wire Wire Line
	5850 3850 7600 3850
Wire Wire Line
	4150 3150 4150 3100
Connection ~ 4150 3100
Wire Wire Line
	4150 3100 4000 3100
Wire Wire Line
	4150 3450 4150 3550
Wire Wire Line
	2200 3850 3700 3850
Wire Wire Line
	2200 2800 2200 3850
Connection ~ 4150 3850
Wire Wire Line
	3700 3300 3700 3850
Connection ~ 3700 3850
Wire Wire Line
	3700 3850 4150 3850
$EndSCHEMATC
