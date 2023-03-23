#include <NewPing.h>
int outSensorEsq = 4;
int pinSensorEsq1 = 2;
int pinSensorEsq2 = 3;
int pinSensorDir1 = A5;
int pinSensorDir2 = A4;
int outSensorDir = A3;
int pinDir1 = 10;
int pinDir2 = 9;
int pinEsq1 = 5;
int pinEsq2 = 6;

class Motor{
  private: 
    int pinDir1;
    int pinDir2;
    int pinEsq1;
    int pinEsq2;
  public:
    Motor(int pinDir1,int pinDir2, int pinEsq1, int pinEsq2){
      this->pinDir1 = pinDir1;
      this->pinDir2 = pinDir2;
      this->pinEsq1 = pinEsq1;
      this->pinEsq2 = pinEsq2;
      pinMode(this->pinDir1,OUTPUT);
      pinMode(this->pinDir2,OUTPUT);
      pinMode(this->pinEsq1,OUTPUT);
      pinMode(this->pinEsq2,OUTPUT);
    }
    void parar(int delaytime = 100){
      digitalWrite(this->pinDir1,LOW);
      digitalWrite(this->pinDir2,LOW);
      digitalWrite(this->pinEsq1,LOW);
      digitalWrite(this->pinEsq2,LOW);
      delay(delaytime);
    }
    void andar(){
      digitalWrite(this->pinDir1,HIGH);
      digitalWrite(this->pinDir2,LOW);
      digitalWrite(this->pinEsq1,HIGH);
      digitalWrite(this->pinEsq2,LOW);
    }
    void andar(int velocidade, int delaytime = 100){
      if(velocidade>0 && velocidade<=255){
      analogWrite(this->pinDir1,velocidade);
      digitalWrite(this->pinDir2,LOW);
      analogWrite(this->pinEsq1,velocidade);
      digitalWrite(this->pinEsq2,LOW);
      delay(delaytime);
      }
      else if(velocidade<0 && velocidade>=-255){
      int velocidadevoltar = velocidade*(-1);
      digitalWrite(this->pinDir1,LOW);
      analogWrite(this->pinDir2,velocidadevoltar);
      digitalWrite(this->pinEsq1,LOW);
      analogWrite(this->pinEsq2,velocidadevoltar);
      delay(delaytime);
      }
    }
    void virarEsq(int velocidade,int delaytime=100){
      int velocidadevoltar = velocidade*(-1);
      digitalWrite(this->pinDir1,LOW);
      analogWrite(this->pinDir2,velocidadevoltar);
      digitalWrite(this->pinEsq1,velocidade);
      analogWrite(this->pinEsq2,LOW);
      delay(delaytime);
    }
    void virarDir(int velocidade,int delaytime=100){
      int velocidadevoltar = velocidade*(-1);
      analogWrite(this->pinDir1,velocidadevoltar);
      digitalWrite(this->pinDir2,LOW);
      digitalWrite(this->pinEsq1,LOW);
      analogWrite(this->pinEsq2,velocidade);
      delay(delaytime);
    }
};
class SensorCor{
  private:
    int pinSensorEsq1;
    int pinSensorEsq2;
    int pinSensorDir1;
    int pinSensorDir2;
    int outSensorEsq;
    int outSensorDir;    
  public:
    SensorCor(int pinSensorEsq1, int pinSensorEsq2, int pinSensorDir1, int pinSensorDir2,int outSensorEsq, int outSensorDir){
      this->pinSensorEsq1 = pinSensorEsq1;
      this->pinSensorEsq2 = pinSensorEsq2;
      this->pinSensorDir1 = pinSensorDir1;
      this->pinSensorDir2 = pinSensorDir2;
      this->outSensorEsq = outSensorEsq;
      this->outSensorDir = outSensorDir;
      pinMode(this->pinSensorEsq1,OUTPUT);
      pinMode(this->pinSensorEsq2,OUTPUT);
      pinMode(this->pinSensorDir1,OUTPUT);
      pinMode(this->pinSensorDir2,OUTPUT);
      pinMode(this->outSensorEsq,INPUT);
      pinMode(this->outSensorDir,INPUT);
    }
    int lerVerdeEsquerdo(){
      digitalWrite(this->pinSensorEsq1,HIGH);
      digitalWrite(this->pinSensorEsq2,HIGH);
      int green = pulseIn(this->outSensorEsq, digitalRead(this->outSensorEsq) == HIGH ? LOW : HIGH);
      return green;
      
    }


};


Motor motor(pinDir1,pinDir2,pinEsq1,pinEsq2);
SensorCor sensor(pinSensorEsq1,pinSensorEsq2,pinSensorDir1,pinSensorDir2,outSensorEsq,outSensorDir);


void setup() { 
  pinMode(13,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  //motor.parar();
  //delay(1000);
  //motor.andar(100);
  //delay(1000);
  //motor.virarEsq(100,1000);
  Serial.println(sensor.lerVerdeEsquerdo());  
  if(sensor.lerVerdeEsquerdo()<30){
    motor.andar(80,0);
  }
  else{
    motor.parar();
  }
}
void loop2() {
  digitalWrite(13,HIGH);
  delay(1000);
  digitalWrite(13,LOW);
  delay(1000);
}
