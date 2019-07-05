class Humidity {
  private int x;  
  private int y;    
  private int data;  
  private float warnHum=90; 
  Humidity(int x, int y) {
    this.x=x;         
    this.y=y;
  }     
  void setWarnHum(float hum) {
    warnHum=hum;
  }     
  void warning() {
    if (data>warnHum)
      fill(255, 0, 0);         
    else
      fill(0, 255, 0); 
    ellipse(x-50, y, 30, 30);
  }     

  void Shape() {
    fill(50, 50, 255);
    ellipse(x+25, y+350, 80, 80);
    noStroke();
    rect(x+1, y+300, 49, 30);
    stroke(0);
    fill(255);
    for (int i=0; i<61; i++) {
      line(x+60, y+5*i, x+65, y+5*i);
      if (i%10==0) {
        line(x+60, y+5*i, x+70, y+5*i);
        fill(0);
        text(90-i, x+85, y+5*i);
        fill(255);
        continue;
      }             
      if (i%5==0) {
        line(x+60, y+5*i, x+68, y+5*i);
      }
    }
  }     

  void update(String data) {   
    this.data=Integer.parseInt(data);    
    if (this.data>30) { 
      fill(50, 50, 255);          
      rect(x+1, y+450-this.data*5, 49, this.data*5-150);
      stroke(255);
      line(x+1, y+450-warnHum*5, x+49, y+450-warnHum*5);
      noStroke();             
    }
  }
}
