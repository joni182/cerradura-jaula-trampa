#include <Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//Declaremos los pines CE y el CSN
#define CE_PIN 9
#define CSN_PIN 10

//Variable con la dirección del canal que se va a leer
byte direccion[5] = {'c', 'a', 'n', 'a', 'l'};

//creamos el objeto radio (NRF24L01)
RF24 radio(CE_PIN, CSN_PIN);

Servo servoMotor;


//vector para los datos recibidos
int  datos[1];

void setup()
{
  //inicializamos el NRF24L01
  radio.begin();
  //inicializamos el puerto serie
  Serial.begin(9600);

  // Iniciamos el servo para que empiece a trabajar con el pin 6
  servoMotor.attach(6);

  //Abrimos el canal de Lectura
  radio.openReadingPipe(1, direccion);

  //empezamos a escuchar por el canal
  radio.startListening();

}

void loop() {
  uint8_t numero_canal;
  //if ( radio.available(&numero_canal) )
  if ( radio.available() )
  {
    //Leemos los datos y los guardamos en la variable datos[]
    radio.read(datos, sizeof(datos));

    Serial.println(datos[0]);

    if (datos[0] == 1)
    {
      servoMotor.write(0);
    }

    if (datos[0] == 2)
    {
      servoMotor.write(65);
    }

    if (datos[0] == 9)
    {
      servoMotor.write(180);
    }

  }
}
