#include <LiquidCrystal.h>  // libreria LCD
#include "TimerOne.h" //libreria para manejar interrupciones temporales

LiquidCrystal lcd(12,11, 6, 5, 4, 3); // pines para configurar el LCD

int pinInterrupcion = 0;     // uso del pin de interrupción externa 0 = pin digital 2     
long pulsos = 0;  // variable para contar los pulsos
int resolucion = 64;  // resolución del encoder número de pulsos por revolución
double rpm; // variable para almacenar el calculo de la velocidad rpm
 

void deteccion(){  // función que se ejecuta cuando hay interrupción externa
  pulsos++; // se incrementa la variable pulso en uno.
}
 
void segundo () {  // función que se ejecuta cuando se cumple el tiempo de interrupcíón temporal
  
 rpm=((double)pulsos/resolucion)*60; // calculo de velocidad rpm
 pulsos=0; // pulsos
}
 
void setup() {  

  lcd.begin(16,2); //  se inicia el LCD
  Serial.begin(9600);// se inicia la comunicación serial
   
  Timer1.initialize(1000000);  // cada 1 segundo se ejecuta la interrupción     
  Timer1.attachInterrupt(segundo);//se establece función de interrupción
 
  attachInterrupt(pinInterrupcion, deteccion, RISING);// se programa un interrupción externa, cada que hay un cambio de bajo a alto
  

  
}
void loop() {
          
   Serial.println(rpm); // se envia via serial la variable rpm
   lcd.setCursor(0,0); // se va a la posición (0,0) en la LCD
   lcd.write("rpm:"); // se escribe un texto
   lcd.setCursor(5,0); // se va a la posición (5,0) en la LCD
   lcd.write(rpm); // se escribe la variable rpm
 
 
}
