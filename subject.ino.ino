#include<ESP8266WiFi.h>
#include<Servo.h>
#define ZhuanDong D3
#define Move1 D6
#define Move2 D7
#define Turn1 D4
#define Turn2 D5
#define Echo D2
#define Trig D8
Servo ZhuanDongjiqi;
char* wifiname = "wififormatch";
char* password = "18220000911";

int port = 8888;          //端口号
WiFiServer server(port);  // 设置服务器端口号

void getwifi()
{
  WiFi.mode(WIFI_STA);                          // 设置STA模式
  WiFi.begin(wifiname, password);               //连接网络
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

}

long gettime()
{
  digitalWrite(Trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig,LOW);
  return pulseIn(Echo,HIGH);
}

void carbegin()
{
  pinMode(Move1, OUTPUT);
  pinMode(Move2, OUTPUT);
  pinMode(Turn1, OUTPUT);
  pinMode(Turn2, OUTPUT);
}
void qian()              //控制前进
{
  digitalWrite(Move1, HIGH);
  digitalWrite(Move2, LOW);
}
void hou()
{
  digitalWrite(Move1, LOW);
  digitalWrite(Move2, HIGH);
}
void ting()
{
  digitalWrite(Move1, LOW);
  digitalWrite(Move2, LOW);
}
void zuo()
{
  digitalWrite(Turn1, HIGH);
  digitalWrite(Turn2, LOW);
}
void zheng()
{
  digitalWrite(Turn1, LOW);
  digitalWrite(Turn2, LOW);
}
void you()
{
  digitalWrite(Turn1, LOW);
  digitalWrite(Turn2, HIGH);
}
void setup()
{
  pinMode(Echo,INPUT);
  pinMode(Trig,OUTPUT);
  Serial.begin(115200);
  ZhuanDongjiqi.attach(ZhuanDong);
  getwifi();
  carbegin();
  server.begin();              //启动服务器

}

void loop()
{
  char cmd;
  int n;
  long distance;
  WiFiClient client = server.available();      //服务初始化
  while (client.connected())                   //等待客户端连接
  {
    while (client.available() > 0)             //有数据出现
    {
      cmd = client.read();                     //读取数据
      Serial.println(cmd);
      distance=gettime()/58;
      Serial.print("目前距前方距离为");
      Serial.println(distance);
      if(distance<15)
      {
        hou();
        ZhuanDongjiqi.write(90);
        delay(500);
        ting();
        delay(1000);
        qian();zuo();
        delay(1000);

        you();
        delay(600);
        ZhuanDongjiqi.write(220);
        ting();zheng();

        n=1;
      }
      else{n=0;}
      if(n==0){
      switch (cmd)
      {
        case 'q':
          qian();
          break;
        case 'h':
          hou();
          break;
        case 'z':
          zuo();
          break;
        case 'y':
          you();
          break;
          case 's':
          ting();
          break;
          case 'd':
          zheng();
          break;
      }
      }
    }
  }
}


