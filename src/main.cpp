#include <Arduino.h>

#include <LcdMenu.h>
#include <MenuScreen.h>
#include <ItemSubMenu.h>
#include <ItemIntRange.h>
#include <ItemList.h>
#include <ItemToggle.h>
#include <ItemBack.h>
#include <display/LiquidCrystal_I2CAdapter.h>
#include <renderer/CharacterDisplayRenderer.h> 
#include <RotaryEncoder.h>
#include "RotaryAdapter.h"

#include "lcd.h"
#include "Menu.h"


LiquidCrystal_I2CAdapter  lcdAdapter(&lcd);
CharacterDisplayRenderer renderer(&lcdAdapter, 20, 4);
LcdMenu menu(renderer);

RotaryEncoder rotaryEnc(15, 8, 9,  RotaryEncoder::LatchMode::FOUR0);
RotaryAdapter rotary(&menu, &rotaryEnc);
/*
// Define the main menu
// Declare callbacks 
    void timersOpen(int pos);
    void timersClose(int pos);
    void timersMidstop(int pos);
    void midstopOutpinCallback(uint8_t pos);
    void midstopCycles(int pos);
    void encoderStatusToggle(bool isActive);
    void encoderCmdCallback(uint8_t pos);
    void encoderFreq(int pos);
    void sdcardStatusToggle(bool isActive);
    void paramBtnDura(int pos);
    void paramBtnRead(int pos);
    void paramCounterCallback(uint8_t pos);
    void paramStopOutCallback(uint8_t pos);
*/
/*     extern MenuScreen* timersScreen;
    extern MenuScreen* midstopScreen;
    extern MenuScreen* encoderScreen;
    extern MenuScreen* sdcardScreen;
    extern MenuScreen* paramScreen;

    extern String midstopOutpin[];
    String midstopOutpin[]  ={"OPEN", "O4"};

    extern String encoderCmd[];
    String encoderCmd[] = {"A2B0", "A2B3", "A2B1", "A2B4"};

    extern String paramCounter[];
    String paramCounter[]  ={"CLS.LMT", "OPN.LMT"};

    extern String paramStopOut[];
    String paramStopOut[]  ={"NOR.CLS", "NOR.OPN"}; */

/* // clang-format off
MENU_SCREEN(mainScreen, mainItems,
    ITEM_SUBMENU("TIMERS", timersScreen),
    ITEM_SUBMENU("MIDSTOP", midstopScreen),
    ITEM_SUBMENU("ENCODER", encoderScreen),
    ITEM_SUBMENU("SDCARD", sdcardScreen),
    ITEM_SUBMENU("PARAM", paramScreen)
    );

MENU_SCREEN(timersScreen, timersItems,
    ITEM_INT_RANGE("OPEN   ", 0, 9999, 5, timersOpen),
    ITEM_INT_RANGE("CLOSE  ", 0, 9999, 5, timersClose),
    ITEM_INT_RANGE("MIDSTOP", 0, 9999, 0, timersMidstop),
    ITEM_BACK("...BACK")
);


MENU_SCREEN(midstopScreen, midstopItems,
    ITEM_STRING_LIST("OUTPIN ", midstopOutpin, 2, midstopOutpinCallback),
    ITEM_INT_RANGE("CYCLES ", 0, 9999, 1, midstopCycles),
    ITEM_BACK("...BACK")
);

MENU_SCREEN(encoderScreen, encoderItems,
    ITEM_TOGGLE("STATUS ", encoderStatusToggle),
    ITEM_STRING_LIST("CMD    ", encoderCmd, 4, encoderCmdCallback),
    ITEM_INT_RANGE("FREQ   ", 0, 50, 20, encoderFreq),
    ITEM_BACK("...BACK")
);

MENU_SCREEN(sdcardScreen, sdcardItems,
    ITEM_TOGGLE("STATUS ", sdcardStatusToggle),
    ITEM_BACK("...BACK")
);

MENU_SCREEN(paramScreen, paramItems,
    ITEM_INT_RANGE("BTN.DUR", 0, 9999, 200, paramBtnDura),
    ITEM_INT_RANGE("BTN.RD ", 0, 50, 5, paramBtnRead),
    ITEM_STRING_LIST("COUNTER", paramCounter, 2, paramCounterCallback),
    ITEM_STRING_LIST("STOPOUT", paramStopOut, 2, paramStopOutCallback),
    ITEM_BACK("...BACK")
);   */

const int input_Stop = 6; // stop button pin

volatile bool stopSignal = false; // Volatile because it's shared with ISR
void stopSignalISR(){
    stopSignal = true;
}

// initialize before each run
void initialize(){
    lcd.clear();
    stopSignal = false;
    lcd_print("BIENVENUE", 0, 3);
    lcd_print("HARMONIE_C", 1, 3);
    Serial.printf("Initialize, timers.opens: %d", config.timers.open);
}


void setup(){
    Serial.begin(9600);
    
    LittleFS.begin();

    config.loadFromFile();

    renderer.begin();
    menu.setScreen(mainScreen);


    // set up inputs
    pinMode(input_Stop, INPUT_PULLDOWN);
    attachInterrupt(digitalPinToInterrupt(input_Stop), stopSignalISR, RISING); 

    //delay(5000);

    /*
    Serial.println("Start.... saving file");
    menu.timers.open = 7;
    menu.saveJson(menu.root);
    menu.saveToFile();
    menu.timers.open = 1;
    //serializeJsonPretty(menu.doc, Serial);
    */
/*
    Serial.println("Load from file...");
    menu.loadFromFile();
    Serial.printf("Midstop outpin %s \n", menu.midstop.outpin);
    Serial.printf("STOPOUT outpin %s \n", menu.param.stopout);
    Serial.printf("Timer open %d \n", menu.timers.open );
    Serial.println("End....");
*/
    initialize();
    delay(5000);
    Serial.printf("timers.open: %d\n ", config.timers.open);
}

void loop(){
    if (stopSignal){ initialize();} 
    rotary.observe();
    //Serial.println(rotaryEnc.getButtonPressed());
}

/* 
void timersOpen(int pos){
    Serial.println(pos);
}

void timersClose(int pos){
    Serial.println(pos);
}

void timersMidstop(int pos){
    Serial.println(pos);
}

void midstopOutpinCallback(uint8_t pos){
    Serial.println(pos);
}

void midstopCycles(int pos){
    Serial.println(pos);
}

void encoderStatusToggle(bool isActive){
    Serial.println(isActive);
}

void encoderCmdCallback(uint8_t pos){
    Serial.println(pos);
}

void encoderFreq(int pos){
    Serial.println(pos);
}

void sdcardStatusToggle(bool isActive){
    Serial.println(isActive);
}

void paramBtnDura(int pos){
    Serial.println(pos);
}

void paramBtnRead(int pos){
    Serial.println(pos);
}

void paramCounterCallback(uint8_t pos){
    Serial.println(pos);
}

void paramStopOutCallback(uint8_t pos){
    Serial.println(pos);
}  */