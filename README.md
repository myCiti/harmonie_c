# harmonie_c
Harmonie in C

## libusb - Zadig
In Windows, libusb library is required to to upload files through PlatformIO. libusb is recommanded when using rpi pico in Windows. this library can be downloaded and install with [Zadig](https://zadig.akeo.ie/)


### Modifications to library
When upgrade LcdMedu library, make following changes.

in **`renderer/CharacterDisplayRenderer.cpp**`, in function **`void CharacterDisplayRenderer::appendCursorToText(char* text) {...}**`
```
if (hasFocus && inEditMode){ // Change : to ->  // around line 69
        text[7]=cursorIcon;
    }
```

in **`ItemRangeBase.h`** in function **`bool process(LcdMenu* menu, const unsigned char command) override {...}`**
```
case UP:
    if (decrement()) {  // around line 126
    .
    .
    .
case DOWN:
    if (increment()) { // around line 134
```
