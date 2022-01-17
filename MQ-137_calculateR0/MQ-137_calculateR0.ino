//Code to Calculate R0 
//Rs/R0=3.6

#define Vcc 5
#define RL 10.0

void setup() {
  Serial.begin(9600); //Baud rate 
}
 
void loop() { 
  float VRL = 0;          //Напряжение на нагрузочном резисторе RL 
  float RS = 0;           //Сопротивление датчика при разных концентрациях
  float R0 = 0;           //Сопротивление датчика на чистом воздухе
  float sensorValue = 0;  //Для чтения данных с АЦП 
  
  for(int x = 0 ; x < 500 ; x++) //500 раз читаем АЦП 
  {
    sensorValue += analogRead(A7);
  }
  
  sensorValue /= 500.0; //Среднее из 500 измерений АЦП
  Serial.print("sensorValue = ");
  Serial.print(sensorValue);
  Serial.print("\t|\t");
  
  VRL = sensorValue*(Vcc/1023.0); //Преобразуем значение с АЦП напряжение
  Serial.print("VRL = ");
  Serial.print(VRL);
  Serial.print(" Volt\t\t|\t");
  
  RS = ((Vcc/VRL)-1)*RL; //Сопротивление при разных концентрациях 
  Serial.print("RS = ");
  Serial.print(RS);
  Serial.print(" kOhm\t\t|\t");
  
  R0 = RS/3.6; //Сопротивление на свежем воздухе
  Serial.print("R0 = "); //Display "R0"
  Serial.print(R0); //Display value of R0 
  Serial.print(" kOhm\t\n");
  
  delay(3000); //Пауза
}
