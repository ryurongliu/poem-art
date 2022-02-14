/*
 Display all the fast rendering fonts.

 This sketch uses the GLCD (font 1) and fonts 2, 4, 6, 7, 8
 
 Make sure all the display driver and pin connections are correct by
 editing the User_Setup.h file in the TFT_eSPI library folder.

 #########################################################################
 ###### DON'T FORGET TO UPDATE THE User_Setup.h FILE IN THE LIBRARY ######
 #########################################################################
*/

// New background colour
#define TFT_BROWN 0x38E0

// Pause in milliseconds between screens, change to 0 to time font rendering
#define WAIT 500

#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h

unsigned long targetTime = 0; // Used for testing draw times


String lines[32] = {"I remember walking", "through the morning",
                      "after a night of heavy", "snow and drink", 
                      "with headphones on", "and they played",
                      "me the most", "perfect song: no one",
                      "was awake and", "I was hungover",
                      "young as clean", "as a piano",
                      "I thought", "and at any moment",
                      "someone might fall", "in love with me I was",
                      "that woven", "into the electric",
                      "cold bright air", "and for weeks",
                      "after I went", "through the album",
                      "in search of the song", "but could not",
                      "find it and later", "much later I saw",
                      "that what I had taken", "to be the song",
                      "was in fact the joyous", "concordance of",
                      "a moment that would", "not come again"};

int linelengths[32];

void setup(void) {
  tft.init();
  tft.setRotation(1);

  for (int i = 0; i < 32; i++){
    linelengths[i] = lines[i].length(); 
  }
}

const char title[] = "PERFECT SONG";
const char author[] = "Heather Christle"; 


void loop() {
  targetTime = millis();

  //initialize....
  tft.setTextSize(1);
  tft.setTextColor(TFT_WHITE);
  tft.fillScreen(TFT_BLACK);

  //print title and author name
  delay(2000); 
  tft.setCursor(22, 55, 4); 
  tft.println(title); 
  delay(5000);
  tft.fillScreen(TFT_BLACK);
  delay(1000);
  tft.setCursor(22, 55, 4); 
  tft.println(author);
  delay(5000);

  //blank out the screen
  tft.fillScreen(TFT_BLACK);
  delay(1000); 

  //set text to white
  tft.setTextColor(TFT_WHITE);

  //some variables to keep track of background color
  uint16_t color = tft.color565(0, 0, 0); 
  int currcol = 0; 
  int colswitch = 0; 


  //loop over all lines
  for (int i = 0; i < 16; i++){

    //clear screen
    tft.fillScreen(color);
    delay(50);

    //change text colors in between
    if (i < 7 or i > 14){
      tft.setTextColor(TFT_WHITE);
    }
    else{
      tft.setTextColor(TFT_BLACK);
    }
    //get line (broken into two)
    String line1 = lines[2*i];
    String line2 = lines[2*i+1];


    //special handling for first part of 12th line
    if (i == 11){
      //print "in search of " in black
      String l1 = ""; 
      for (int j = 0; j < 13; j++){
        tft.setCursor(2, 43, 4);
        l1 += line1[j];
 
        if (currcol > 254){
          colswitch = 1;
        }
        if (colswitch == 0){
          currcol += 1;
        }
        else if (colswitch == 1){
          currcol -= 1;
        }
        color = tft.color565(currcol, currcol, currcol);
        tft.fillScreen(color); 
        tft.setTextColor(TFT_BLACK);
        tft.println(l1);
        //wait a bit between characters
        delay(70); 
        
      }
      String l2 = "";
      for (int j = 13; j < line1.length(); j++){
        tft.setCursor(2, 43, 4);
        l2 += line1[j];
        if (currcol > 254){
          colswitch = 1;
        }
        if (colswitch == 0){
          currcol += 1;
        }
        else if (colswitch == 1){
          currcol -= 1;
        }
        color = tft.color565(currcol, currcol, currcol);
        tft.fillScreen(color); 
        tft.setTextColor(TFT_BLACK);
        tft.print(l1);
        tft.setTextColor(TFT_WHITE);
        tft.print(l2);
        //wait a bit between characters
        delay(70); 
      }
    }

    else{
       //iterate over first line....
      String l1 = "";
      for (int j = 0; j < line1.length(); j++){
        
        //reset cursor
        tft.setCursor(2, 43, 4);
        
        //for first char, only print first char
        if (j==0){
          l1 = line1[j];
        }
        
        //else, add on consecutive chars
        else{
          l1 += line1[j];
        }
  
        //if background color reaches white, start fading back to black
        if (currcol > 254){
          colswitch = 1;
        }
        
        //increment or decrement background color 
        if (colswitch == 0){
          currcol += 1;
        }
        else if (colswitch == 1){
          currcol -= 1;
        }
  
        //change background color
        color = tft.color565(currcol, currcol, currcol);
        tft.fillScreen(color); 
        //and print line
        tft.println(l1);
        
        //wait a bit between characters
        delay(70); 
      }
    }
    
    //wait between lines
    delay(200);

    
    
    //special handling for second part of fourth line of poem
    //print "perfect song:" in black, and the rest of the line in white
    if (i == 3){
      String l2 = "";
      for (int j = 0; j < 13; j++){
        tft.setCursor(2, 43, 4); 
        l2 += line2[j];
        if (currcol > 254){
          colswitch = 1;
        }
        if (colswitch == 0){
          currcol += 1;
        }
        else if (colswitch == 1){
          currcol -= 1;
        }
        color = tft.color565(currcol, currcol, currcol);
        tft.fillScreen(color);
        //print first line white
        tft.setTextColor(TFT_WHITE);
        tft.println(line1);
        //print second part of second line black
        tft.setTextColor(TFT_BLACK);
        tft.print(l2);
        delay(70);
      }
      //wait after "perfect song:"
      delay(2000);
      String l3 = "";
      for (int j = 13; j < line2.length(); j++){
        tft.setCursor(2, 43, 4); 
        l3 += line2[j]; 
        if (currcol > 254){
          colswitch = 1;
        }
        if (colswitch == 0){
          currcol += 1;
        }
        else if (colswitch == 1){
          currcol -= 1;
        }
        color = tft.color565(currcol, currcol, currcol);
        tft.fillScreen(color);
        //print first line white
        tft.setTextColor(TFT_WHITE);
        tft.println(line1);
        //print first part of second line black
        tft.setTextColor(TFT_BLACK);
        tft.print(l2);
        //print second part of second line white
        tft.setTextColor(TFT_WHITE);
        tft.print(l3);
        delay(70);
          
      }
      delay(1000);
    }



    //special handling for second part of sixth line
    //print piano alternating black and white characters
    else if (i == 5){
      String l2 = "";

      //print "as a " normally
      for (int j = 0; j < 5; j++){
        tft.setCursor(2, 43, 4); 
        l2 += line2[j];
        if (currcol > 254){
          colswitch = 1;
        }
        if (colswitch == 0){
          currcol += 1;
        }
        else if (colswitch == 1){
          currcol -= 1;
        }
        color = tft.color565(currcol, currcol, currcol);
        tft.fillScreen(color);
        tft.setTextColor(TFT_WHITE);
        tft.println(line1);
        tft.print(l2);
        delay(70);
      }

      //print "piano" alternating black and white
      String piano = "piano";  
      for (int j = 0; j < piano.length(); j++){
        tft.setCursor(2, 43, 4); 
        if (currcol > 254){
          colswitch = 1;
        }
        if (colswitch == 0){
          currcol += 1;
        }
        else if (colswitch == 1){
          currcol -= 1;
        }
        color = tft.color565(currcol, currcol, currcol);
        tft.fillScreen(color);
        //print first line white
        tft.setTextColor(TFT_WHITE);
        tft.println(line1);
        tft.print(l2);

        //print "piano" with alternating color
        for (int k = 0; k <=j; k++){
          if (k%2){
            tft.setTextColor(TFT_WHITE);
          }
          else{
            tft.setTextColor(TFT_BLACK);
          }
          tft.print(piano[k]);
        }
        delay(70);
          
      }
      delay(2000);
    }




    //special handling for second part of eigtht line
    else if (i == 7){
      String l2 = "";

      //print "in " in black
      for (int j = 0; j < 3; j++){
        tft.setCursor(2, 43, 4); 
        l2 += line2[j];
        if (currcol > 254){
          colswitch = 1;
        }
        if (colswitch == 0){
          currcol += 1;
        }
        else if (colswitch == 1){
          currcol -= 1;
        }
        color = tft.color565(currcol, currcol, currcol);
        tft.fillScreen(color);
        tft.setTextColor(TFT_BLACK);
        tft.println(line1);
        tft.print(l2);
        delay(70);
      }

      //print "love" in red
      String l3 = "";  
      for (int j = 3; j < 7; j++){
        tft.setCursor(2, 43, 4); 
        l3 += line2[j];
        if (currcol > 254){
          colswitch = 1;
        }
        if (colswitch == 0){
          currcol += 1;
        }
        else if (colswitch == 1){
          currcol -= 1;
        }
        color = tft.color565(currcol, currcol, currcol);
        tft.fillScreen(color);
        //print first line white
        tft.setTextColor(TFT_BLACK);
        tft.println(line1);
        tft.print(l2);
        tft.setTextColor(TFT_RED);
        tft.print(l3);
        delay(70);
          
      }

      //print " with me I was" in black
      String l4 = "";
      for (int j = 7; j < line2.length(); j++){
        tft.setCursor(2, 43, 4);
        l4 += line2[j];
        if (currcol > 254){
          colswitch = 1;
        }
        if (colswitch == 0){
          currcol += 1;
        }
        else if (colswitch == 1){
          currcol -= 1;
        }
        color = tft.color565(currcol, currcol, currcol);
        tft.fillScreen(color);
        //print first line white
        tft.setTextColor(TFT_BLACK);
        tft.println(line1);
        tft.print(l2);
        tft.setTextColor(TFT_RED);
        tft.print(l3);
        tft.setTextColor(TFT_BLACK);
        tft.print(l4);
        delay(70);
        
      }
      delay(2000);
    }




    //special handling for second part of ninth line
    else if (i == 8){
      String l2 = "";

      //print "into the " in black
      for (int j = 0; j < 9; j++){
        tft.setCursor(2, 43, 4); 
        l2 += line2[j];
        if (currcol > 254){
          colswitch = 1;
        }
        if (colswitch == 0){
          currcol += 1;
        }
        else if (colswitch == 1){
          currcol -= 1;
        }
        color = tft.color565(currcol, currcol, currcol);
        tft.fillScreen(color);
        tft.setTextColor(TFT_BLACK);
        tft.println(line1);
        tft.print(l2);
        delay(70);
      }

      //print "electric" in blue
      String l3 = "";  
      for (int j = 9; j < line2.length(); j++){
        tft.setCursor(2, 43, 4); 
        l3 += line2[j];
        if (currcol > 254){
          colswitch = 1;
        }
        if (colswitch == 0){
          currcol += 1;
        }
        else if (colswitch == 1){
          currcol -= 1;
        }
        color = tft.color565(currcol, currcol, currcol);
        tft.fillScreen(color);
        //print first line white
        tft.setTextColor(TFT_BLACK);
        tft.println(line1);
        tft.print(l2);
        tft.setTextColor(TFT_BLUE);
        tft.print(l3);
        delay(70);
          
      }
      delay(2000);
    }


    //special for line 12
    else if (i == 11){
      //iterate over second line...
      String l1 = "in search of ";
      String l2 = "the song";
      String l3 = ""; 
      for (int j = 0; j < line2.length(); j++){
        //second line, same as the first line
        tft.setCursor(2,43, 4); 
        l3 += line2[j];
        if (currcol > 254){
          colswitch = 1;
        }
  
        if (colswitch == 0){
          currcol += 1;
        }
        else if (colswitch == 1){
          currcol -= 1;
        }
        color = tft.color565(currcol, currcol, currcol);
        tft.fillScreen(color);  
        tft.setTextColor(TFT_BLACK);
        tft.print(l1);
        tft.setTextColor(TFT_WHITE);
        tft.println(l2);
        tft.setTextColor(TFT_BLACK);
        tft.print(l3);
        delay(70);
      }
      delay(2000);
    }



    //special handling for second part of 14th line
    else if (i == 13){
      String l2 = "";

      //print "to be " in black
      for (int j = 0; j < 6; j++){
        tft.setCursor(2, 43, 4); 
        l2 += line2[j];
        if (currcol > 254){
          colswitch = 1;
        }
        if (colswitch == 0){
          currcol += 1;
        }
        else if (colswitch == 1){
          currcol -= 1;
        }
        color = tft.color565(currcol, currcol, currcol);
        tft.fillScreen(color);
        tft.setTextColor(TFT_BLACK);
        tft.println(line1);
        tft.print(l2);
        delay(70);
      }

      //print "the song" in white
      String l3 = "";  
      for (int j = 6; j < line2.length(); j++){
        tft.setCursor(2, 43, 4); 
        l3 += line2[j];
        if (currcol > 254){
          colswitch = 1;
        }
        if (colswitch == 0){
          currcol += 1;
        }
        else if (colswitch == 1){
          currcol -= 1;
        }
        color = tft.color565(currcol, currcol, currcol);
        tft.fillScreen(color);
        //print first line white
        tft.setTextColor(TFT_BLACK);
        tft.println(line1);
        tft.print(l2);
        tft.setTextColor(TFT_WHITE);
        tft.print(l3);
        delay(70);
          
      }
      delay(2000);
    }


    

    //special handling for second part of last line
    else if (i == 15){
      String l2 = "";

      //print "not " and then wait
      for (int j = 0; j < 4; j++){
        tft.setCursor(2, 43, 4); 
        l2 += line2[j];
        if (currcol > 254){
          colswitch = 1;
        }
        if (colswitch == 0){
          currcol += 1;
        }
        else if (colswitch == 1){
          currcol -= 1;
        }
        color = tft.color565(currcol, currcol, currcol);
        tft.fillScreen(color);
        tft.setTextColor(TFT_WHITE);
        tft.println(line1);
        tft.print(l2);
        delay(70);
      }
      delay(500);
      
      
      //print "come " and then wait  
      for (int j = 4; j < 9; j++){
        tft.setCursor(2, 43, 4); 
        l2 += line2[j];
        if (currcol > 254){
          colswitch = 1;
        }
        if (colswitch == 0){
          currcol += 1;
        }
        else if (colswitch == 1){
          currcol -= 1;
        }
        color = tft.color565(currcol, currcol, currcol);
        tft.fillScreen(color);
        //print first line white
        tft.setTextColor(TFT_WHITE);
        tft.println(line1);
        tft.print(l2);
        delay(70);
          
      }
      delay (500); 

      //print "again"
      for (int j = 9; j < line2.length(); j++){
        tft.setCursor(2, 43, 4);
        l2 += line2[j];
        if (currcol > 254){
          colswitch = 1;
        }
        if (colswitch == 0){
          currcol += 1;
        }
        else if (colswitch == 1){
          currcol -= 1;
        }
        color = tft.color565(currcol, currcol, currcol);
        tft.fillScreen(color);
        //print first line white
        tft.setTextColor(TFT_WHITE);
        tft.println(line1);
        tft.print(l2);
        delay(70);
        
      }
      delay(2000);
    }

    //handling for all other lines
    else{
      //iterate over second line...
      String l2 = line1 + "\n"; 
      for (int j = 0; j < line2.length(); j++){
        //second line, same as the first line
        tft.setCursor(2,43, 4); 
        l2 += line2[j];
        if (currcol > 254){
          colswitch = 1;
        }
  
        if (colswitch == 0){
          currcol += 1;
        }
        else if (colswitch == 1){
          currcol -= 1;
        }
        color = tft.color565(currcol, currcol, currcol);
        tft.fillScreen(color);  
        tft.print(l2);
        delay(70);
      }

    //wait after each line is written
    delay(2000);
    }
    
  }

  //wait after poem is over
  delay(2000);
  tft.fillScreen(TFT_BLACK);
  
  /*
  int pos = 0; 
  String c = "";

  for (int i=0; i < strlen(test); i++){
    if (i==0){
      c = test[i];
    }
    else{
      c += test[i];
    } 
    tft.setCursor(0, 0, 4);
    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    tft.println(c);
    delay(1000);
  }
  */

  /*
  tft.drawString(" !\"#$%&'()*+,-./0123456", 0, 0, 4);
  tft.drawString("789:;<=>?@ABCDEFGHIJKL", 0, 20, 4);
  tft.drawString("MNOPQRSTUVWXYZ[\\]^_`", 0, 40, 4);
  tft.drawString("abcdefghijklmnopqrstuvw", 0, 60, 4);
  int xpos = 0;
  xpos += tft.drawString("xyz{|}~", 0, 64, 2);
  tft.drawChar(127, xpos, 64, 2);
  */

}
