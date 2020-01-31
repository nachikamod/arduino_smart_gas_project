#define ir_movement 10

int ir_data = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(ir_movement, INPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  ir_data = digitalRead(ir_movement);
  Serial.println(ir_data);  
  delay(1000);

}
