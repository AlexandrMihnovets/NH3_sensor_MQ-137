/*
 * Program to measure gas in ppm using MQ sensor
 * Program by: B.Aswinth Raj
 * Website: http://www.circuitdigest.com/
 * Dated: 28-12-2017
 */

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
#define RL 10         //сопротивление резистора RL 10 кОм
#define m -0.243      //здесь вводим рассчитанный коэффициент наклона кривой
#define b 0.323       //здесь вводим рассчитанный коэффициент для точки пересечения
#define Ro 24         //здесь вводим найденное значение Ro
#define MQ_sensor A0  //датчик подключен к контакту A7
#define Vcc 5.0

#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

Adafruit_SSD1306 display(OLED_RESET);



void setup() {
 Serial.begin(9600);
 
 display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
 display.clearDisplay();
}
void loop() {
  display.clearDisplay();

  float VRL = 0;    //падение напряжение на датчике газа серии MQ
  float Rs = 0;     //сопротивление датчика при наличии концентрации газа 
  float ratio = 0;  //переменная для хранения отношения Rs/Ro
   
  VRL = analogRead(MQ_sensor)*(Vcc/1023.0); //измеряем падение напряжения и конвертируем его в диапазон 0-5V
  Rs = ((Vcc*RL)/VRL)-RL; //формула для расчета значения Rs
  ratio = Rs/Ro;  // находим отношение Rs/Ro

  double ppm = pow(10.0, ((log10(ratio)-b)/m)); //формула для расчета ppm
  ppm = constrain(ppm, 0, 500);   //Ограничил от 0 до 500 ppm

  double *ptr;
  ptr = &ppm;
  
  Serial.print("NH3 = ");   //отображаем концентрацию аммиака в ppm
  Serial.print(ppm);
  Serial.print("\tppm\t\t|\t\t");
  Serial.print("Voltage = "); //Display a intro message 
  Serial.print(VRL);
  Serial.print("\tVolt\n");
  
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("NH3 =");
  display.setCursor(63,0);
  display.print(*ptr, 1);
  display.setCursor(0,16);
  display.print("ppm");
  display.display();
  
  delay(500);
}
