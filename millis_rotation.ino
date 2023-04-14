const int motor_A1 = 5;
const int motor_A2 = 6;
const int motor_B1 = 9;
const int motor_B2 = 10;
const int IR_R = A1;
const int IR_M = A3;
const int IR_L = A5;
const int trigPin = 8;
const int echoPin = 11;
int IR_L_data;
int IR_M_data;
int IR_R_data;

unsigned long t_prev = 0;
const unsigned long t_delay = 3000;

int speed_A = 255; // 모터A의 속도
int speed_B = 255; // 모터B의 속도
float duration, distance;

void setup() {
  pinMode(motor_A1, OUTPUT);
  pinMode(motor_A2, OUTPUT);
  pinMode(motor_B1, OUTPUT);
  pinMode(motor_B2, OUTPUT);
  pinMode(IR_L, INPUT);
  pinMode(IR_M, INPUT);
  pinMode(IR_R, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  Serial.print("Start");
}

void loop() {
  IR_L_data = digitalRead(IR_L);
  IR_M_data = digitalRead(IR_M);
  IR_R_data = digitalRead(IR_R);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration * .0343) / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance < 10) {
    Serial.println("정지");
    stop();
    delay(100);
    unsigned long t_now = millis();
    if(t_now - t_prev >= t_delay) {
     int f_now =  t_now / 3000; 
     if (f_now % 1 == 0){
        rotation(speed_A, speed_B);
        delay(2000);
      Serial.print("time: ");
      Serial.println(f_now);
      }
      t_prev = t_now;
      // Serial.print("time: ");
      // Serial.println(t_now);
    }
  }
  else if (distance >= 10) {
    // Serial.println("직진");
    forward(speed_A, speed_B);
  }
  // else if (IR_L_data == 1 and IR_M_data == 0 and IR_R_data == 0) {
  //   // Serial.println("좌회전");
  //   left(speed_A*0.8, speed_B);
  // }
  // // else if (IR_L_data == 1 and IR_M_data == 1 and IR_R_data == 0) {
  // //   // Serial.println("좌회전");
  // //   left(speed_A*0.8, speed_B);
  // // }
  // else if (IR_L_data == 0 and IR_M_data == 0 and IR_R_data == 1) {
  //   // Serial.println("우회전");
  //   right(speed_A, speed_B*0.8);
  // }
  // else if (IR_L_data == 0 and IR_M_data == 1 and IR_R_data == 1) {
  //   // Serial.println("우회전");
  //   right(speed_A, speed_B*0.8);
  // }
  // else if (IR_L_data == 1  and IR_R_data == 1) {
  //   Serial.println("정지");
  //   stop();
  // }
  // else if (distance>=1 and distance <= 5) {
  //   Serial.println("정지");
  //   stop();
  // }
  delay(100);
}

void right(int speed_A, int speed_B) {
  // 우회전
  analogWrite(motor_A1, speed_A);
  analogWrite(motor_A2, LOW);
  analogWrite(motor_B1, LOW);
  analogWrite(motor_B2, speed_B);
}

void left(int speed_A, int speed_B) {
  // 좌회전
  analogWrite(motor_A1, LOW);
  analogWrite(motor_A2, speed_A);
  analogWrite(motor_B1, speed_B);
  analogWrite(motor_B2, LOW);
}

void forward(int speed_A, int speed_B) {
  // 전진
  analogWrite(motor_A1, speed_A);
  analogWrite(motor_A2, LOW);
  analogWrite(motor_B1, speed_B);
  analogWrite(motor_B2, LOW);
}

void backward(int speed_A, int speed_B) {
  // 후진
  analogWrite(motor_A1, LOW);
  analogWrite(motor_A2, speed_A);
  analogWrite(motor_B1, LOW);
  analogWrite(motor_B2, speed_B);
}

void stop() {
  analogWrite(motor_A1, LOW);
  analogWrite(motor_A2, LOW);
  analogWrite(motor_B1, LOW);
  analogWrite(motor_B2, LOW);
}

void rotation(int speed_A, int speed_B){
  analogWrite(motor_A1, LOW);
  analogWrite(motor_A2, speed_A*0.9);
  analogWrite(motor_B1, LOW);
  analogWrite(motor_B2, LOW);
}
