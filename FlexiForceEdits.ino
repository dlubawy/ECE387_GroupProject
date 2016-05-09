//From the bildr article http://bildr.org/2012/11/flexiforce-arduino/

int flexiForcePin = A0; //analog pin 0
int transPin = 7;
int n = 0;

void setup(){
  //Pin for transisto r gate
  pinMode(2, OUTPUT);
  pinMode(7, OUTPUT);
  Serial.begin(9600);
  //Turn alarm on
  digitalWrite(2, HIGH);
  digitalWrite(7, LOW);
}

void loop(){
  //Read pressure sensor
  int flexiForceReading = analogRead(flexiForcePin); 
  //Increment n for readings over 150
  if(flexiForceReading > 150){
    n++;
  }
  //Turn off alarm if n reaches 20 loops or 5 seconds
  if(n >= 20) {
    digitalWrite(2, LOW);
    digitalWrite(7, HIGH);
  }
  //Serial monitor troubleshooting
  Serial.print(flexiForceReading);
  Serial.print(" ");
  Serial.println(n);
  Serial.print("transceiver pin "); Serial.println(digitalRead(transPin));
  delay(250); //just here to slow down the output for easier reading
}
