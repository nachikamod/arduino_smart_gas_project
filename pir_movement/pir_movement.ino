#define pir_movement 8

int pir_data = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(pir_movement, INPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  pir_data = digitalRead(pir_movement);
  Serial.println(pir_data);  
  delay(1000);

}
