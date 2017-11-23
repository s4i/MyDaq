void setup(){
  Serial.begin(9600);
}
void loop(){
   long int x, y, z;
   x = y = z = 0;
   x = analogRead(0);
   y = analogRead(1);
   z = analogRead(2);
   Serial.print("x:");
   Serial.print(x);
   Serial.print("y:");
   Serial.print(y);
   Serial.print("z:");
   Serial.println(z);
   delay(1000);
}
