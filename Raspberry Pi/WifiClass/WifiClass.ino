int GreenButtonPin = 12;
int BlackButtonPin = 14;
int RedButtonPin = 4;
int YellowButtonPin = 5;

int GreenVal = 0;
int BlackVal = 0;
int RedVal = 0;
int YellowVal = 0;


void setup() {
  // put your setup code here, to run once:
pinMode(GreenButtonPin, INPUT);
pinMode(BlackButtonPin, INPUT);
pinMode(RedButtonPin, INPUT);
pinMode(YellowButtonPin, INPUT);
Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:

GreenVal = digitalRead(GreenButtonPin);
BlackVal = digitalRead(BlackButtonPin);
RedVal = digitalRead(RedButtonPin);
YellowVal = digitalRead(YellowButtonPin);

Serial.print("Green Val: ");
Serial.print(GreenVal);
Serial.print(" | Black Val: ");
Serial.print(BlackVal);
Serial.print(" | Red Val: ");
Serial.print(RedVal);
Serial.print(" | Yellow Val: ");
Serial.println(YellowVal);


}
