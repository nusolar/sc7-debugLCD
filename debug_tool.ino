void setup() {
  // PORTS //
  Serial3.begin(9600);              // set up serial port for 9600 baud
  pinMode(13, INPUT_PULLUP);        // power on/off
  pinMode(12, INPUT_PULLUP);        // debug on/off
  pinMode(11, INPUT_PULLUP);        // mode toggle

  // LCD SETUP //
  delay(1000);                      // wait for display to boot
  Serial3.write("                                    ");
  startlcd();
}

// Tells LCD a command is coming
void com() {
  Serial3.write(254);
}

// Moves cursor to start
void startlcd(){
  com();
  Serial3.write(128);
}

// Update the mode if button is pushed
bool oldbutton = 0;
bool newbutton;
int modeUpdate(int mode){
  newbutton = digitalRead(11);
  if (!newbutton && oldbutton){
    if (mode == 3){
      mode = 1;
    }
    else{
    mode++;
    }
  }
  oldbutton = newbutton;
  
  return mode;
}

// Mode return values
String modeOne(){
  return ("Power is on, Debug is on, Mode 1");
}

String modeTwo(){
  return ("Power is on, Debug is on, Mode 2");
}

String modeThree(){
  return ("Power is on, Debug is on, Mode 3");
}

// Makes strings 32 characters long
String blank = "                               ";
String make32(String input){
  input = input + blank;
  input = input.substring(0, 32);
  return input;
}

// Variables
int mode = 1;
String displayString = "empty";

void loop() {
  startlcd();
  mode = modeUpdate(mode);
  
  if (digitalRead(13)==HIGH){
    displayString = "Power is off";      // power is off
  }
  else if (digitalRead(13)==LOW && digitalRead(12)==HIGH){      // recording mode
    displayString = "Power is on, Debug is off";  
  }
  else if (digitalRead(13)==LOW && digitalRead(12)==LOW){        // debug mode
    if (mode == 1){                  // mode 1
      displayString = modeOne();
    }
    else if (mode == 2){             // mode 2
      displayString = modeTwo();
    }
    else if (mode == 3){              // mode 3
      displayString = modeThree(); 
    }    
  }
  
  Serial3.print(make32(displayString));      // print string to LCD
}
