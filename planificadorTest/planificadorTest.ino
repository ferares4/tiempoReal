/*Representacion de señal en 32 muestras*/
float tabla[32]={0, 0.199367934, 0.390731128, 0.555570233, 0.707106781, 0.831469612, 0.923879533, 0.98078528, 1, 0.979924705, 0.923879533, 0.831469612, 0.707106781, 0.555570233, 0.382683432, 0.195090322, 0, -0.195090322, -0.382683432, -0.555570233,
-0.707106781, -0.831469612, -0.923879533, -0.98078528, -1, -0.98078528, -0.923879533, -0.831469612, -0.707106781, -0.555570233, -0.382683432, -0.195090322};

/*Variables de tareas*/
float tablaUltimoValor[10] = {0,0,0,0,0,0,0,0,0,0};
long tiemposInicio[10] = {0,0,0,0,0,0,0,0,0,0};
long tiemposFin[10] = {0,0,0,0,0,0,0,0,0,0};
long contadoresTarea[10] = {0,0,0,0,0,0,0,0,0,0};

/*Configuracion de tareas*/
int intervalos[10] = {615,1155,2287,4253,4496,4897,6132,6179,6581,6647};
int tiemposDelay[10] = {132,102,24,790,146,205,311,545,1891,994};

/*Configuracion Inicial*/
long tiempoSistema = 0;
int cantidadDeTareas=10;
boolean finalizado=false;

void setup() {
  Serial.begin(9600);  
}

float leerTabla(int i){
  return tabla[i]; 
}

void ejecutarTarea(int numero){
  if (contadoresTarea[numero] < 32){
    float valor = leerTabla(contadoresTarea[numero]);
    tablaUltimoValor[numero]=valor;
    contadoresTarea[numero]++;  
  }
  else{
    if(numero==cantidadDeTareas-1){
      exit;
    }
    contadoresTarea[numero]=0;
    ejecutarTarea(numero);  
  }  
  delay(tiemposDelay[numero]);
}

void loop() {
  //while (finalizado!=true){    
   long tiempoSistema = millis();
   /* Imprime el ultimo tiempo de cada tarea en una linea */
   for (int tarea=0;tarea<cantidadDeTareas;tarea++){
    Serial.print(tablaUltimoValor[tarea],9);
      if (tarea<cantidadDeTareas-1){
        Serial.print("|");
      }
   }
   /* Simula la ejecucion de cada tarea con prioridad y sin desalojo */
   for (int tarea=0; tarea < cantidadDeTareas; tarea ++){
    if (tiempoSistema-tiemposFin[tarea] > intervalos[tarea]){ 
      tiemposInicio[tarea] = millis();
      ejecutarTarea(tarea);
      tiemposFin[tarea] = millis();
    }
   }
   Serial.println("");
  //}
}
