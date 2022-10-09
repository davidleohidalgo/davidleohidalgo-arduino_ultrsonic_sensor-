
// SENSOR DE ULTRASONIDO CON PANTALLA LCD

// Llamado de libreria de la pantalla LCD
#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

//Definicion de Pins y Variables del sensor de distancia
const int trigPin = 4;
const int echoPin = 3;
long duracion;
int distancia;
int ultimaDistancia = 0;

// Define Pins del led RGB
#define RED 48
#define GREEN 50
#define BLUE 52 

void setup() {
 pinMode (trigPin, OUTPUT);
 pinMode (echoPin, INPUT);

 Serial.begin (9600);

lcd.begin(16, 2);
lcd.print(distancia);

pinMode(RED, OUTPUT);
pinMode(GREEN, OUTPUT);
pinMode(BLUE, OUTPUT);
digitalWrite(RED, LOW);
digitalWrite(GREEN, HIGH);
digitalWrite(BLUE, LOW);
}

void loop() {
  digitalWrite(trigPin, LOW); //apagar sensor en estado inicial
  delayMicroseconds(2); // tiempo de apagado del sensor  

  digitalWrite(trigPin, HIGH); // Start Sensor
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duracion = pulseIn(echoPin, HIGH); // Secuencia de funcionamiento del Sensor
  distancia = (duracion * 0.034) / 2;

  if(distancia != ultimaDistancia)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Distancia: ");
    lcd.print(distancia);
    lcd.print(" cm");
    ultimaDistancia = distancia;
 }
  
  delay(500);
  Serial.println(distancia); 

// Secuencia de luces LEDS

  if(distancia <= 10)
  {
    digitalWrite(RED, HIGH);
    digitalWrite(GREEN, LOW);
    digitalWrite(BLUE, LOW);
    tone(2, 1047, 1000);  // Activacion del Buzzer
    delay (700);
  }
 else if(distancia > 10  && distancia <= 20)
  {
    digitalWrite(RED, LOW);
    digitalWrite(GREEN, LOW);
    digitalWrite(BLUE, HIGH);
  }
 else if(distancia > 20)
  {
    digitalWrite(RED, LOW);
    digitalWrite(GREEN, HIGH);
    digitalWrite(BLUE, LOW);
  }
}
