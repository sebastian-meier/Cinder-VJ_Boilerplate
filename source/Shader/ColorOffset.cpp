//
//  ColorOffset.cpp
//  VJ_Boilerplate
//
//  Created by Sebastian Meier on 06.10.13.
//
//

#include "ColorOffset.h"

void ColorOffset::set(){
    GLfloat params[1];
    params[0] = 0.7;
    shader.uniform("alpha", params, 1);
    shader.uniform("redOffset", redOffset);
    shader.uniform("greenOffset", greenOffset);
}

void ColorOffset::midiInput(int deviceid, int masterid, int midiid, int value){
    if(deviceid == TTNanoPad){
        if(masterid == TTNP_S1_B9_DOWN_V1 && midiid == TTNP_S1_B9_DOWN_V2){
            if(active){active=false;}else{active=true;}
        }else if(masterid == TTNP_S1_S1_X_V1 && midiid == TTNP_S1_S1_X_V2){
            redOffset.x = (float(value)-64.0)/640.0;
            greenOffset.x = (float(value)-64.0)*-1.0/640.0;
        }else if(masterid == TTNP_S1_S1_Y_V1 && midiid == TTNP_S1_S1_Y_V2){
            redOffset.y = (float(value)-64.0)/640.0;
            greenOffset.y = (float(value)-64.0)*-1.0/640.0;
        }
    }
}

void ColorOffset::setOffsetGreen(Vec2f green){
    greenOffset = green;
}

void ColorOffset::setOffsetRed(Vec2f red){
    redOffset = red;
}

void ColorOffset::setAlpha(float a){
    alpha = a;
}