#include <Servo.h>
#define PIN_SERVO 9
Servo myservo;
int pos = 0; 
#include <LiquidCrystal.h>
int out = 7; //7号IO口作为通信接口
int relay_pin =8;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial.begin(9600); //波特率9600
  myservo.attach(PIN_SERVO);
  pinMode(out, INPUT);  //IO口设为输入模式
  pinMode(rs, OUTPUT);
  pinMode(en, OUTPUT);
  pinMode(d4, OUTPUT);
  pinMode(d5, OUTPUT);
  pinMode(d6, OUTPUT);
  pinMode(d7, OUTPUT);
  pinMode(relay_pin, OUTPUT);
  digitalWrite(relay_pin, LOW); 
  lcd.begin(16, 2);
  lcd.setCursor(0, 0); // line 0, pos 0
  lcd.print("Good Day GPA");
  lcd.setCursor(0, 1); // line 1, pos 0
  lcd.print("H:  % T:   ");
  delay(1000);
}

void loop() {
  begin();    //起始函数，向DHT11发送起始信号
  int* b = read1(); //读取传感器数据
  display_1(b);//串口显示数据

}

void begin()
{
  pinMode(out, OUTPUT); //io 设为输出模式，是因为测量发现DHT11的上拉电流有5mA，
  //远大于输入模式下ATmega328的 io 的下拉电流，便无法得到 起始的至少28ms的低电平。
  digitalWrite(out, HIGH); //io置高
  delay(1400);      //等待1.4s,因为DHT11的采样周期为1s，这里取的稍长一些。
  digitalWrite(out, LOW); //io拉低，发送起始信号
  delay(30);        //延时至少28ms，这里取30ms
  digitalWrite(out, HIGH); //拉高
  pinMode(out, INPUT); //切换到输入模式，准备读数据
}

int* read1()
{
  int a[6] = {0, 0, 0, 0, 0, 0}; //定义数组，存放数据
  int i, j; //变量，下面用到
  int* b = new int[5]; //用b将数据返回给loop
  delayMicroseconds(40);//延时40us，等待DHT11将io拉低
  if (digitalRead(out) == 0) //io读取值为0，说明DHT11已响应，io已经被拉低
  {
    while (digitalRead(out) == 0); //等待80us的低电平结束
    delayMicroseconds(90);//等待80us的高电平结束
    for (i = 0; i < 5; i++) //5个元素，依次存放温度、湿度、校验值数据
    {
      for (j = 0; j < 8; j++) //依次读取各二进制位
      {
        while (digitalRead(out) == 0); //等待50us的低电平结束
        delayMicroseconds(40);//延时40us, 大于表示数据"0"的26-28us高电平,并小于表示数据“1”70us高电平
        if (digitalRead(out) == 0) //若io读取值为0，说明高电平时间小于40us，即为数据“0”
        {
          a[i] = a[i] | 0x00; //数据最低位取0
        }
        else//若io读取值为1，说明高电平时间大于40us，即为数据“1”
        {
          a[i] = a[i] | 0x01; //数据最高位取1
          delayMicroseconds(35);//因数据“1”高电平时间为70us，70-40=30,这里取的比30稍大，确保io已经拉低
        }
        if (j < 7) //最后一位不用移
        {
          a[i] = a[i] << 1; //得到二进制数的第一位之后，将数据左移一位
        }

      }
      b[i] = a[i]; //依次将a[]传给b[];
    }
  }
  else    //如果io读取不为0，说明io没有被拉低
  {
    Serial.print("    DHT11未响应 , ");//则认为是DHT11未响应
    for (i = 0; i < 1; i++)
    {
      b[i] = -1;
    }
  }
  return b;
}

void display_1(int b[])//显示函数
{
  float WenDu, ShiDu; //定义浮点数据类型
  ShiDu = b[0] + float(b[1]) / 10; //计算湿度。
  WenDu = b[2] + float(b[3]) / 10; //计算温度。
  digitalWrite(out, HIGH); //串口显示数据
  Serial.print(b[0], DEC);
  Serial.print(",");
  Serial.print(b[2], DEC);
  Serial.print(",");
  Serial.print("\n");
  if (WenDu>27){
    digitalWrite(relay_pin, HIGH);
      for(pos = 0; pos <= 180; pos += 1) 
  {                                  
    myservo.write(pos);               
    delay(15);                       
  } 
  for(pos = 180; pos>=0; pos-=1)   
  {                                
    myservo.write(pos);              
    delay(15);                      
  } 
    }
  lcd.setCursor(2, 1);
  lcd.print(b[0]);
  lcd.setCursor(8, 1);
  lcd.print(b[2]);
  delay(1000);
  }
