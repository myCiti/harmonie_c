//---------
// Menu.h - library for using menu with lcd
//-----------

#ifndef CONFIG_H
#define CONFIG_H

#include <ArduinoJson.h>
#include <LittleFS.h>


struct Timers {
    int open;
    int close;
    int midstop;

    void save(JsonObject obj) const{
    obj["OPEN"] = open | 5;
    obj["CLOSE"] = close | 4;
    obj["MIDSTOP"] = midstop | 0;
};
     
    void load(JsonObjectConst obj) {
        open = obj["OPEN"];
        close = obj["CLOSE"];
        midstop = obj["MIDSTOP"]; 
     }
};

struct Midstop {
    char outpin[5];
    int cycles;

    void save(JsonObject obj) const {
        obj["OUTPIN"] = outpin;
        obj["CYCLES"] = cycles;
    }

    void load(JsonObjectConst obj){
        (outpin[0] == '\0') ? strlcpy(outpin, "OPEN", 5) : strlcpy(outpin, obj["OUTPIN"], 5);
        cycles = obj["CYCLES"];
    }
};

struct Encoder {
    char status[9];
    char cmd[5];
    int freq;

    void save(JsonObject obj) const {
        obj["STATUS"] = status;
        obj["CMD"] = cmd;
        obj["FREQ"] = freq | 20;
    }

    void load(JsonObjectConst obj){
        (status[0] == '\0') ? strlcpy(status, "INACTIVE", 9) : strlcpy(status, obj["STATUS"], 9);
        (cmd[0] == '\0') ? strlcpy(cmd, "A2B0", 5) : strlcpy(cmd, obj["CMDV"], 5);
        freq = obj["FREQ"];
    }
};

struct SDCard {
    char status[9];

    void save(JsonObject obj) const {
        obj["STATUS"] = status;
    }

    void load(JsonObjectConst obj){
        (status[0] == '\0') ? strlcpy(status, "INACTIVE", 9) : strlcpy(status, obj["STATUS"], 9); // default value: INACTIVE
    }
};

struct Param {
    int btn_dura;
    int btn_read;
    char counter[8];
    char stopout[8];

    void save(JsonObject obj) const {
        obj["BTN_DURA"] = btn_dura | 200;
        obj["BNT_READ"] = btn_read | 3;
        obj["COUNTER"] = counter ;
        obj["STOPOUT"] =  stopout;
    }

    void load(JsonObjectConst obj){
        btn_dura = obj["BNT_DURA"];
        btn_read = obj["BTN_READ"];
        (counter[0] == '\0') ? strlcpy(counter, "CLS.LMT", 8) : strlcpy(counter, obj["COUNTER"], 8); // default value: Close Limit
        (stopout[0] == '\0') ? strlcpy(stopout, "NOR.CLS", 8) : strlcpy(stopout, obj["STOPOUT"], 8);
    }
};

class Config {
public:
    Timers timers;
    Midstop midstop;
    Encoder encoder;
    SDCard sdcard;
    Param param;

    JsonDocument doc;
    JsonObject root = doc.to<JsonObject>();

    void saveJson (JsonObject obj) const; // Create and save Json objects..
    bool saveToFile(); // Save Json to file
    void loadJson();
    bool loadFromFile(); // Load Json string from file.
};
#endif