//Includes
#include <NewPing.h>
#include <Servo.h> 

//Defines
#define DISTANCE_TRIGGER_PIN  5  // Pino trigger do sensor ultrassonico
#define DISTANCE_ECHO_PIN     4  // Pino echo do sensor ultrassonico
#define SERVO_PIN             3  // Pino do servo
#define MAX_DISTANCE 200 // Distancia maxima que queremos que o sensor identifique
#define ACTION_DISTANCE 15 // Distancia maxima que queremos que o sensor identifique

//Objetos 
NewPing sonar(DISTANCE_TRIGGER_PIN, DISTANCE_ECHO_PIN, MAX_DISTANCE); // Objeto para controlar o sensor ultrassonico
Servo myservo;  // Objeto para controlar o servo (Na maioria das placas  possivel controlar at 12)
int pos = 0;    // Variavel para armazenar a posicao do servo 
boolean foundObject = false; // Identifica se algo foi encontrado
int nowPosition = 0; // Posicao atual do servo
int stepIncrement = 1;
 
void setup() { 
  Serial.begin(115200); // Mostra resultados no Serial Monitor
  myservo.attach(SERVO_PIN);  // Atribui o pino do servo ao objeto 
  myservo.write(nowPosition); 
} 
 
void loop() { 
  unsigned int distancia_autal = calculateDistance();
     if(distancia_autal > ACTION_DISTANCE || distancia_autal == 0){
       keepRotating();
     }else{
       foundObject = true;
     }
} 

void keepRotating(){  
  if( (nowPosition == 0 && stepIncrement < 0) || (nowPosition == 180 && stepIncrement > 0) ){
    stepIncrement = stepIncrement * -1;
  }
  
  if(!foundObject){
    nowPosition += stepIncrement; // Incremente/Decremeta posicao atual
    myservo.write(nowPosition); // Manda o servo ir para possicao 'nowPosition'
    delay(15); // Delay para dar tempo do servo ir para posicao indicada
  }else if(foundObject){
    for(int i = 0; (i <= 10) && (nowPosition < 180); i++){
        nowPosition += 1; // Incremente/Decremeta posicao atual
        myservo.write(nowPosition); // Manda o servo ir para possicao 'nowPosition'
        delay(15); // Delay para dar tempo do servo ir para posicao indicada
        if(calculateDistance() <= ACTION_DISTANCE){
          foundObject = true;
          return;
        }
    }
    for(int i = 0; (i <= 20) && (nowPosition > 0); i--){
        nowPosition -= 1; // Incremente/Decremeta posicao atual
        myservo.write(nowPosition); // Manda o servo ir para possicao 'nowPosition'
        delay(15); // Delay para dar tempo do servo ir para posicao indicada
        if(calculateDistance() <= ACTION_DISTANCE){
          foundObject = true;
          return;
        }
    }
    foundObject = false;
  }
  
}

unsigned int calculateDistance(){
  unsigned int pingMicroSec = sonar.ping(); // Envia ping, recebe tempo de retorno em microsegundos
  unsigned int distancia = pingMicroSec / US_ROUNDTRIP_CM; // Converte o resultado em distancia
  Serial.print("Ping: ");
  Serial.print(distancia);
  Serial.println("cm");
  return distancia;
}
