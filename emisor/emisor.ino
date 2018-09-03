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

const int ABIERTO[] = {1};
const int CERRADO[] = {2};
const int TEST[] = {9};

//Variable con la dirección del canal por donde se va a transmitir
byte direccion[5] = {'c', 'a', 'n', 'a', 'l'};

//creamos el objeto radio (NRF24L01)
RF24 radio(CE_PIN, CSN_PIN);
  float datos[1];

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
    bool ok = radio.write(ABIERTO, sizeof(ABIERTO));
          Serial.println(ABIERTO[0]);

    //reportamos por el puerto serial los datos enviados
    if (ok)
    {
      Serial.print("Datos enviados: ");
    }
    else
    {
      Serial.println("no se ha podido enviar");
    }
  }

  if (digitalRead(PULSADOR_2) == HIGH) {
     bool ok = radio.write(CERRADO, sizeof(CERRADO));
     Serial.println(CERRADO[0]);

    //reportamos por el puerto serial los datos enviados
    if (ok)
    {
      Serial.print("Datos enviados: ");
    }
    else
    {
      Serial.println("no se ha podido enviar");
    }
    
  }

  if (digitalRead(PULSADOR_3) == HIGH) {
     Serial.println(TEST[0]);
     bool ok = radio.write(TEST, sizeof(TEST));
    
    //reportamos por el puerto serial los datos enviados
    if (ok)
    {
      Serial.print("Datos enviados: ");
    }
    else
    {
      Serial.println("no se ha podido enviar");
    }
  }

}
