import processing.serial.*;

Serial myPort;  // Objeto puerto serial
String val;     // Variable para guardar datos del puerto serial
PrintWriter output;

void setup()
{
  String portName = Serial.list()[1]; //ajustar dependiendo la posicion del puerto usado
  output = createWriter("valores.txt"); 
  myPort = new Serial(this, portName, 9600);
}

void draw()
{                           
  if ( myPort.available() > 0) 
  {  // If data is available,
    val = myPort.readStringUntil('\n');         // leer y guardar en variable
  } 
  if (val!=null){
    output.println(val); //guarda linea en archivo
    println(val); //imprime variable en la consola                                
  }
}

void keyPressed() {
  output.flush();
  output.close();
  exit();
}