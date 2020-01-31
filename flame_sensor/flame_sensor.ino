#define flame_sensor 8

int flame_data = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(flame_sensor, INPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  flmae_data = digitalRead(flame_sensor);
  Serial.println(flame_data);  
  delay(1000);

}
