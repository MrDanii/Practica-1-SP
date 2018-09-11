//constantes de tiempo para cada color
int TIEMPO_ROJO = 10000;   //10 segundos
int TIEMPO_AMBAR = 2000;   // 2 segundos
int TIEMPO_VERDE = 10000;  //10 segundos
int TIEMPO_ESPERA = 1000;     // 1 segundo

//Variables para los led del semaforo
  //Semaforo Automoviles
#define rojoC 13
#define ambarC 12
#define verdeC 11
  //Semaforo Peaton
#define rojoP 9
#define verdeP 8

#define botonP 3
#define perilla A5          //Potenciometro para regular el tiempo del led verde de los coches, cuando se inicia la petición del peatón
int valorPerilla = 0;
//Funcionalidad Extra, Activar un sonido para los peatones
#define bocina 2

void setup() {
  pinMode(rojoC, OUTPUT);
  pinMode(ambarC, OUTPUT);
  pinMode(verdeC, OUTPUT);
  pinMode(rojoP, OUTPUT);
  pinMode(verdeP, OUTPUT);
  pinMode(botonP, INPUT);
  Serial.begin(9600);
}

void loop() {
  activarCoche();
  if(digitalRead(botonP) == HIGH){
    valorPerilla = analogRead(perilla) * 15;
    Serial.println(valorPerilla);         //Centinela: tiempo agregado de espera de solicitud
    delay(TIEMPO_VERDE + valorPerilla);     //#4 estado, tiempo de espera de la solicitud, es decir, un tiempo mínimo del led verde en los coches, antes de activar el semaforo del peaton
    activarPeaton();
  }
}

/**
 * Método para activar el verde en el semáforo de coches,cuando no hay peticion de un peaton
 * el semáforo para los coches siempre estará en verde, hasta que se inicie una peticion
 */
void activarCoche (){
  //Estado #1
  digitalWrite(verdeC, HIGH);
  digitalWrite(rojoP, HIGH);
}

/**
 * Método para activar el funcionamiento del semáforo de los peatones,
 */
void activarPeaton (){
  //Estado #2
  digitalWrite(verdeC, LOW);
  digitalWrite(ambarC, HIGH);
  delay(TIEMPO_AMBAR);
  //Estado #3
  digitalWrite(ambarC, LOW);
  digitalWrite(rojoC, HIGH);
  delay(TIEMPO_ESPERA);      //se agrega para que haya un pequeño tiempo el rojo de los coches y el verde de los peatones
  tone(bocina, 440);         //activamos la bocina, cuando el peatón pueda cruzar
  digitalWrite(verdeP, HIGH);
  digitalWrite(rojoP, LOW);
  delay(TIEMPO_ROJO);       //EL tiempo que durará el verde para los peatones
  digitalWrite(verdeP, LOW);
  digitalWrite(rojoP, HIGH);
  tone(bocina, 640);  
  delay(TIEMPO_ESPERA);       //otro tiempo de espera
  noTone(bocina);
  digitalWrite(rojoC, LOW);  
}
