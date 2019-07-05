import processing.serial.*; 
Serial port; 
Temperature myTem=new Temperature(100, 50); 
Humidity myHum=new Humidity(400, 50);
String data;
String [] str;
float resTem=50;
float resHum=90; 

void setup() {     
  size(600, 500);     
  smooth();     
  port = new Serial(this, "COM3", 9600); 
  port.bufferUntil('\n');
} 

void draw() {
  myTem.setWarnTem(resTem);       
  myHum.setWarnHum(resHum);
  myTem.Shape(); 
  myHum.Shape();
  myTem.warning(); 
  myHum.warning();
} 

void serialEvent(Serial p) {    
  String inString = p.readString();    
  data=inString;      
  str=data.split(",");      
  myHum.update(str[0]);
  myTem.update(str[1]);       
  println("Hum"+str[0]);
  println("Tem"+str[1]);
}
