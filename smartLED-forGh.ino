#include <Ultrasonic.h>
#include <Servo.h>

//пины
int trigPin = A0;
int echoPin = A1;
int potentiometer = A3;
int LED = 3;    //ШИМ
int LED2 = 6;    //ШИМ
int LED3 = 11;    //ШИМ
int LED4 = 10;    //ШИМ
int LED5 = 9;    //ШИМ
int servoPin = 5;    //ШИМ

//переменные
int distance = 0;
int power = 0;    // при включении, диоды выключены
int sleepmode = 0;    // при включении, выходит из сна
int sleepPos = 180;    // позиция сна (в градусах)
int targetPos = 130;    // позиция в режиме работы (в градусах)
int stepPos = 5;    // шаг вращения
int rate = 2;    // погрешность в см, так как датчик работает от 2см
Ultrasonic ultrasonic(trigPin, echoPin);
Servo Servo1;


void setup(){ 
  Serial.begin(9600); // Запускаем монитор для инфо
  pinMode(LED, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(potentiometer, INPUT);
  Servo1.attach(servoPin);
  targetPos = targetPos / stepPos; // меняем градусы на делитель для потенциометра
  Servo1.write(sleepPos); //калибруем на позицию сна
  delay(100);
}

void loop(){
  //задаем дистанцию для управления
  distance = ultrasonic.distanceRead();
  if (distance < (15 + rate) && distance > (0 + rate)) {
    power = (distance - rate) * 17;
    analogWrite(LED, power);
    analogWrite(LED2, power);
    analogWrite(LED3, power);
    analogWrite(LED4, power);
    analogWrite(LED5, power);
  } else if (distance < (1 + rate) && distance > 0) {
    power = 0;
    analogWrite(LED, power);
    analogWrite(LED2, power);
    analogWrite(LED3, power);
    analogWrite(LED4, power);
    analogWrite(LED5, power);

  } else if (distance < (20 + rate) && distance > (16 + rate)) {
    power = 255;
    analogWrite(LED, power);
    analogWrite(LED2, power);
    analogWrite(LED3, power);
    analogWrite(LED4, power);
    analogWrite(LED5, power);
  } else {analogWrite(LED, power);
  analogWrite(LED2, power);
  analogWrite(LED3, power);
  analogWrite(LED4, power);
  analogWrite(LED5, power);}

  //задаем угол вращения
  int currPos = Servo1.read(); // Текущая позиция
  int val_poten = analogRead(potentiometer); // Считываем данные с потенциометра
  targetPos = map(val_poten, 0, 1023, 0, 180 / stepPos); // переводим данные потенциометра в новый диапазон


  if (power == 0) {    // переход в режим сна
    delay(1000);
    while (currPos < sleepPos) { // Вращаем сервомотор влево с шагом 5 градусов
      currPos += stepPos;
      Servo1.write(currPos);
      delay(100);
    }

  } else {
    int diff = abs(currPos - (targetPos * stepPos)); // Вычисляем разницу между переменными
    if (diff > 5) { // Если разница больше 5
        if (currPos > (targetPos * stepPos)) { // Если текущая позиция больше заданной
            while (currPos > (targetPos * stepPos)) { // Вращаем сервомотор влево с шагом 5 градусов
                currPos -= stepPos;
                Servo1.write(currPos);
                delay(100);
            }
        } else if (currPos < (targetPos * stepPos)) { // Если текущая позиция меньше заданной
            while (currPos < (targetPos * stepPos)) { // Вращаем сервомотор вправо с шагом 5 градусов
                currPos += stepPos;
                Servo1.write(currPos);
                delay(100);
            }
        }
    } else {
        // Разница между переменными составляет 5 или менее
    }
}
  //Монитор для инфо
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm, power: ");
  Serial.println(power);
  delay(300);

}
