#pragma once

#include "input/InputInterface.h"
#include <RotaryEncoder.h>

class RotaryAdapter : public InputInterface {
    private:
        bool pendingEnter = false;  // Flag to indicate if an enter action is pending
        RotaryEncoder* encoder;     // Pointer to Rotary encoder instance 
    
    public:
        RotaryAdapter (LcdMenu* menu, RotaryEncoder* encoder)
            : InputInterface(menu), encoder(encoder){
            }
        
        void observe() override{
            encoder->tick();
            int rotation = (int)encoder->getDirection();
            bool pressed = encoder->getButtonPressed();

            if (rotation == 1){
                menu->process(DOWN);
            } else if (rotation == -1){
                menu->process(UP);
            }
            
            // handle button press
            if (pressed){
                if (!menu->getRenderer()->isInEditMode() && pendingEnter){
                menu->process(ENTER);
                pendingEnter = false;
                }
                if(pendingEnter){
                    pendingEnter = true;
                    menu->process(BACK);
                } else {
                    pendingEnter = true;
                    menu->refresh();
                }
            }
        }
};