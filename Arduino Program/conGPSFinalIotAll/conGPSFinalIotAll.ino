#include <TinyGPS++.h>
#include <SoftwareSerial.h>

#define timeout 2000

// Choose two Arduino pins to use for software serial
int RXPin = 2;
int TXPin = 3;

int GPSBaud = 9600;


// Create a TinyGPS++ object
TinyGPSPlus gps;

// Create a software serial port called "gpsSerial"
SoftwareSerial gpsSerial(RXPin, TXPin);

double latt = 0;
double lngg = 0;
int countTimeout = 0;
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
  while (Serial.available() > 0)
  {
    countTimeout = 0;
    a = Serial.readString();
    //.println(a.length());
  }
  
  if (countTimeout > timeout)
  {
    countTimeout = 0;
    countt=0;
    Serial.println("AT+HTTPTERM");
    delay(1000);
    Serial.println("AT+SAPBR=0,1");
    delay(1000);
    Serial.println("AT+CIPSHUT");
    delay(1000);
  }
  
  if (a.length() == 0)
  {
    delay(1);
    countTimeout++;
    //.println(countTimeout);
  }
  else
  {
    if (countt == 0)
    {
      Serial.println(simString[countt]);
      countt++;
    } else
    {
      for (int i = 0; i < (a.length() - 1); i++)
      {
        if ((a[i] == 'O') && (a[i + 1] == 'K'))
        {
          delay(100);
          Serial.print(simString[countt]);
          if (countt == 7)
          {
            Serial.print("=\"URL\",\"http://piranti2022.harishidayatulloh.my.id/iot/gps/changeValue.php?lat=");
            Serial.print(latt, 6);
            Serial.print("&lng=");
            Serial.print(lngg, 6);
            Serial.println("&id=1\"");
          } else
          {
            Serial.println();
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
        Serial.print(simString[countt]);
        if (countt == 7)
        {
          Serial.print("=\"URL\",\"http://harishidayatulloh.my.id/iot/gps/changeValue.php?lat=");
          Serial.print(latt, 6);
          Serial.print("&lng=");
          Serial.print(lngg, 6);
          Serial.println("&id=1\"");
        } else
        {
          Serial.println();
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
  // start th  communication with the host computer
  Serial.begin(9600);

  // Start the software serial port at the GPS's default baud
  gpsSerial.begin(GPSBaud);
}

void loop() {
  readRespon();
  while (gpsSerial.available() > 0)
    if (gps.encode(gpsSerial.read()))
      displayInfo();
  /*
    if(gps.available() > 0)
    if (gps.encode(gps.read()))
      displayInfo();
    /*
    initSIM();
    //Serial.println("AT+HTTPPARA=\"URL\",\"http://harishidayatulloh.my.id/iot/gps/changeValue.php?lat=0.7&lng=0.9&id=1\"");
    Serial.print("AT+HTTPPARA=\"URL\",\"http://harishidayatulloh.my.id/iot/gps/changeValue.php?lat=");
    Serial.print(latt,6);
    Serial.print("&lng=");
    Serial.print(lngg,6);
    Serial.println("&id=1\"");
    receive_message();
    delay(1000);
    Serial.println("AT+HTTPACTION=1");
    //findError();
    receive_message();
    delay(1000);
    latt = latt+0.01;
    lngg = lngg+0.01;
    /*
    Serial.println("AT+CIPSHUT");
    receive_message();
    delay(1000);
    Serial.println("AT+SAPBR=0,1");
    receive_message();
    delay(1000);*/
}
void displayInfo()
{
  if (gps.location.isValid())
  {
    latt = gps.location.lat();
    lngg = gps.location.lng();
  }
}
