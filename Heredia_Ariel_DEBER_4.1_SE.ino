/*
 * CAPITULO IV: PERIFÉRICOS ESPECIALES
 * DEBER 4.1: CAD Y PWM
 * NOMBRE: Ariel Heredia
 * OBJETIVO: Realizar lecturas del conversr analógico digital
 * para determinar la velocidad de un motor en DC
 * Funciones: analogrRead(Conversor)
 *            conversor -> A0-A5
 *            analogWrite(pin,duty)
 *            pin-> pines con ~, duty -> 0-255
 */

#include <LiquidCrystal.h>                          //Llamo a la librería
LiquidCrystal lcd1(13,12,A2,A3,A4,A5);              //Pines de LCD para el motor 1
LiquidCrystal lcd2(1,0,11,10,9,8);                  //Pines de LCD para el motor 2  
int conversor1, conversor2;                         //Variable para adquirir los datos de los pines analógicos A0-A1
int sw = 2;                                         //variable de entrada digital 
int btn = 3;                                        //variable de entrada digital 
float voltaje1, voltaje2;                           //Variable de conversion de voltajes obtenidos de ambos ADC
int duty1, duty2;                                   //Variable para el uso del PWM

void setup() {
  lcd1.begin(16,2);                                 //Inicializa LCD1
  lcd2.begin(16,2);                                 //Inicializa LCD2
  pinMode(sw,INPUT);                                //Pin 2 configurado como entrada
  pinMode(btn,INPUT);                               //Pin 3 configurado como entrada
}

void loop() {
  if(digitalRead(sw)==HIGH){                        //Condición de activación en ALTO
    conversor1=analogRead(A0);                      //Lectura del canal análogo A0 - puede ser 0 o 14
    voltaje1=(conversor1*5.0)/1023.0;               //Conversión del voltaje
    duty1=conversor1/4;                             //Cambio de escala para el ciclo de la variable duty1  
    analogWrite(5,duty1);                           //Envío del valor al pin 5 análogo
    imprimirLCD1();                                 //Llama a la rutina para imprimir en LCD
  }else{
    lcd1.clear();
    analogWrite(5,0);                               //Envío del valor nulo al pin 5 análogo
  }

  if(digitalRead(btn)==HIGH){                       //Condición de activación en ALTO
    //delay(200);
    
    conversor2=analogRead(A1);                      //Lectura del canal análogo A1 
    voltaje2=(conversor2*5.0)/1023.0;               //Conversión del voltaje
    duty2=conversor2/4;                             //Cambio de escala para el ciclo de la variable duty2
    analogWrite(6,duty2);                           //Envío del valor al pin 6 análogo
    imprimirLCD2();                                 //Llama a la rutina para imprimir en LCD
  }else{
    lcd2.clear();  
    analogWrite(6,0);
  }
  
 
  
  delay(300);
}

void imprimirLCD1(){
  lcd1.setCursor(0,0);                              //Ubicación del cursor en la LCD
  lcd1.print("CAD: ");                              //Impresión del mensaje en la LCD
  lcd1.setCursor(6,0);
  lcd1.print(conversor1);
  lcd1.setCursor(0,1);
  lcd1.print("V: ");
  lcd1.setCursor(4,1); 
  lcd1.print(voltaje1);
  lcd1.setCursor(9,1);
  lcd1.print("PWM: ");
  lcd1.setCursor(13,1);
  lcd1.print((duty1*100)/255);                      //Ajuste de valor en porcentaje   
}
void imprimirLCD2(){
  lcd2.setCursor(0,0);                              //Ubicación del cursor en la LCD
  lcd2.print("CAD: ");                              //Impresión del mensaje en la LCD
  lcd2.setCursor(6,0);
  lcd2.print(conversor2);
  lcd2.setCursor(0,1);
  lcd2.print("V: ");
  lcd2.setCursor(4,1); 
  lcd2.print(voltaje2);
  lcd2.setCursor(9,1);
  lcd2.print("PWM: ");
  lcd2.setCursor(13,1);
  lcd2.print((duty2*100)/255);                      //Ajuste de valor en porcentaje   
}
