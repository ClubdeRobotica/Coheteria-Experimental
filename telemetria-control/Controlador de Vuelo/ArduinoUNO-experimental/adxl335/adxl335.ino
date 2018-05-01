// Los tiempos de conversion del ADC estan entre 13 - 260μs, exactitud de +-2LSB y 10 bits de resolucion.
// El acelerometro (ADXL335) tiene una alimentacion entre 1.8 y 3.6V, mide un rango de +-3g sus capacitores de salida
// determinan un rango de frecuencias de 0.5Hz a 1600Hz para los ejes X e Y y 0.5Hz a 550Hz para el eje Z para rangos de 
// temperaturas de -40°C a 85°C


#include <avr/io.h>

void adc_ini(void);  //inicializacion del adc
void adc_lec(void);  //funcion que lee los tres ejes del sensor y los guarda en una variable global
int xyz[3];          //variable global donde se guardan los valores de los acelerometros

void setup() {
  Serial.begin(9600);
  DDRB |= (1<<PB5);                               //PB5 digital 13 is an output
  adc_ini();                                      

}

void loop() {
  float m;    
  while(1){

    adc_lec();                       //leo los adc0, adc1 y adc2

    //imprimo el valor leido en cada adc    
    Serial.print(xyz[0]);
    Serial.print("\t");
    Serial.print(xyz[1]);
    Serial.print("\t");
    Serial.print(xyz[2]);
    Serial.print("\t");  


    //calculo el modulo de los vectores y lo imprimo
    m=(float) xyz[0] * (float) xyz[0] + (float) xyz[1] * (float) xyz[1] +(float) xyz[2] * (float) xyz[2];
    m=sqrt(m);
    Serial.print(m);
    Serial.print("\n");
 
    //si el modulo supera cierto valor prendo el led, si esta por debajo lo apago 
    if(m > 900){
      PORTB |= (1<<PB5);                        
    }
    else {
      PORTB &= ~(1<<PB5);                       
    }
    
    
  }
}

void adc_ini(){
  ADCSRA |= ((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));     //Prescaler at 128 so we have an 125Khz clock source 
  ADMUX &= ~((1<<REFS1)|(1<<REFS0));                //AREF, Internal Vref turned off
  ADCSRB &= ~((1<<ADTS2)|(1<<ADTS1)|(1<<ADTS0));    //ADC in free-running mode
  ADCSRA |= ((1<<ADATE | (1<<ADEN)));               //Signal source, in this case is the free-running | Power up the ADC                      
  ADCSRA |= (1<<ADSC);                              //Start converting 
}

void adc_lec(){

      ADMUX &=~((1<<MUX3)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0));     //se direcciona al ADC0         
      delayMicroseconds(260);                                 //el delay tiene que durar 260μs que es el maximo tiempo de conversion del adc del arduino 1
      xyz[0]=ADCW;                                            //se lee el registro donde se guarda el valor convertido
      
      ADMUX &=~((1<<MUX3)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0));     //se direcciona al ADC1
      ADMUX |= ((1<<MUX0));                     
      delayMicroseconds(260);
      xyz[1]=ADCW;
      
      ADMUX &=~((1<<MUX3)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0));     //se direcciona al ADC2
      ADMUX |= ((1<<MUX1));                     
      delayMicroseconds(260);
      xyz[2]=ADCW;       
      
}


