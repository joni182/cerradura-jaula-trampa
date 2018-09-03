#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//Declaremos los pines CE y el CSN
#define CE_PIN 9
#define CSN_PIN 10

const int inputPin = 4;
int dato[1];

//Variable con la dirección del canal por donde se va a transmitir
byte direccion[5] ={'c','a','n','a','l'};

//creamos el objeto radio (NRF24L01)
RF24 radio(CE_PIN, CSN_PIN);

//vector con los datos a enviar

void setup()
{
  pinMode(inputPin, INPUT);
  //inicializamos el NRF24L01 
  radio.begin();
  //inicializamos el puerto serie
  Serial.begin(9600); 
 
//Abrimos un canal de escritura
 radio.openWritingPipe(direccion);

 dato[0] = 9;
 
}
 
void loop()
{
  if (digitalRead(inputPin) == HIGH) {
      bool ok = radio.write(dato, sizeof(dato));
      //reportamos por el puerto serial los datos enviados 
      if(ok)
      {
        Serial.print("Dato enviado: "); 
        Serial.print(dato[0]); 
     }
     else
     {
       Serial.println("no se ha podido enviar");
     }
  }
  else {
      Serial.println("Apagado");
  }
  delay(10);
}
