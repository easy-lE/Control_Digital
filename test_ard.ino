#include <TimerOne.h>

float SetP;                      //Setpoint. 
float yt;                        //Retroalimentación (Temperatura actual)
volatile float e1t, e2t,e3t;     //error actual y anterior
int uk;                          //Salida(pwm)
float kp, ki, kd;                   //Constantes ki y kp
float T=0.1;                   // tiempo de muestreo



void setup(){
  Timer1.initialize(100);                //Ancho de pulso (ms)
  Timer1.attachInterrupt(control);       //Activa la interrupción
  Serial.begin(9600);
}

void control()
{
  SetP=analogRead(0);             //Setpoint en A0

  yt=analogRead(1);               //Sensor retroalimentacion A1 
  yt=yt*500/1024;                 //transformación a mV 
  SetP=SetP*500/1024;             //Transformacion setpoint a grados
  e3t=e2t;                        //calculo de error anterior
  e2t=e1t;
  e1t=SetP-yt;                   //calcular error
  
 
  kp=4.97*e1t;                      //cONSTANTES I,P,D
  ki=0.073183*e2t;
  kd=84.6*e3t; 

  
  uk=kp+ki+kd;               //Salida del sistema PID
 
}
void loop(){
  if(uk>255);                   //
  if(uk<-255);
  if(e1t>0){                          //Si error actual es mayor a 0 se calienta horno (PIN 11)
    analogWrite(11,uk);
    analogWrite(10,LOW);                  //Calentar
    //
  }
if (e1t<0){                           //Enfriar si error actual es menor que 0   (PIN 10)
  analogWrite(11,LOW);
  analogWrite(10,HIGH);
  //
  }
}
