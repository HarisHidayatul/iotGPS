#include <TinyGPS++.h>
#include <SoftwareSerial.h>
SoftwareSerial SIM900A(10, 11); // RX | TX
// Connect the SIM900A TX to Arduino pin 10 RX.
// Connect the SIM900A RX to Arduino pin 11 TX.

#define timeout 2000

double latt = 0.1;
double lngg = 0.1;
int countTimeout = 0;
bool respOK = false;
bool respER = false;
int countt = 0;
int countgps = 0;

char c = ' ';

const char simString[][35] = {"AT+CGATT=1",
                              "AT+CSTT=\"indosatgprs\",\"\",\"\"",
                              "AT+CIICR",
                              "AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"",
                              "AT+SAPBR=3,1,\"APN\",\"indosatgprs\"",
                              "AT+SAPBR=1,1",
                              "AT+HTTPINIT",
                              "AT+HTTPPARA",
                              "AT+HTTPPARA=\"CID\",1",
                              "AT+HTTPACTION=0",
                              "AT+HTTPREAD",
                              "AT+HTTPTERM",
                              //"AT+SAPBR=0,1"
                              "AT"
                             };
void readRespon()
{
  String a = "";
  while (SIM900A.available() > 0)
  {
    countTimeout = 0;
    a = SIM900A.readString();
    Serial.print(a);
    //Serial.println(a.length());
  }
  
  if (countTimeout > timeout)
  {
    countTimeout = 0;
    countt=0;
    SIM900A.println("AT+HTTPTERM");
    delay(1000);
    SIM900A.println("AT+SAPBR=0,1");
    delay(1000);
    SIM900A.println("AT+CIPSHUT");
    delay(1000);
  }
  
  if (a.length() == 0)
  {
    delay(1);
    countTimeout++;
    //Serial.println(countTimeout);
  }
  else
  {
    Serial.println(a.length());
    if (countt == 0)
    {
      SIM900A.println(simString[countt]);
      countt++;
    } else
    {
      for (int i = 0; i < (a.length() - 1); i++)
      {
        if ((a[i] == 'O') && (a[i + 1] == 'K'))
        {
          delay(100);
          SIM900A.print(simString[countt]);
          if (countt == 7)
          {
            SIM900A.print("=\"URL\",\"http://harishidayatulloh.my.id/iot/gps/changeValue.php?lat=");
            SIM900A.print(latt, 6);
            SIM900A.print("&lng=");
            SIM900A.print(lngg, 6);
            SIM900A.println("&id=1\"");
          } else
          {
            SIM900A.println();
          }
          countt++;
          if (countt > 12)
          {
            countt = 6;
          }
          break;
        }
      }
    }
  }

  /*
    for (int i = 0; i < (a.length()-1); a++)
    {
    if (a[i] == 'O') {
      respOK = true;
    }
    if (a[i+1] == 'K')
    {
      if (respOK)
      {
        delay(100);
        SIM900A.print(simString[countt]);
        if (countt == 7)
        {
          SIM900A.print("=\"URL\",\"http://harishidayatulloh.my.id/iot/gps/changeValue.php?lat=");
          SIM900A.print(latt, 6);
          SIM900A.print("&lng=");
          SIM900A.print(lngg, 6);
          SIM900A.println("&id=1\"");
        } else
        {
          SIM900A.println();
        }
        countt++;
        if (countt > 13)
        {
          countt = 6;
        }
        respOK = false;
      }
    }
    }*/
}
void setup() {
  // put your setup code here, to run once:
  // start th serial communication with the host computer
  Serial.begin(9600);
  SIM900A.begin(9600);
}

void loop() {
  readRespon();
  latt = latt+0.01;
  lngg = lngg+0.01;
  /*
    if(gpsSerial.available() > 0)
    if (gps.encode(gpsSerial.read()))
      displayInfo();
    /*
    initSIM();
    //SIM900A.println("AT+HTTPPARA=\"URL\",\"http://harishidayatulloh.my.id/iot/gps/changeValue.php?lat=0.7&lng=0.9&id=1\"");
    SIM900A.print("AT+HTTPPARA=\"URL\",\"http://harishidayatulloh.my.id/iot/gps/changeValue.php?lat=");
    SIM900A.print(latt,6);
    SIM900A.print("&lng=");
    SIM900A.print(lngg,6);
    SIM900A.println("&id=1\"");
    receive_message();
    delay(1000);
    SIM900A.println("AT+HTTPACTION=1");
    //findError();
    receive_message();
    delay(1000);
    latt = latt+0.01;
    lngg = lngg+0.01;
    /*
    SIM900A.println("AT+CIPSHUT");
    receive_message();
    delay(1000);
    SIM900A.println("AT+SAPBR=0,1");
    receive_message();
    delay(1000);*/
}
