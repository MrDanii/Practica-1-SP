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

/**
 * Método con la Configuración inicial del sketch, el cual se ejecuta una vez
 */
void setup() {
  pinMode(rojoC, OUTPUT);
  pinMode(ambarC, OUTPUT);
  pinMode(verdeC, OUTPUT);
  pinMode(rojoP, OUTPUT);
  pinMode(verdeP, OUTPUT);
  pinMode(botonP, INPUT);
  Serial.begin(9600);
}

/**
 * Metodo que se iterara indefinidamente durante la ejecución del sketch
 */
void loop() {
  activarCoche();
  if(digitalRead(botonP) == HIGH){
    valorPerilla = analogRead(perilla) * 15;
    Serial.println(valorPerilla);           //Centinela: tiempo agregado de espera de solicitud
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
  parpadearLed(verdeC, 3, 1000);
  digitalWrite(ambarC, HIGH);
  delay(TIEMPO_AMBAR);
  //Estado #3
  digitalWrite(ambarC, LOW);
  digitalWrite(rojoC, HIGH);  
  delay(TIEMPO_ESPERA);         //se agrega para que haya un pequeño tiempo el rojo de los coches y el verde de los peatones
  tone(bocina, 440);            //activamos la bocina, cuando el peatón pueda cruzar
  digitalWrite(verdeP, HIGH);
  digitalWrite(rojoP, LOW);
  delay(TIEMPO_ROJO);           //El tiempo que durará el verde para los peatones
  parpadearLed(verdeP, 3, 1000);
  digitalWrite(verdeP, LOW);
  digitalWrite(rojoP, HIGH);
  tone(bocina, 640);  
  delay(TIEMPO_ESPERA);          //otro tiempo de espera
  noTone(bocina);
  digitalWrite(rojoC, LOW);    
}

/**
 * Método para parpadear hacer parpadear un led un numero especifico de veces, con un tiempo determinado
 * @param nPin numero de pin en donde se encuentra nuestro LED en la placa
 * @param nParpadeos numero de parpadeos que habrá dentro del intervalo de tiempo, definido en "nTiempo"
 * @param nTiempo tiempo en milisegundos, del parpadeo
 */
void parpadearLed(int nPin, int nParpadeos, int nTiempo){
  while(nParpadeos > 0){
    digitalWrite(nPin, HIGH);
    delay(nTiempo/2);  
    digitalWrite(nPin, LOW);
    delay(nTiempo/2);  
    nParpadeos--;
  }
}
