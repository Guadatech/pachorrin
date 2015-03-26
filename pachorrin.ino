  
#include <Servo.h> 
#include <Ultrasonic.h>

#define POS_INICIAL_SERVO_1  75
#define POS_INICIAL_SERVO_3  90
#define POS_INICIAL_SERVO_2  90
#define POS_INICIAL_SERVO_4  90

#define PAUSA 500
#define RANGO_MOVIMIENTO 20

enum acciones {INICIO,AVANCE, ATRAS} ;

Servo myservo1;  
Servo myservo2;
Servo myservo3;  
Servo myservo4;


int val = 60;
int retardoMovimiento = 200;
float mediaUltrasonidos();
Ultrasonic ultrasonic(9,8);
 
float mediaUltrasonidos(){
  /* Tomo cinco medidas del ultrasonidos y me quedo con la media */
 
 int total = 0;
 
 for (int i = 0; i < 5; i++)
   total += ultrasonic.Ranging(CM); 
   
 float media = (float)total/(float)5;
 // Quitando mediciones parasitas
 if (media < 1)
   media = 50;
   
 return media;
   
 }
 
void posicionInicial(){
  myservo3.write(POS_INICIAL_SERVO_3);
  delay(retardoMovimiento);
  myservo4.write(POS_INICIAL_SERVO_4);
  delay(retardoMovimiento);     
  myservo1.write(POS_INICIAL_SERVO_1);
  delay(retardoMovimiento);
  myservo2.write(POS_INICIAL_SERVO_2);
  delay(retardoMovimiento);
}

void accion(int numAccion,  int numServo){
  Servo servoAmover;
  int  POS_INICIAL_SERVO;
  switch(numServo)
  {
    case 1:
      servoAmover = myservo1;
      POS_INICIAL_SERVO = POS_INICIAL_SERVO_1;
      break;
    case 2:
      servoAmover = myservo2;
      POS_INICIAL_SERVO = POS_INICIAL_SERVO_2;
      break;
    case 3:
      servoAmover = myservo3;
      POS_INICIAL_SERVO = POS_INICIAL_SERVO_3;
      break;
    case 4:
      servoAmover = myservo4;
      POS_INICIAL_SERVO = POS_INICIAL_SERVO_4;
      break; 
    default:
      break;  
  }
  int multiplicador = 1;
  
  // Los servos enfrentados de las patas, tienen que ir en sentido contrario
  if (numServo == 1 || numServo == 3)
    multiplicador = -1;
  
  switch(numAccion)
      {
        case INICIO:
          servoAmover.write(POS_INICIAL_SERVO);
          break;  
        case AVANCE:
          servoAmover.write(POS_INICIAL_SERVO + (multiplicador * RANGO_MOVIMIENTO));
          break; 
        case ATRAS:
          servoAmover.write(POS_INICIAL_SERVO - (multiplicador * RANGO_MOVIMIENTO));
          break;    
        default:
        
          break;
      }
  delay(retardoMovimiento);
}

void andurriaBasica(){
  accion(AVANCE,3);
  accion(AVANCE,4);

}

void flexiones()
{
  delay(1000);
  accion(AVANCE,1);
  accion(AVANCE,2);  
  accion(ATRAS,4);
  accion(ATRAS,3);
  delay(1000); 
}

void lucia()
{
  for (int i = 0; i<5;i++){
    accion(AVANCE,4);
    accion(AVANCE,2); 
  
    accion(ATRAS,2);
    accion(ATRAS,4);
  
    accion(AVANCE,3);
    accion(AVANCE,1);
  
    accion(ATRAS,1);
    accion(ATRAS,3);
  }
}



void jesus()
{
  for (int i = 0; i<5;i++){
    accion(AVANCE,4);
    delay(PAUSA);
    accion(ATRAS,2); 
    delay(PAUSA);
    accion(AVANCE,1);
    delay(PAUSA);
    accion(ATRAS,3);
    delay(PAUSA);
    posicionInicial();
   
  }
}
void setup() 
{ 
  myservo1.attach(2);  
  myservo2.attach(3);
  myservo3.attach(4);  
  myservo4.attach(5);
  Serial.begin(9600);
} 
 
void loop() 
{ 
  
  float mediaU = mediaUltrasonidos();

  Serial.println(mediaU);
  
  posicionInicial(); 
  
  if (mediaU < 10) 
    {
    jesus();
    }
} 





