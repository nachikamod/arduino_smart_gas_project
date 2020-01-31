#define gas_sensor A0

int gas_data;

void setup() {
  // put your setup code here, to run once:
  pinMode(gas_sensor, INPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  gas_data = analogRead(gas_sensor);
  Serial.println(gas_data);
 
}
