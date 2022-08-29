#include <ESP8266WiFi.h>
#include <Wire.h>

// Motor A connections
int enA = 0;
int in1 = 1;
int in2 = 2;
// Motor B connections
int in3 = 5;
int in4 = 6;
int enB = 7;

const char* ssid = "Robotic Crab";      //Your SSID
const char* password = "DUM-ESP8266"; //Your password

WiFiServer server(80);  //Service Port for http


void setup() {

  // Set all the motor control pins to outputsi
	pinMode(enA, OUTPUT);
	pinMode(enB, OUTPUT);
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	pinMode(in3, OUTPUT);
	pinMode(in4, OUTPUT);
	
	// Turn off motors - Initial state
	digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);

  pinMode(16, OUTPUT);  //LED indicator for Wi-Fi connection
  digitalWrite(16, LOW);
  Serial.begin(115200); //Baud rate
  delay(1000);

  //Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("-");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");

  digitalWrite(16, HIGH);
}


void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // Match the request

  if (request.indexOf("/F") != -1) {
    forward();
  }
  if (request.indexOf("/F3") != -1) {
    forward();
    forward();
    forward();
  }
  if (request.indexOf("/B") != -1) {
    backward();
  }
  if (request.indexOf("/B3") != -1) {
    backward();
    backward();
    backward();
  }
  if (request.indexOf("/L") != -1) {
    left();
  }
  if (request.indexOf("/L3") != -1) {
    left();
    left();
    left();
  }
  if (request.indexOf("/R") != -1) {
    right();
  }
  if (request.indexOf("/R3") != -1) {
    right();
    right();
    right();
  }

  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");
  client.println("<style>");
  client.println(".button{");

  client.println("background-color: #4CAF50; /* Green */");
  client.println("width: 48%;");
  client.println("border: none;");
  client.println("color: white;");
  client.println("padding: 50px 40px;");
  client.println("text-align: center;");
  client.println("text-decoration: none;");
  client.println("display: inline-block;");
  client.println("font-size: 50px;");
  client.println("margin: 4px 2px;");
  client.println("cursor: pointer;");
  client.println("border-radius: 12px;");
  client.println("}");

  client.println("</style>");
  client.println("</head>");
  client.println("<body bgcolor=black>");

  client.println("<button class=\"button\" onclick=\"window.location.href='/F';\">Forward</button>");
  client.println("<button class=\"button\" onclick=\"window.location.href='/F3';\">Forward (x4)</button>");
  client.println("<br></br>");
  client.println("<button class=\"button\" onclick=\"window.location.href='/B';\">Backward</button>");
  client.println("<button class=\"button\" onclick=\"window.location.href='/B3';\">Backward (x4)</button>");
  client.println("<br></br>");
  client.println("<button class=\"button\" onclick=\"window.location.href='/L';\">Left</button>");
  client.println("<button class=\"button\" onclick=\"window.location.href='/L3';\">Left (x4)</button>");
  client.println("<br></br>");
  client.println("<button class=\"button\" onclick=\"window.location.href='/R';\">Right</button>");
  client.println("<button class=\"button\" onclick=\"window.location.href='/R3';\">Right (x4)</button>");
  client.println("<br></br>");
  client.println("<button class=\"button\" onclick=\"window.location.href='/S';\">Sleep</button>");
  client.println("<button class=\"button\" onclick=\"window.location.href='/W';\">Wake</button>");
  client.println("</body>");
  client.println("</html>");

  delay(1);
  Serial.println("Client disconnected");
  Serial.println("");
}

/*----------Quadruped Functions----------*/


void forward()
{
  analogWrite(enA, 255);
	analogWrite(enB, 255);
  digitalWrite(in1, HIGH);
	digitalWrite(in2, LOW);
	digitalWrite(in3, HIGH);
	digitalWrite(in4, LOW);
	delay(2500);
  digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);
}

void backward()
{
  analogWrite(enA, 255);
	analogWrite(enB, 255);
  digitalWrite(in1, LOW);
	digitalWrite(in2, HIGH);
	digitalWrite(in3, LOW);
	digitalWrite(in4, HIGH);
	delay(2500);
  digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);
}

void left()
{
  analogWrite(enA, 255);
	analogWrite(enB, 55);
  digitalWrite(in1, HIGH);
	digitalWrite(in2, LOW);
	digitalWrite(in3, HIGH);
	digitalWrite(in4, LOW);
	delay(2500);
  digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);
}

void right()
{
  analogWrite(enA, 55);
	analogWrite(enB, 255);
  digitalWrite(in1, HIGH);
	digitalWrite(in2, LOW);
	digitalWrite(in3, HIGH);
	digitalWrite(in4, LOW);
	delay(2500);
  digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);
}
