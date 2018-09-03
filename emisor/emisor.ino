#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//Declaremos los pines CE y el CSN
#define CE_PIN 9
#define CSN_PIN 10

//Declaremos los pines de los pulsadores
#define PULSADOR_1 2
#define PULSADOR_2 3
#define PULSADOR_3 4

const char ABIERTO[] = "ABIERTO";
const char CERRADO[] = "CERRADO";
const char TEST[] = "TEST";

//Variable con la dirección del canal por donde se va a transmitir
byte direccion[5] = {'c', 'a', 'n', 'a', 'l'};

//creamos el objeto radio (NRF24L01)
RF24 radio(CE_PIN, CSN_PIN);

//vector con los datos a enviar

void setup()
{
  //Declaramos pines de entrada
  pinMode(PULSADOR_1, INPUT);
  pinMode(PULSADOR_2, INPUT);
  pinMode(PULSADOR_3, INPUT);

  //inicializamos el NRF24L01
  radio.begin();
  //inicializamos el puerto serie
  Serial.begin(9600);

  //Abrimos un canal de escritura
  radio.openWritingPipe(direccion);


}

void loop()
{
  while (!digitalRead(PULSADOR_1) == HIGH && !digitalRead(PULSADOR_2) == HIGH && !digitalRead(PULSADOR_3) == HIGH) {}

  if (digitalRead(PULSADOR_1) == HIGH) {
    Serial.println(ABIERTO);
    bool ok = radio.write(ABIERTO, sizeof(ABIERTO));
    
    //reportamos por el puerto serial los datos enviados
    if (ok)
    {
      Serial.print("Datos enviados: ");
      Serial.println(ABIERTO);

    }
    else
    {
      Serial.println("no se ha podido enviar");
    }
  }

  if (digitalRead(PULSADOR_2) == HIGH) {
    Serial.println(CERRADO);
  }

  if (digitalRead(PULSADOR_3) == HIGH) {
    Serial.println(TEST);
  }

  delay(250);
}
