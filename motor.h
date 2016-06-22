#define D1 5
#define D2 4
#define D3 0
#define D4 2      

#define PWMA D1
#define DIRA D3
#define PWMB D2
#define DIRB D4


// constants won't change :
const long TIME = 500;           // interval at which to blink (milliseconds)

int speed = 1024;                // a number between 0 and 1024




void motor0 ( int speed, int direction) {
  if (direction) {
    digitalWrite(DIRA, HIGH);
  }
  else {
    digitalWrite(DIRA, LOW);
  }
  analogWrite(PWMA, speed);
}


void motor1 ( int speed, int direction) {
  if (direction) {
    digitalWrite(DIRB, HIGH);
  }
  else {
    digitalWrite(DIRB, LOW);
  }
  analogWrite(PWMB, speed);
}


void Forward(){
      motor0 (1024, 0);
    motor1 (1024, 1);
}

void Back(){
      motor0 (1024, 1);
    motor1 (1024, 0);
}

void Left(){
        motor0 (256, 0);
    motor1 (1024, 1);
}

void Right(){
        motor0 (1024, 0);
    motor1 (256, 1);
}

void Stop(){
      motor0 (0, 0);
    motor1 (0, 0);
}


void MotorCommond(String text){
  
        if (text.startsWith("F")) {
        String xVal = (text.substring(text.indexOf("F") + 1, text.length()));
        int speed = xVal.toInt();
        Forward();
        }

        if (text.startsWith("B")) {
        Back();
        }

        else if (text.startsWith("L")) {
        Left();
        }
        else if (text.startsWith("R")) {
        Right();
        }        
        else if (text == "STOP") {
        Stop();
        }

}

