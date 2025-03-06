/************************** Configuration ***********************************/
#define IO_USERNAME "USERNAME"
#define IO_KEY "KEY"

#define WIFI_SSID "HONOR"
#define WIFI_PASS "12345678"

#include "AdafruitIO_WiFi.h"
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

/************************ Variables Globales *******************************/
#define LedR 5
#define ENVIO_INTERVALO 15000  // Enviar datos cada 10 segundos
unsigned long ultimoEnvio = 0;

int temp = 0, contaminacion = 0, luz = 0;  // Variables para almacenar valores más recientes

// Feeds de Adafruit IO
AdafruitIO_Feed *feedControl = io.feed("Control");
//AdafruitIO_Feed *feedBoton = io.feed("Boton");
AdafruitIO_Feed *feedT = io.feed("Temperatura");
AdafruitIO_Feed *feedA = io.feed("Contaminación");
AdafruitIO_Feed *feedL = io.feed("Iluminación");

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.print("Conectando a Adafruit IO");
  //pinMode(LedR, OUTPUT);
  //digitalWrite(LedR, LOW);

  // Conectar a Adafruit IO
  io.connect();
  feedControl->onMessage(handleMessageControl);
  //feedBoton->onMessage(handleMessageBoton);

  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println(io.statusText());
  feedControl->get();
  //feedBoton->get();
}

void loop() {
  io.run();  // Mantener conexión con Adafruit IO

  if (Serial.available() > 0) {
    String dato = Serial.readStringUntil('\n');  
    dato.trim();

    int indiceT = dato.indexOf("T");
    int indiceA = dato.indexOf("A");
    int indiceL = dato.indexOf("L");

    if (indiceT != -1 && indiceA != -1 && indiceL != -1) {
      temp = dato.substring(indiceT + 1, indiceA).toInt();
      contaminacion = dato.substring(indiceA + 1, indiceL).toInt();
      luz = dato.substring(indiceL + 1).toInt();

      /*Serial.print("T: "); Serial.println(temp);
      Serial.print("A: "); Serial.println(contaminacion);
      Serial.print("L: "); Serial.println(luz);*/
    }
  }

  // Enviar datos a Adafruit IO solo cada 10 segundos
  if (millis() - ultimoEnvio >= ENVIO_INTERVALO) {
    ultimoEnvio = millis();
    //Serial.println("Enviando datos a Adafruit IO...");
    feedT->save(temp);
    feedA->save(contaminacion);
    feedL->save(luz);
  }
}

// Control de LED desde Adafruit IO
void handleMessageControl(AdafruitIO_Data *data) {
  //Serial.print("received <- ");
  Serial.println(data->value());
  //digitalWrite(LedR, atoi(data->value()) == 1 ? HIGH : LOW);
}


