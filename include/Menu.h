#ifndef MENU_H
#define MENU_H

#include "Config.h"

Config config;

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

extern MenuScreen* timersScreen;
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
String paramStopOut[]  ={"NOR.CLS", "NOR.OPN"};
/*
void setupMenu();
 */

// clang-format off
MENU_SCREEN(mainScreen, mainItems,
    ITEM_SUBMENU("TIMERS", timersScreen),
    ITEM_SUBMENU("MIDSTOP", midstopScreen),
    ITEM_SUBMENU("ENCODER", encoderScreen),
    ITEM_SUBMENU("SDCARD", sdcardScreen),
    ITEM_SUBMENU("PARAM", paramScreen)
    );

MENU_SCREEN(timersScreen, timersItems,
    ITEM_INT_RANGE("OPEN   ", 0, 9999, config.timers.open, timersOpen),
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
);  


void timersOpen(int pos){
    config.timers.open = pos;
    config.saveJson(config.root);
    config.saveToFile();
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
}
#endif