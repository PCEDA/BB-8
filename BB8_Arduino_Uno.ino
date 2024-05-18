#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <Dabble.h>


//pines del motor A
int motorApin1 = 4;
int motorApin2 = 5;


//pines del motor B
int motorBpin1 = 6;
int motorBpin2 = 7;


float vel_max;
float velA;
float velB;


float p; //relación entre velocidades A y B
int estado; //casos posibles


enum estado{
  derecha_arriba,
  arriba,
  izquierda_arriba,
  izquierda,
  izquierda_abajo,
  abajo,
  derecha_abajo,
  derecha
};


void f_derecha_arriba(){
  velA=vel_max;
  velB=p/6*velA;
  digitalWrite(motorApin1, HIGH);
  digitalWrite(motorApin2, LOW);
  digitalWrite(motorBpin1, HIGH);
  digitalWrite(motorBpin2, LOW);
  //mismo sentido
}


void f_arriba(){
  velA=vel_max;
  velB=velA;
  digitalWrite(motorApin1, HIGH);
  digitalWrite(motorApin2, LOW);
  digitalWrite(motorBpin1, HIGH);
  digitalWrite(motorBpin2, LOW);
  //mismo sentido
}


void f_izquierda_arriba(){
  velB=vel_max;
  velA=p/6*velB;
  digitalWrite(motorApin1, HIGH);
  digitalWrite(motorApin2, LOW);
  digitalWrite(motorBpin1, HIGH);
  digitalWrite(motorBpin2, LOW);
  //sentidos contrarios
}


void f_izquierda(){
  velA=vel_max;
  velB=velA;
  digitalWrite(motorApin1, HIGH);
  digitalWrite(motorApin2, LOW);
  digitalWrite(motorBpin1, LOW);
  digitalWrite(motorBpin2, HIGH);
  //mismo sentido
}


void f_izquierda_abajo(){
  velA=vel_max;
  velB=p/6*velA;
  digitalWrite(motorApin1, LOW);
  digitalWrite(motorApin2, HIGH);
  digitalWrite(motorBpin1, LOW);
  digitalWrite(motorBpin2, HIGH);
  //sentidos contrarios
}


void f_abajo(){
  velA=vel_max;
  velB=velA;
  digitalWrite(motorApin1, LOW);
  digitalWrite(motorApin2, HIGH);
  digitalWrite(motorBpin1, LOW);
  digitalWrite(motorBpin2, HIGH);
  //mismo sentido
}


void f_derecha_abajo(){
  velB=vel_max;
  velA=p/6*velB;
  digitalWrite(motorApin1, LOW);
  digitalWrite(motorApin2, HIGH);
  digitalWrite(motorBpin1, LOW);
  digitalWrite(motorBpin2, HIGH);
  //sentidos contrarios
}


void f_derecha(){
  velA=vel_max;
  velB=velA;
  digitalWrite(motorApin1, LOW);
  digitalWrite(motorApin2, HIGH);
  digitalWrite(motorBpin1, HIGH);
  digitalWrite(motorBpin2, LOW);
  //mismo sentido
}


void setup() {
  pinMode(motorApin1, OUTPUT);
  pinMode(motorApin2, OUTPUT);
  pinMode(motorBpin1, OUTPUT);
  pinMode(motorBpin2, OUTPUT);


  pinMode(9,  OUTPUT);
  pinMode(10, OUTPUT);
  Serial.begin(9600);
  Dabble.begin(9600); //Recomendado 9600
}


void loop() {


//Obtención datos del joystick
Dabble.processInput();
  int a = GamePad.getAngle();
  int b = GamePad.getRadius();


//relación entre radio y velocidad(0-255)
vel_max=b*255/7;


//definimos velocidad de cada motor
analogWrite(9, velA); //ENA pin
analogWrite(10, velB); //ENB pin


switch(estado){
  case derecha_arriba:
  f_derecha_arriba();
  break;
 
  case arriba:
  f_arriba();
  break;
 
  case izquierda_arriba:
  f_izquierda_arriba();
  break;
 
  case izquierda:
  f_izquierda();
  break;


  case izquierda_abajo:
  f_izquierda_abajo();
  break;
 
  case abajo:
  f_abajo();
  break;


  case derecha_abajo:
  f_derecha_abajo();
  break;


  case derecha:
  f_derecha();
  break;
}
 
 if(0<a && a<90){
  estado=derecha_arriba;}


if(a==90){
  estado=arriba;}


if(90<a && a<180){
  estado=izquierda_arriba;}


if(a==180){
  estado=izquierda;}
 
if(180<a && a<270){
  estado=izquierda_abajo;}
 
if(a==270){
  estado=abajo;}


if(270<a && a<360){
  estado=derecha_abajo;}


if(a==0){
  estado=derecha;}


if(a==15 || a==165 || a==195 || a==345){
  p=1;}


if(a==30 || a==150 || a==210 || a==330){
  p=2;}
 
if(a==45 || a==135 || a==225 || a==315){
  p=3;}


if(a==60 || a==120 || a==240 || a==300){
  p=4;}


if(a==75 || a==105 || a==255 || a==285){
  p=5;}


}
