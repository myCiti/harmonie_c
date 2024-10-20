// Config.cpp
#include <Config.h>

void Config::saveJson(JsonObject obj) const {
    timers.save(obj["Timers"].to<JsonObject>());
    midstop.save(obj["Midstop"].to<JsonObject>());
    encoder.save(obj["Encoder"].to<JsonObject>());
    sdcard.save(obj["SDCard"].to<JsonObject>());
    param.save(obj["Param"].to<JsonObject>());
    }

bool Config::saveToFile(){
    File file = LittleFS.open("/config.json", "w");
    if (!file){
        Serial.println(F("Failed to create config file."));
        return false;
    }
    
    // serialize Json to file
    bool success = serializeJsonPretty(doc, file);
    if (!success){
        Serial.println(F("Failed to save file."));
        return false;
    }
    file.close();
    return true;
}

void Config::loadJson(){
    timers.load(doc["Timers"]);
    midstop.load(doc["Midstop"]);
    encoder.load(doc["Encoder"]);
    sdcard.load(doc["SDCard"]);
    param.load(doc["Param"]);

}

bool Config::loadFromFile(){
    File file = LittleFS.open("/config.json", "r");
    if(!file){
        Serial.println("Failed to open config file.");
        return false;
    }

    // Parse Json objects in the file
    DeserializationError error = deserializeJson(doc, file);
    if (error){
        Serial.println("Failed to deserialize config file.");
        return false;
    }
    file.close();
    loadJson();
    //serializeJsonPretty(doc, Serial); // print Json content
    return true;
}