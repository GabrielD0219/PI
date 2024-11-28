/*TB6612FNG-Dual-Driver  //RECEPTOR - ARDUINO NANO RF - CONTROL1 ARMADO
*/

#include <RF24.h>
#include <RF24_config.h>
#include <nRF24L01.h>
#include <printf.h>
#include <SPI.h>

const int CE = 10;
const int CSN = 9;

#define PWM1 3 //PWM MOTOR 1 (IZQUIERDA)
#define AIN1 2
#define AIN2 4
#define PWM2 5 //PWM MOTOR 2 (DERECHA)
#define BIN1 7
#define BIN2 8

RF24 radio (CE,CSN);
const uint64_t canal = 0x6E6E6ELL;

int datos[3];
int xx = 0;
int yy = 0;
int boton = 0;
int variable_pwm = 0;


void setup() {
  Serial.begin(9600);

  radio.begin();
  radio.openReadingPipe(1, canal); // Dirección del transmisor
  radio.startListening();

  pinMode(PWM1,OUTPUT);
  pinMode(AIN1,OUTPUT);
  pinMode(AIN2,OUTPUT);
  pinMode(PWM2,OUTPUT);
  pinMode(BIN1,OUTPUT);
  pinMode(BIN2,OUTPUT);
  pinMode(6, OUTPUT);
  
}
 
void loop() {
  //control_robot(200);
  if(radio.available()){
    radio.read(datos,sizeof(datos));
    xx=datos[0];
    yy=datos[1];
    boton=datos[2];

    control_robot(200);

    Serial.print("X: " );
    Serial.print(xx);
    Serial.print(" Y: " );
    Serial.print(yy);
    Serial.print(" Boton: " );
    Serial.println(boton);
  }
    
}

void control_robot(int variable_pwm){
 //Moverse hacia aDELANTE
 if(yy<505){
   digitalWrite(AIN1,HIGH); //Motor A Rotate Clockwise
   digitalWrite(AIN2,LOW);
   digitalWrite(BIN1,HIGH); //Motor B Rotate Clockwise
   digitalWrite(BIN2,LOW);
   analogWrite(PWM1,variable_pwm); //Speed control of Motor A
   analogWrite(PWM2,variable_pwm); //Speed control of Motor B
   //delay(100);
 }

 //Moverse hacia atras
 if(yy>520){
   digitalWrite(AIN1,LOW); //Motor A Rotate Clockwise
   digitalWrite(AIN2,HIGH);
   digitalWrite(BIN1,LOW); //Motor B Rotate Clockwise
   digitalWrite(BIN2,HIGH);
   analogWrite(PWM1,variable_pwm); //Speed control of Motor A
   analogWrite(PWM2,variable_pwm); //Speed control of Motor B
   //delay(100);
 }

 //Moverse hacia la derecha
 if(xx>510){
   digitalWrite(AIN1,HIGH); //Motor A Rotate Clockwise
   digitalWrite(AIN2,LOW);
   digitalWrite(BIN1,LOW); //Motor B Rotate Clockwise
   digitalWrite(BIN2,HIGH);
   analogWrite(PWM1,variable_pwm); //Speed control of Motor A
   analogWrite(PWM2,variable_pwm); //Speed control of Motor B
   //delay(100);
 }

 //Moverse hacia la izquierda
 if(xx<495){
   digitalWrite(AIN1,LOW); //Motor A Rotate Clockwise
   digitalWrite(AIN2,HIGH);
   digitalWrite(BIN1,HIGH); //Motor B Rotate Clockwise
   digitalWrite(BIN2,LOW);
   analogWrite(PWM1,variable_pwm); //Speed control of Motor A
   analogWrite(PWM2,variable_pwm); //Speed control of Motor B
   //delay(100);
 }

//Detenerse
 if(xx>500 && xx<510 && yy>505 && yy<515){
   digitalWrite(AIN1,LOW); //Motor A Rotate Clockwise
   digitalWrite(AIN2,LOW);
   digitalWrite(BIN1,LOW); //Motor B Rotate Clockwise
   digitalWrite(BIN2,LOW);
   analogWrite(PWM1,variable_pwm); //Speed control of Motor A
   analogWrite(PWM2,variable_pwm); //Speed control of Motor B
   //delay(100);
 }

 //Sistema de pateo
 if(boton==1){
   digitalWrite(6,HIGH); //Activar solenoide
   delay(100);                       
   digitalWrite(6, LOW);    
   delay(100); 
  }

 delay(100);
}