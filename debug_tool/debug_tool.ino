void setup() {
  // PORTS //
  Serial3.begin(9600);              // set up serial port for 9600 baud
  pinMode(12, INPUT_PULLUP);        // debug on/off
  pinMode(11, INPUT_PULLUP);        // mode toggle

  // LCD SETUP //
  delay(1000);                      // wait for display to boot
  Serial3.write("                                    ");
  startlcd();
}

// Variables
const int varNum = 5;             // Number of variables to display
int a = 200;
float b = 200.000;
String c = "Two Hundred!!";
String d = "Two Hunnned and lots of characters this is a long string";
int e = 9001;
String varName[varNum] = {"a", "b", "c", "d", "e"};           // Array containing names of variables
String varValue[varNum] = {String(a), String(b), String(c), String(d), String(e)};          // Array containing values of variables
String displayString = "empty";

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
int mode = 0;
int setMode(int mode){
  bool newbutton = digitalRead(11);
  if (!newbutton && oldbutton){
    if (mode == (varNum - 1)){
      mode = 0;
    }
    else{
      mode++;
    }
  }
  
  oldbutton = newbutton;
  return mode;
}

// Returns string to display given mode number
String callMode(int mode){
  String Stringg = (varName[mode] + " = " + varValue[mode]);
  if (Stringg.length() > 32){                                    // length error checking
    Stringg = ("Error:          Message too long");
  }
  return (make32(Stringg));
}

// Makes strings 32 characters long
String blank = "                               ";
String make32(String input){
  input = input + blank;
  input = input.substring(0, 32);
  return input;
}

// LOOP
void loop() {
  startlcd();
  
  if (digitalRead(12)==HIGH){         // recording mode
    displayString = make32("Logging data");  
  }
  else if (digitalRead(12)==LOW){     // debug mode
    mode = setMode(mode);             // update mode
    displayString = callMode(mode);       // pull stuff from mode to display
  }
  else{
    displayString = "Error: debug switch not readable";
  }
  
  Serial3.print(displayString);      // print string to LCD
}
