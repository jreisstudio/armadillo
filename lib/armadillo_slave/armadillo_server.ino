/**
* New Wifly HQ simplified server.
* in fact I only readed the Wifly Server example code, and refactored that to be more simple understanding.
*
*/

/**
The default #workAround to silence compiler warning generations (Progmen and PSTR bug)
**/
#undef PROGMEM 
#define PROGMEM __attribute__(( section(".progmem.data") )) 
#undef PSTR 
#define PSTR(s) (__extension__({static prog_char __c[] PROGMEM = (s); &__c[0];})) 
#include <WiFlyHQ.h>
#include <SoftwareSerial.h>
/*Maybe yor shield use another RX /TX pin... so maybe you should change that! */
SoftwareSerial wifiSerial(4,5);
char buf[80];
WiFly wifly;
/*Now some  configurations var that you need to change...*/
const char network_ssid[] = "<<network>>";
const char network_password[] = "<<password>>";

/*The methods declaration...yeap, it's C and will not work untill you put every method here!*/
void   serial_start();
void join_network();
void server_start(char *server_name);
void default_header();
void send_404();
void on_pin(int pin);
void off_pin(int pin);

void pin2_listener_on();
void pin3_listener_on();
void pin6_listener_on();
void pin7_listener_on();
void pin8_listener_on();
void pin9_listener_on();
void pin10_listener_on();
void pin11_listener_on();
void pin12_listener_on();
void pin13_listener_on();
void pin2_listener_off();
void pin3_listener_off();
void pin4_listener_off();
void pin5_listener_off();
void pin6_listener_off();
void pin7_listener_off();
void pin8_listener_off();
void pin9_listener_off();
void pin10_listener_off();
void pin11_listener_off();
void pin12_listener_off();
void pin13_listener_off();

/* OK lets use that!*/
void setup(){
  serial_start();
  join_network();
  server_start("WebServer_Wifly");
  //default_setup();
}

void loop(){
/*Humm.. is somenone Requesting me?*/
  if (wifly.available() > 0) {
    if (wifly.gets(buf, sizeof(buf))) {
      /*Nice! what can i serve to you?*/
     router();
    }
  }
}


void serial_start(){
  Serial.begin(115200);
  wifiSerial.begin(9600);
  if (!wifly.begin(&wifiSerial, &Serial)) {
    Serial.println(F("[Serial] - Failed."));
    wifly.terminal();
  }
}

void join_network(){
  if (!wifly.isAssociated()) {
    wifly.setSSID(network_ssid);
    wifly.setPassphrase(network_password);
    wifly.enableDHCP();
    wifly.save();    
    if (wifly.join()) {
      Serial.println(F("[Network] Joined!"));
    } else {
      Serial.println(F("[Network] - Failed to join."));
      wifly.terminal();
    }    
  }else{
    Serial.println(F("[Network]Already joined.")); 
  }
  wifly.setBroadcastInterval(0);  // Turn off UPD broadcast
  Serial.print(F("[Network]MAC/IP:")); 
  Serial.print(wifly.getMAC(buf, sizeof(buf)));
  Serial.print(F(" / "));
  Serial.println(wifly.getIP(buf, sizeof(buf)));
}

void server_start(char *server_name){
  wifly.setDeviceID(server_name);
  if (wifly.isConnected()) {
    Serial.println(F("[Server] Old connection active. Closing"));
    wifly.close();
  }
  wifly.setProtocol(WIFLY_PROTOCOL_TCP);
  if (wifly.getPort() != 80) {
    wifly.setPort(80);
    wifly.save();
    Serial.println(F("[Server] Set port to 80."));
    wifly.reboot();
    delay(3000);
  }
    Serial.print(F("[Server] The "));  
    Serial.print(wifly.getDeviceID(buf, sizeof(buf)));
    Serial.println(F(" is ready"));  
}


void default_header(){
    wifly.println(F("HTTP/1.1 200 OK"));
    wifly.println(F("Content-Type: text/html"));
    wifly.println(F("Transfer-Encoding: chunked"));
    wifly.println();    
    wifly.sendChunkln(F("<html>"));
    wifly.sendChunkln(F("</html>"));
    wifly.sendChunkln();    
}
void send_404(){
  wifly.flushRx();
  wifly.println(F("HTTP/1.1 404 Not Found"));
  wifly.println(F("Content-Type: text/html"));
  wifly.println(F("Transfer-Encoding: chunked"));
  wifly.println();
  wifly.sendChunkln(F("<html><head>"));
  wifly.sendChunkln(F("<title>404 Not Found</title>"));
  wifly.sendChunkln(F("</head><body>"));
  wifly.sendChunkln(F("<h1>Not Found</h1>"));
  wifly.sendChunkln(F("<hr>"));
  wifly.sendChunkln(F("</body></html>"));
  wifly.sendChunkln();
}

/*digital pin listener on */

void on_pin(int pin){
    if(digitalRead(pin) ==LOW){
      pinMode(pin, OUTPUT);
      digitalWrite(pin, HIGH);
    }  
}


void off_pin(int pin){
    if(digitalRead(pin) ==HIGH){
      pinMode(pin, OUTPUT);
      digitalWrite(pin, LOW);
    }  
}

void router(){

  if (strncmp_P(buf, PSTR("GET /digital/02/on"), 18) == 0) {
    on_pin(2);    
    default_header();
  } else if (strncmp_P(buf, PSTR("GET /digital/03/on"), 18) == 0) {
    on_pin(3);    
    default_header();
  } else if (strncmp_P(buf, PSTR("GET /digital/06/on"), 18) == 0) {
    on_pin(6);    
    default_header();
  } else if (strncmp_P(buf, PSTR("GET /digital/07/on"), 18) == 0) {
    on_pin(7);    
    default_header();
  } else if (strncmp_P(buf, PSTR("GET /digital/08/on"), 18) == 0) {
    on_pin(8);   
    default_header();
  } else if (strncmp_P(buf, PSTR("GET /digital/09/on"), 18) == 0) {
    on_pin(9);    
    default_header();
  } else if (strncmp_P(buf, PSTR("GET /digital/10/on"), 18) == 0) {
    on_pin(10);    
    default_header();
  } else if (strncmp_P(buf, PSTR("GET /digital/11/on"), 18) == 0) {
    on_pin(11);    
    default_header();
  } else if (strncmp_P(buf, PSTR("GET /digital/12/on"), 18) == 0) {
    on_pin(12);    
    default_header();
  } else if (strncmp_P(buf, PSTR("GET /digital/13/on"), 18) == 0) {
    on_pin(13);    
    default_header();
  } else if (strncmp_P(buf, PSTR("GET /digital/02/off"), 19) == 0) {
    off_pin(2);
    default_header();
  } else if (strncmp_P(buf, PSTR("GET /digital/03/off"), 19) == 0) {
    off_pin(3);
    default_header();
  } else if (strncmp_P(buf, PSTR("GET /digital/06/off"), 19) == 0) {
    off_pin(6);
    default_header();
  } else if (strncmp_P(buf, PSTR("GET /digital/07/off"), 19) == 0) {
    off_pin(7);
    default_header();
  } else if (strncmp_P(buf, PSTR("GET /digital/08/off"), 19) == 0) {
    off_pin(8);
    default_header();
  } else if (strncmp_P(buf, PSTR("GET /digital/09/off"), 19) == 0) {
    off_pin(9);
    default_header();
  } else if (strncmp_P(buf, PSTR("GET /digital/10/off"), 19) == 0) {
    off_pin(10);
    default_header();
  } else if (strncmp_P(buf, PSTR("GET /digital/11/off"), 19) == 0) {
    off_pin(11);
    default_header();
  } else if (strncmp_P(buf, PSTR("GET /digital/12/off"), 19) == 0) {
    off_pin(12);
    default_header();
  } else if (strncmp_P(buf, PSTR("GET /digital/13/off"), 19) == 0) {
    off_pin(13);
    default_header();
  } else{
    send_404();
  }  
}

