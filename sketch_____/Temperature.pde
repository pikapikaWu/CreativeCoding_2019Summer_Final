class Temperature {
  private int x;
  private int y;
  private int data;
  private float warnTem=50;
  Temperature (int x, int y) {
    this.x=x;
    this.y=y;
  }
  void setWarnTem (float tem) {
    warnTem=tem;
  }

  void warning() {
    if (data>warnTem)
      fill(255, 0, 0);
    else             
    fill(0, 255, 0);
    ellipse(x+100, y, 30, 30);
  }

  void Shape() {
    fill(255, 0, 0);
    ellipse(x+25, y+350, 80, 80);
    noStroke();
    rect(x+1, y+300, 49, 30);
    stroke(0);
    fill(255);
    for (int i=0; i<31; i++) {
      line(x-15, y+10*i, x-10, y+10*i);
      if (i%5==0) {
        line(x-20, y+10*i, x-10, y+10*i);
        fill(0);
        text(50-i+"°C", x-45, y+10*i);
        fill(255);
        continue;
      }
    }
  }
  
  void update (String data) {        
    this.data=Integer.parseInt(data);              
    if (this.data>20) {                     
      fill(255, 0, 0);        
      rect(x+1, y+500-this.data*10, 49, this.data*10-200);
      stroke(255);           
      line(x+1, y+500-warnTem*10, x+49, y+300-warnTem*10+200);            
      noStroke();  
    }
  }
}
