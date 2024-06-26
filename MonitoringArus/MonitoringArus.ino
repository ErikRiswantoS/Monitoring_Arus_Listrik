#include <PZEM004Tv30.h>

 // Insallasi objek untuk PZ
  PZEM004Tv30 pzem(12, 13); // 12=D6 (Rx), 13=D7 (Tx)

// Variabel Penampung untuk nilai sensor arus
float Power, Energy, Voltase, Current;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Baca Nilai Power (KW)
  Power = pzem.power();
  // jika gagal membaca Power
  if(isnan(Power))
  {
    Serial.println("Gagal membaca power");
  }
  else
  {
    Serial.print("Power : ");
    Serial.print(Power);
    Serial.println("kW");
  }

 // Baca Nilai Energy (kWh)
  Energy = pzem.energy();
  // jika gagal membaca Energy
  if(isnan(Energy))
  {
    Serial.println("Gagal membaca energy");
  }
  else
  {
    Serial.print("Energy : ");
    Serial.print(Energy);
    Serial.println("kWh");
  }

 // Baca Nilai voltase (Volt)
  Voltase = pzem.voltage();
  // jika gagal membaca voltase
  if(isnan(Voltase))
  {
    Serial.println("Gagal membaca voltase");
  }
  else
  {
    Serial.print("Voltase : ");
    Serial.print(Voltase);
    Serial.println("V");
  }

 // Baca Nilai current (A)
  Current = pzem.current();
  // jika gagal membaca current
  if(isnan(Current))
  {
    Serial.println("Gagal membaca Current");
  }
  else
  {
    Serial.print("Current : ");
    Serial.print(Current);
    Serial.println("A");
  }

  Serial.println();
  delay(1000);

}
