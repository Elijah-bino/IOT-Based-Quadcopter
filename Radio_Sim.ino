#include <Arduino.h>
#include <Firebase_ESP_Client.h>

#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#define WIFI_SSID "dlink-9338"
#define WIFI_PASSWORD "zvgvc96724"

#define API_KEY "AIzaSyCb-WIw2e7FMh--UMFyfmWy1mEA-5veqn4"
#define DATABASE_URL "https://test-7018d-default-rtdb.asia-southeast1.firebasedatabase.app/"
//#define USER_EMAIL ""
//#define USER_PASSWORD ""

#define LED_PIN 16 // NodeMCU onboard LED pin
#define LED_PIN2 D0

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

String s;
bool signupok = false;

unsigned long previousMillis = 0;
const int loopIntervalMicros = 4000;


int throtleup_value = 0;
int throtledown_value = 0;

int yawleft_value = 0;
int yawright_value = 0;

int pitchfront_value = 0;
int pitchback_value = 0;

int rollleft_value = 0;
int rollright_value = 0;


int throtle=1000;
int yaw = 1500;
int pitch=1500;
int roll = 1500;


void handle_values(void){
  /*
  //throtle up
  if(throtleup_value == 1){
      throtle+=50;
      if(throtle>2000)throtle=2000;
  }
  if(throtleup_value == 0){
      throtle-=100;
      if(throtle<1000)throtle=1000;//hover value
  }

  //throtle down
  if(throtledown_value == 1){
      throtle=1000;
      if(throtle<1000)throtle=1000;
  }


  */
  
  //yaw left
  if(yawleft_value == 1 && yawright_value == 0){
      yaw-=50;
      if(yaw<1000)yaw=1000;
  }

  if(yawleft_value == 0 && yawright_value == 1){
      yaw+=50;
      if(yaw>2000)yaw=2000;
  }

  //yaw right
  if(yawright_value == 1 && yawleft_value == 1){
      yaw-=50;
      if(yaw<1500)yaw=1500;
  }
  if(yawright_value == 0 && yawleft_value == 0){
      //yaw-=50;
      if(yaw>1500){
        yaw = 1500;
        if(yaw<1500){
          yaw = 1500;
        }
      }
      if(yaw<1500){
        yaw = 1500;
        if(yaw>1500){
          yaw = 1500;
        }
      }
      
  }

   //pitch front
  if(pitchfront_value == 1 && pitchback_value == 0){
      pitch+=50;
      if(pitch>2000)pitch=2000;
  }

  if(pitchfront_value == 0 && pitchback_value == 1){
      pitch-=50;
      if(pitch<1000)pitch=1000;
  }

 //pitch back
  if(pitchfront_value == 1 && pitchback_value == 1){
      pitch-=50;
      if(pitch<1500)pitch=1500;
  }
  if(pitchfront_value == 0 && pitchback_value == 0){
      if(pitch>1500){
        pitch = 1500;
        if(pitch<1500){
          pitch = 1500;
        }
      }
      if(pitch<1500){
        pitch = 1500;
        if(pitch>1500){
          pitch = 1500;
        }
      }
      
  }

  //roll left
  if(rollleft_value == 1 && rollright_value == 0){
      roll-=50;
      if(roll<1000)roll=1000;
  }

  if(rollleft_value == 0 && rollright_value == 1){
      roll+=50;
      if(roll>2000)roll=2000;
  }

 //roll right
  if(rollleft_value == 1 && rollright_value == 1){
      roll=1500;
      if(roll<1500)roll=1500;
  }
  if(rollleft_value == 0 && rollright_value == 0){
      if(roll>1500){
        roll = 1500;
        if(roll<1500){
          roll = 1500;
        }
      }
      if(roll<1500){
        roll = 1500;
        if(roll>1500){
          roll = 1500;
        }
      }
      
  }

}

void read_values(void){
  if (Firebase.ready() && signupok)
  {
    // Listen for changes in the Firebase RTDB under the "test" node for LED status
    //Serial.println("waiting");
    if (Firebase.RTDB.getString(&fbdo, "/throtleup")){
      if (fbdo.dataType()=="string"){
          s = fbdo.stringData();
          throtleup_value = s.toInt();
          digitalWrite(LED_PIN, throtleup_value == 1 ? LOW : HIGH); // Turn on/off the LED based on the received status
      }
    }
    if (Firebase.RTDB.getString(&fbdo, "/throtledown")){
      if (fbdo.dataType()=="string"){
          s = fbdo.stringData();
          throtledown_value = s.toInt();          
          digitalWrite(LED_PIN2, throtledown_value == 1 ? LOW : HIGH); // Turn on/off the LED based on the received status
      }
    }
    if (Firebase.RTDB.getString(&fbdo, "/yawleft")){
      if (fbdo.dataType()=="string"){
          s = fbdo.stringData();
          yawleft_value = s.toInt();          
          digitalWrite(LED_PIN, yawleft_value == 1 ? LOW : HIGH); // Turn on/off the LED based on the received status
      }
    }
    if (Firebase.RTDB.getString(&fbdo, "/yawright")){
      if (fbdo.dataType()=="string"){
          s = fbdo.stringData();
          yawright_value = s.toInt();          
          digitalWrite(LED_PIN2, yawright_value == 1 ? LOW : HIGH); // Turn on/off the LED based on the received status
      }
    }
    if (Firebase.RTDB.getString(&fbdo, "/pitchfront")){
      if (fbdo.dataType()=="string"){
          s = fbdo.stringData();
          pitchfront_value = s.toInt();          
          digitalWrite(LED_PIN2, yawright_value == 1 ? LOW : HIGH); // Turn on/off the LED based on the received status
      }
    }
    if (Firebase.RTDB.getString(&fbdo, "/pitchback")){
      if (fbdo.dataType()=="string"){
          s = fbdo.stringData();
          pitchback_value = s.toInt();          
          digitalWrite(LED_PIN2, yawright_value == 1 ? LOW : HIGH); // Turn on/off the LED based on the received status
      }
    }
    if (Firebase.RTDB.getString(&fbdo, "/rollleft")){
      if (fbdo.dataType()=="string"){
          s = fbdo.stringData();
          rollleft_value = s.toInt();          
          digitalWrite(LED_PIN2, yawright_value == 1 ? LOW : HIGH); // Turn on/off the LED based on the received status
      }
    }
    if (Firebase.RTDB.getString(&fbdo, "/rollright")){
      if (fbdo.dataType()=="string"){
          s = fbdo.stringData();
          rollright_value = s.toInt();          
          digitalWrite(LED_PIN2, yawright_value == 1 ? LOW : HIGH); // Turn on/off the LED based on the received status
      }
    }
  }
  else{
    Serial.println(fbdo.errorReason());
  }
}


void setup() {
  pinMode(LED_PIN2, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN2, HIGH);
  delay(250);
  digitalWrite(LED_PIN2, LOW);  

  Serial.begin(57600);


  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  config.api_key = API_KEY;
  //auth.user.email = USER_EMAIL;
  //auth.user.password = USER_PASSWORD;
  config.database_url = DATABASE_URL;

  Firebase.reconnectNetwork(true);
  Firebase.begin(&config, &auth);
  while(signupok == false){
    Serial.println("connecting to database...");
    if(Firebase.signUp(&config, &auth, "", "")){
      Serial.println("connected to database");
      signupok = true;
    }
    delay(500);
  }
  
  Firebase.reconnectNetwork(true);
  Firebase.begin(&config, &auth);
  // Set initial LED status in the Firebase RTDB under the "test" node to 1
  Firebase.RTDB.setString(&fbdo, "/throtleup", 1000);
  Firebase.RTDB.setString(&fbdo, "/throtledown", 0);
  Firebase.RTDB.setString(&fbdo, "/yawleft", 0);
  Firebase.RTDB.setString(&fbdo, "/yawright", 0);
  Firebase.RTDB.setString(&fbdo, "/pitchfront", 0);
  Firebase.RTDB.setString(&fbdo, "/pitchback", 0);
  Firebase.RTDB.setString(&fbdo, "/rollleft", 0);
  Firebase.RTDB.setString(&fbdo, "/rollright", 0);

 
  digitalWrite(LED_PIN, HIGH);
  delay(250);
  digitalWrite(LED_PIN, LOW);
  
  Serial.println("i'm out of setup...");
}



void loop() {
  /*
  unsigned long currentMillis = micros();

  // Check if the desired loop interval has passed
  if (currentMillis - previousMillis >= loopIntervalMicros) {
    // Update the previousMillis to the current time
    previousMillis = currentMillis;
  */
    // Your existing loop code goes here
    read_values();
    Serial.print(throtleup_value);
    Serial.print(",");
    Serial.print(throtledown_value);
    Serial.print(",");
    Serial.print(yawleft_value);
    Serial.print(",");
    Serial.print(yawright_value);
    Serial.print(",");
    Serial.print(pitchfront_value);
    Serial.print(",");
    Serial.print(pitchback_value);
    Serial.print(",");
    Serial.print(rollleft_value);
    Serial.print(",");
    Serial.println(rollright_value);
  //}
}










