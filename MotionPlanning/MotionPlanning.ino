#include <Servo.h> //include the servo library

int safePos = 90;

Servo ServoA; //yellow
Servo ServoB; //orange
Servo ServoC; //green
Servo ServoD; //blue
Servo ServoE; //purple

int ServoAPin = 3;
int ServoBPin =5;
int ServoCPin = 9;
int ServoDPin = 10;
int ServoEPin = 11;

// for bin 1,2,3,4
int BinPositionsA[] = {79, 69, 79, 65};
int BinPositionsB[] = {74, 64, 104, 98};
int BinPositionsC[] = {54, 45, 101, 84};
int BinPositionsD[] = {68, 68, 84, 68};
int BinPositionsE[] = {86, 86, 86, 86};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ServoA.attach(ServoAPin); //attaches the servo to the pin
  ServoB.attach(ServoBPin);
  ServoC.attach(ServoCPin);
  ServoD.attach(ServoDPin);
  ServoE.attach(ServoEPin);

  Serial.println("Setting up - bringing everything back to safe position");
  ResetAllServosToSafePos();

  Serial.println("Set up complete");
  delay(500);
}

void loop() {

  BallPickup();
  ResetAllServosToSafePos();


 Serial.println("Executing Bin 1 drop off");
 BallDrop(1);
  ResetAllServosToSafePos();
 
 delay(2000); //delay in the process
 Serial.println("Executing Bin 2 drop off");
 BallDrop(2);
  ResetAllServosToSafePos();
 delay(2000);

 Serial.println("Executing Bin 3 drop off");
 BallDrop(3);
  ResetAllServosToSafePos();
 delay(2000);

 Serial.println("Executing Bin 4 drop off");
 BallDrop(4);
  ResetAllServosToSafePos();
 delay(2000);

 Serial.println("Returning back"); // so that the initiatialization doesnt break our arm
 ResetAllServosToSafePos();

delay(2000);
}

void UpdateServoPos(Servo servo, float angl) {
  
  int lastPos = servo.read() ;
  if (lastPos <= angl) {
  for (lastPos; lastPos < angl; lastPos++) {
      servo.write(lastPos);
      delay(50);
}} else{
  for (lastPos; lastPos > angl; lastPos--) {
      servo.write(lastPos);
      delay(50);
  }
}
 }

void BallPickup() {
    int PosA = 108;
    int PosB = 57;
    int PosC = 91;
    int PosD = 101;
    int PosE = 125;

    Serial.println("Executing ball pick up");


    UpdateServoPos(ServoA,PosA);
    UpdateServoPos(ServoB,PosB);
    UpdateServoPos(ServoC,PosC);
    UpdateServoPos(ServoD,PosD);
    UpdateServoPos(ServoE,PosE);
}

void ResetAllServosToSafePos() {
  UpdateServoPos(ServoA, 90);
  
  UpdateServoPos(ServoB, 94);

  UpdateServoPos(ServoD, 153);
  UpdateServoPos(ServoC, 121);



  UpdateServoPos(ServoE, 90);
}


void AfterPickUp() {
  UpdateServoPos(ServoD, 144);
  UpdateServoPos(ServoB, 89);


}


void BallDrop(int binNum) {
  if (binNum >= 1 && binNum <= 4) {
    int index = binNum - 1; // Convert bin number to 0-indexed array position
    UpdateServoPos(ServoA, BinPositionsA[index]);
    UpdateServoPos(ServoB, BinPositionsB[index]);
    UpdateServoPos(ServoC, BinPositionsC[index]);
    UpdateServoPos(ServoD, BinPositionsD[index]);
    UpdateServoPos(ServoE, BinPositionsE[index]);
  } else {
    Serial.println("Error: Invalid bin number");
  }
}
