#include <SoftwareSerial.h>
#include <FlySkyIBus.h>

FlySkyIBus IBus;

SoftwareSerial ibus(2, 3);

byte values[7];//массив значений стиков + синхроимпульс завершения пакета данных (0xF0+. то есть 0xF0 - 0xFF, у меня 0xFF)

void setup() {
  ibus.begin(115200);
  IBus.begin(ibus);
  Serial.begin(19200);//скорость общения с симулятором (9600/синхросигнал 0xF0+ или 19200/синхросигнал 0xFF)
  values[0] = 0xFF;//устанавливаем синхросигнал

}

void loop() {
  IBus.loop();
  values[1] = map(IBus.readChannel(0), 1000, 2000, 0, 254);//крен
  values[2] = map(IBus.readChannel(1), 1000, 2000, 0, 254);//тангаж
  values[3] = map(IBus.readChannel(2), 1000, 2000, 0, 254);//газ
  values[4] = map(IBus.readChannel(3), 1000, 2000, 0, 254);//рысканье
  values[5] = map(IBus.readChannel(4), 1000, 2000, 0, 254);//доп. канал 1
  values[6] = map(IBus.readChannel(5), 1000, 2000, 0, 254);//доп. канал 2
  Serial.write(values, 7);//отправляем в симулятор
  delay(10);

}
