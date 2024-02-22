# Smart-LED-lamp-Arduino

Описание:
---------------------
В коде реализована работа лампы, которая поворачивается при включении и имеет регулировку уровня света через приближение или отдаление ладони.

![image](https://github.com/Kirill-Kasparov/Smart-LED-lamp-Arduino/assets/131332065/87d68145-9096-4818-ab6f-692e27a64130)

Принцип работы:
---------------------
За основу взят корпус от сломанной люминисцентной лампы. Свет заменен на 5 светодиодов. Добавлен сервопривод для автоматического разворота, потенциометр для регулирования угла поворота, ультразвуковой датчик для управления включением лампы и силой свечения.
В плафон лампы установлен дальномер, который реагирует только в диапазоне от 0 до 20 см:

  0-3 см - светодиоды выключены, лампа разворачивается в стартовую позицию.
  
  4-20 см - лампа поворачивается в рабочую позицию, интенсивность свечения настраивается от дальности ладони, где 4 см - минимальная яркость, 20 см - максимальная яркость.

Чтобы настроить угол поворота лампы, добавлен потенциометр. Настройка осуществляется только один раз, или меняется при необходимости. Дальше лампа всегда будет выходить на заданную позицию.

Потребуется:
---------------------
1. Каркас лампы
2. Подшипник
3. Контролер Arduino Nano
4. Сервопривод SG90
5. Ультразвуковой датчик HC-SR04
6. Потенциометр (можно без него, указав градус поворота в Скетче)
7. Провода: красный - 150, черный - 150, зеленый (для сервопривода) - 100, обрезки от 5 до 10 см ~ 10 шт
8. Резисторы - 5 шт. 220 Ом
9. Светодиод 3мм - 5 шт.
10. Разъем USP Type-A (male) или источник питания ~5V

Реализация:
---------------------
1. Разметка проводов.

Из лампы убираем все "лишнее". В своем варианте я укоротил плафон светильника, вырезал дополнительные отверстия под провода, ультразвуковой датчик и потенциометр.
Заготавливаем провода для пайки. Так как Arduino Nano хорошо помещается в боксе, где был патрон от люминисцентной лампы, оптимальное расположение проводов:
![image](https://github.com/Kirill-Kasparov/Smart-LED-lamp-Arduino/assets/131332065/eecf114a-ac4b-44aa-a295-c024c7a7969f)

2. Пайка плафона.

Рекомендую потратить время и крепко закрепить Arduino Nano на своем месте. Убедитесь, что Вам будет удобно подключать usb-кабель для кодирования. Я этого не сделал и для загрузки обновления приходилось каждый раз разбирать плафон.
Пайку осуществляем по схеме ниже. В плафон пойдет всё, кроме сервопривода. 

LifeHack: гибкие провода можно взять из интернет-кабеля, там их 8 штук, да и стоит такой провод дешевле.

По итогу у нас должен быть готовый плафон и от него выходит 3 длинных провода (плюс, общий минус, pin для серво).

![image](https://github.com/Kirill-Kasparov/Smart-LED-lamp-Arduino/assets/131332065/f71b8976-3f9b-4d10-881b-5d3098f00f66)

У меня получилось так:

![image](https://github.com/Kirill-Kasparov/Smart-LED-lamp-Arduino/assets/131332065/430a4367-ed91-4b3c-9d8c-33de54da3c4e)

![image](https://github.com/Kirill-Kasparov/Smart-LED-lamp-Arduino/assets/131332065/cf50ccb5-af00-4717-a0ff-67f8673dfbd4)


Теперь 3 длинных провода (плюс, общий минус, pin для серво) можно пропустить по корпусу. На сгибах оставляйте запас по 3 см кабеля, тогда лампу можно будет сгибать без риска обрыва проводов.

3. Установка сервопривода.

В разложенном виде лампа создает Очень большую нагрузку на основание, поэтому прямое подключение маломощного сервопривода SG90 невозможно. Чтобы перенести нагрузку с сервопривода, я использую подшипник.

LifeHack: сразу 8 отличных подшипников можно взять от старых роликовых коньков. Нам потребуется только 1.

Собираем такую конструкцию:

![image](https://github.com/Kirill-Kasparov/Smart-LED-lamp-Arduino/assets/131332065/e222a576-3c8e-4c10-8b9e-de4abc80808d)

LifeHack: металлическая скоба сделана из уголка под штукатурку - это очень дешевый и довольно крепкий материал. Искать как "Угол алюминиевый перфорированный 20x20"

В такой конструкции корпус сервопривода жестко крепится к корпусу лампы и внешней стороне подшипника. Сервопривод вращает внутреннюю сторону подшипника, на которую так же винтом закреплена полка - основание. Важно! В моем примере основание будет иметь дополнительное крепление к столу. Чтобы лампа не заваливалась под собственным весом,потребуется полка не менее 15см.

Подкдлючаем сервопривод к 3 проводам, которые мы вывели раннее. Зеленый (pin для серво) подключаем прямо к хвосту, обрезаем излишек. К красному и черному проводу необходимо врезаться удобным для Вас способом. Останется хвост 50+ см из красного и черного провода - подключаем к источнику питания.

У моего светльника у основания был корпус под дроссель для люминисцентной лампы, поэтому сервопривод я спрятал в корпус. В модификации без этого корпуса, каркас лампы придется сместить влево или вправо и подумать над жестким креплением к внешней стороне подшипника, так как нагрузка рычага лампы большая (про горячий клей и жидкие гвозди забудьте).

![image](https://github.com/Kirill-Kasparov/Smart-LED-lamp-Arduino/assets/131332065/fc65f969-dae8-4c74-85c5-3db6e61aa41a)

![image](https://github.com/Kirill-Kasparov/Smart-LED-lamp-Arduino/assets/131332065/ba743656-e7bf-423b-9979-1aa35e68b491)

Сцепку корпуса лампы с внешней стороной подшипника сделал так же из металлического  уголка. Это был уже третий вариант крепления, поэтому корпус много повидал.

![image](https://github.com/Kirill-Kasparov/Smart-LED-lamp-Arduino/assets/131332065/54afbb9c-3ed3-4ad5-8ce0-7706672011a3)

На этом этапе корпус лампы собран, все контакты подключены и прозвонены. Осталось только загрузить скетч.

4. Загружаем скетч.
```cpp
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <DHT.h>      // подключаем библиотека для датчика температуры и влажности

int AirValuePin = A3;  // Пин подключения потенциометра для переменной WaterValue
int AlarmLed = 2;   // Пин светодиода тревоги
DHT dht(11, DHT22);  // Пин датчика температуры и влажности
LiquidCrystal_I2C lcd(0x27,16,2);  // Устанавливаем дисплей


//датчики влажности почвы
int AirValue = 600;             // Максимальное значение сухого датчика
int WaterValue = 300;           // Минимальное значение погруженного датчика

int soilMoistureValue = 0;            // Создаем переменную soilMoistureValue
int soilMoisturePercent = 0;    

int soilMoistureValue2 = 0;            // Создаем переменную soilMoistureValue2
int soilMoisturePercent2 = 0;  

int soilMoistureValue3 = 0;            // Создаем переменную soilMoistureValue3
int soilMoisturePercent3 = 0;  

void setup() 
{
  Serial.begin(9600);                 // Открываем последовательную связь на скорости 9600
  pinMode(soilMoistureValue, INPUT);  // Устанавливаем вывод как вход.
  pinMode(soilMoistureValue2, INPUT);  // Устанавливаем вывод как вход.
  pinMode(soilMoistureValue3, INPUT);  // Устанавливаем вывод как вход.
  pinMode(AirValuePin, INPUT);  // Потенциометр
  pinMode(AlarmLed, OUTPUT);
  dht.begin();                // запускаем датчик DHT22
  
  lcd.init();                     
  lcd.backlight();// Включаем подсветку дисплея

}
void loop() 
{
// Снимаем порог влажности с потенциометра
int airPotValue = analogRead(AirValuePin);  // Считываем значение с потенциометра для AirValue
AirValue = map(airPotValue, 0, 1023, WaterValue, 1000); // Маппинг значения на диапазон от 300 до 600

// Снимаем температуру и влажность воздуха
int f = dht.readHumidity();
int t = dht.readTemperature();

// Выводим темп. и влажн. воздуха
lcd.setCursor(0, 0);
lcd.print("Temp: ");
lcd.print(t);
lcd.print("c");

lcd.setCursor(9, 0);
lcd.print(" f: ");
lcd.print(f);
lcd.print("%");

  //Снимаем влажность почвы
soilMoistureValue = analogRead(A0);   // Считываем данные с порта A0 и записываем их в переменную
soilMoistureValue2 = analogRead(A1);   // Считываем данные с порта A0 и записываем их в переменную
soilMoistureValue3 = analogRead(A2);   // Считываем данные с порта A0 и записываем их в переменную

if (soilMoistureValue > AirValue || soilMoistureValue2 > AirValue || soilMoistureValue3 > AirValue) {    // устраняем погрешность вычислений
    AirValue = max(max(soilMoistureValue, soilMoistureValue2), soilMoistureValue3);}

if (soilMoistureValue < WaterValue || soilMoistureValue2 < WaterValue || soilMoistureValue3 < WaterValue) {
  WaterValue = min(min(soilMoistureValue, soilMoistureValue2), soilMoistureValue3);}


soilMoisturePercent = map(soilMoistureValue, AirValue, WaterValue, 0, 9);
soilMoisturePercent2 = map(soilMoistureValue2, AirValue, WaterValue, 0, 9);
soilMoisturePercent3 = map(soilMoistureValue3, AirValue, WaterValue, 0, 9);

// Выводим влажность почвы
lcd.setCursor(0, 1);
lcd.print("1");
lcd.write(126);
lcd.print(soilMoisturePercent);

lcd.setCursor(5, 1);
lcd.print(" 2");
lcd.write(126);
lcd.print(soilMoisturePercent2);

lcd.setCursor(11, 1);
lcd.print(" 3");
lcd.write(126);
lcd.print(soilMoisturePercent3);

// Сигнал тревоги
if (soilMoisturePercent <= 1 || soilMoisturePercent2 <= 1 || soilMoisturePercent3 <= 1) {
    digitalWrite(AlarmLed, HIGH);
  } else {
    digitalWrite(AlarmLed, LOW);
  }

// Монитор
Serial.print("Temp: ");
Serial.print(t);
Serial.print("с f: ");
Serial.println(f);
Serial.print("1-");
Serial.print(soilMoisturePercent);
Serial.print("% 2-");
Serial.print(soilMoisturePercent2);
Serial.print("% 3-");
Serial.println(soilMoisturePercent3);
Serial.print("AirValue: ");
Serial.println(AirValue);
Serial.println(airPotValue);

delay(1000);
}
```
Справочно. В коде заложено несколько функций, чтобы пощадить сервомотор: 
- плавное перемещение светильника (переменная stepPos)
- будет работать только при изменении показателей ультразвукового датчика (переменная old_distance),
- не будет реагировать на близкий к заданному углу промежуток в 5 градусов (переменная diff)

5. Итоговый результат:

https://github.com/Kirill-Kasparov/Smart-LED-lamp-Arduino/assets/131332065/37e47819-3efb-438b-ace4-131e6abe4a67

Бум! :-)
