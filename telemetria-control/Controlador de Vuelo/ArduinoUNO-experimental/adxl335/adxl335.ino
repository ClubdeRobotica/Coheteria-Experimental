// Los tiempos de conversion del ADC estan entre 13 - 260μs, exactitud de +-2LSB y 10 bits de resolucion.
// El acelerometro (ADXL335) tiene una alimentacion entre 1.8 y 3.6V, mide un rango de +-3g sus capacitores de salida
// determinan un rango de frecuencias de 0.5Hz a 1600Hz para los ejes X e Y y 0.5Hz a 550Hz para el eje Z para rangos de 
// temperaturas de -40°C a 85°C


#include <avr/io.h>


#define CLEAN_ADMUX()        ADMUX &=~0x0F

void CanalADCSelect(uint8_t canal);
void LeerADC (uint8_t canal, uint16_t *destino);
void adc_ini();
void adc_lec(uint16_t *xyz);
void LeerTresEjes(uint16_t *destino);

void setup() {
  Serial.begin(9600);
  DDRB |= (1<<PB5);                               //PB5 digital 13 is an output
  adc_ini();                     

}

void loop() {
  uint16_t xyz[3], toggle = 0;          //variable global donde se guardan los valores de los acelerometros
  float m;    
  while(1){
  
    //adc_lec(xyz);                       //leo los adc0, adc1 y adc2
      
    LeerTresEjes(xyz);
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
//    if(m > 900){
//      PORTB |= (1<<PB5);                        
//    }
//    else {
//      PORTB &= ~(1<<PB5);                       
//    }
  }
}

void adc_ini(){
  ADCSRA |= ((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));     //Prescaler at 128 so we have an 125Khz clock source 
  ADMUX &= ~((1<<REFS1)|(1<<REFS0));                //AREF, Internal Vref turned off
  ADCSRB &= ~((1<<ADTS2)|(1<<ADTS1)|(1<<ADTS0));    //ADC in free-running mode
  ADCSRA |= ((1<<ADATE | (1<<ADEN)));               //Signal source, in this case is the free-running | Power up the ADC                      
  ADCSRA |= (1<<ADSC);                              //Start converting 
}


/*
 * CanalADCSelect:
 *  Cotrola el multiplexor del ADC
 * parametros:
 *      canal   El canal del ADC que se quiere seleccionar
 */

void CanalADCSelect(uint8_t canal){
    CLEAN_ADMUX();                                  //se limpia el mux, es una macro (ADMUX &=~0x0F;)
    ADMUX |= canal;                     
    delayMicroseconds(260);
}


/*
 * LeerADC:
 *  Lee el canal del adc seleccionado y lo guarda en la variable destino
 * parametros:
 *      canal:   El canal del adc que se quiere leer.
 *      destino: La variable donde se va a guardar el resultado de la lectura
 * 
 */
void LeerADC (uint8_t canal, uint16_t *destino){
    CanalADCSelect(canal);
    *destino = ADCW;
}


/* LeerTresEjes
 * Lee directamente los tres ejes y los guarda en la variable destino,
 * parametros:
 *  destino   Un puntero a un array de tres elemntos donde se van a guardar los datos leidos
 */
void LeerTresEjes(uint16_t *destino){
  uint8_t i;
  for(i=0;i<3;i++){
    LeerADC(i, &destino[i]);
  }
}

/*
 * CalcularInclinacion(): Calcula la inclinacion del cohete con respecto al eje z,
 * parametros:
 *    offset:           Angulo de offset, para corregir una posible inclinacion del acelerometro dentro del cohete, se lo debe medir con el cohete en posicion vertical
 *    InclinacionDst    Puntero a una variable donde se guarda el angulo de inclinacion
 */
void CalcularInclinacion(uint8_t offset, uint16_t *InclincionDst){
  //Para hacer
}

/*
 * CalcularDireccionXY(): Calcula la direccion resultante de la aceleracion  en el plano XY
 * parametros:
 *      Ver que hace falta, tal vez un vector de referencia
 */
void CalcularDireccionXY(){
  //Para hacer
}

/*
 * PasarGaM_S():    Toma el valor medidio en G y lo convierte a m/s. 
 *    parametros:
 *    Gmodulo:    El valor medido en G
 *    *AcMS:      Puntero a la variable donde se guarda el valor de aceleracion
 */
void PasarGaM_S(){
  //Para hacer
}


void adc_lec(uint16_t *xyz){

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
