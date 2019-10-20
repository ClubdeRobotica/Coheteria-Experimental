EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:switches
LIBS:relays
LIBS:motors
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:wemos_mini
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
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
L WeMos_mini U1
U 1 1 5DACB3F6
P 5250 2750
F 0 "U1" H 5250 3250 60  0000 C CNN
F 1 "WeMos_mini" H 5250 2250 60  0000 C CNN
F 2 "" H 5800 2050 60  0000 C CNN
F 3 "" H 5800 2050 60  0000 C CNN
	1    5250 2750
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x04 J1
U 1 1 5DACB519
P 1200 2400
F 0 "J1" H 1200 2600 50  0000 C CNN
F 1 "Conn_01x04" H 1200 2100 50  0000 C CNN
F 2 "" H 1200 2400 50  0001 C CNN
F 3 "" H 1200 2400 50  0001 C CNN
	1    1200 2400
	-1   0    0    -1  
$EndComp
Text GLabel 1900 2200 2    60   Input ~ 0
3v3
Text GLabel 1900 2350 2    60   Input ~ 0
GND
Text GLabel 1900 2650 2    60   Input ~ 0
SDA
Text GLabel 1900 2500 2    60   Input ~ 0
SCL
Text GLabel 6100 2400 2    60   Input ~ 0
3v3
Text GLabel 4550 2500 0    60   Input ~ 0
GND
Text GLabel 4550 2750 0    60   Input ~ 0
SDA
Text GLabel 4550 2900 0    60   Input ~ 0
SCL
Text GLabel 4200 2600 0    60   Input ~ 0
Buzzer
$Comp
L BC548 Q1
U 1 1 5DACFE2E
P 3000 4400
F 0 "Q1" H 3200 4475 50  0000 L CNN
F 1 "BC548" H 3200 4400 50  0000 L CNN
F 2 "TO_SOT_Packages_THT:TO-92_Molded_Narrow" H 3200 4325 50  0001 L CIN
F 3 "" H 3000 4400 50  0001 L CNN
	1    3000 4400
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 5DAD005C
P 2500 4400
F 0 "R1" V 2580 4400 50  0000 C CNN
F 1 "10k" V 2500 4400 50  0000 C CNN
F 2 "" V 2430 4400 50  0001 C CNN
F 3 "" H 2500 4400 50  0001 C CNN
	1    2500 4400
	0    1    1    0   
$EndComp
Text GLabel 2250 4400 0    60   Input ~ 0
Buzzer
$Comp
L +3.3V #PWR2
U 1 1 5DAD0E24
P 3100 3800
F 0 "#PWR2" H 3100 3650 50  0001 C CNN
F 1 "+3.3V" H 3100 3940 50  0000 C CNN
F 2 "" H 3100 3800 50  0001 C CNN
F 3 "" H 3100 3800 50  0001 C CNN
	1    3100 3800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR3
U 1 1 5DAD1024
P 3100 4750
F 0 "#PWR3" H 3100 4500 50  0001 C CNN
F 1 "GND" H 3100 4600 50  0000 C CNN
F 2 "" H 3100 4750 50  0001 C CNN
F 3 "" H 3100 4750 50  0001 C CNN
	1    3100 4750
	1    0    0    -1  
$EndComp
$Comp
L Buzzer BZ1
U 1 1 5DAD1C13
P 3250 4000
F 0 "BZ1" H 3400 4050 50  0000 L CNN
F 1 "Buzzer" H 3400 3950 50  0000 L CNN
F 2 "" V 3225 4100 50  0001 C CNN
F 3 "" V 3225 4100 50  0001 C CNN
	1    3250 4000
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR6
U 1 1 5DAD2EBD
P 5850 2300
F 0 "#PWR6" H 5850 2150 50  0001 C CNN
F 1 "+3.3V" H 5850 2440 50  0000 C CNN
F 2 "" H 5850 2300 50  0001 C CNN
F 3 "" H 5850 2300 50  0001 C CNN
	1    5850 2300
	1    0    0    -1  
$EndComp
Connection ~ 5850 2400
Wire Wire Line
	5850 2300 5850 2400
Wire Wire Line
	3100 4750 3100 4600
Wire Wire Line
	2650 4400 2800 4400
Wire Wire Line
	2250 4400 2350 4400
Wire Wire Line
	4200 2600 4750 2600
Wire Wire Line
	6100 2400 5750 2400
Wire Wire Line
	4600 2750 4550 2750
Wire Wire Line
	4600 2800 4600 2750
Wire Wire Line
	4750 2800 4600 2800
Wire Wire Line
	4550 2900 4750 2900
Wire Wire Line
	4550 2500 4750 2500
Wire Wire Line
	1650 2650 1900 2650
Wire Wire Line
	1650 2600 1650 2650
Wire Wire Line
	1400 2600 1650 2600
Wire Wire Line
	1400 2500 1900 2500
Wire Wire Line
	1650 2350 1900 2350
Wire Wire Line
	1650 2400 1650 2350
Wire Wire Line
	1400 2400 1700 2400
Wire Wire Line
	1600 2200 1900 2200
Wire Wire Line
	1600 2300 1600 2200
Wire Wire Line
	1400 2300 1600 2300
$Comp
L R R2
U 1 1 5DAD510F
P 2800 4000
F 0 "R2" V 2880 4000 50  0000 C CNN
F 1 "10k" V 2800 4000 50  0000 C CNN
F 2 "" V 2730 4000 50  0001 C CNN
F 3 "" H 2800 4000 50  0001 C CNN
	1    2800 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 3850 3100 3850
Wire Wire Line
	3100 3800 3100 3900
Wire Wire Line
	2800 4150 3100 4150
Wire Wire Line
	3100 4100 3100 4200
Wire Wire Line
	3150 4100 3100 4100
Connection ~ 3100 4150
Wire Wire Line
	3100 3900 3150 3900
Connection ~ 3100 3850
$Comp
L GND #PWR1
U 1 1 5DAD9B82
P 1700 2700
F 0 "#PWR1" H 1700 2450 50  0001 C CNN
F 1 "GND" H 1700 2550 50  0000 C CNN
F 2 "" H 1700 2700 50  0001 C CNN
F 3 "" H 1700 2700 50  0001 C CNN
	1    1700 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	1700 2400 1700 2700
Connection ~ 1650 2400
$Comp
L Battery_Cell BT1
U 1 1 5DADB579
P 4950 4300
F 0 "BT1" H 5050 4400 50  0000 L CNN
F 1 "Battery_Cell" H 5050 4300 50  0000 L CNN
F 2 "" V 4950 4360 50  0001 C CNN
F 3 "" V 4950 4360 50  0001 C CNN
	1    4950 4300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR5
U 1 1 5DADBA2F
P 4950 4500
F 0 "#PWR5" H 4950 4250 50  0001 C CNN
F 1 "GND" H 4950 4350 50  0000 C CNN
F 2 "" H 4950 4500 50  0001 C CNN
F 3 "" H 4950 4500 50  0001 C CNN
	1    4950 4500
	1    0    0    -1  
$EndComp
$Comp
L +3.3V #PWR4
U 1 1 5DADBE5D
P 4950 3950
F 0 "#PWR4" H 4950 3800 50  0001 C CNN
F 1 "+3.3V" H 4950 4090 50  0000 C CNN
F 2 "" H 4950 3950 50  0001 C CNN
F 3 "" H 4950 3950 50  0001 C CNN
	1    4950 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	4950 4100 4950 3950
Wire Wire Line
	4950 4500 4950 4400
$EndSCHEMATC
