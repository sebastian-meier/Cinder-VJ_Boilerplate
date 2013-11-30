//
//  Trip.cpp
//  VJ_Boilerplate
//
//  Created by Sebastian Meier on 29.09.13.
//
//

#include "Visual.h"

Visual::Visual(){}

void Visual::setup(int w, int h){
    width = w;
    height = h;
}

void Visual::init(){}
void Visual::update(){}
void Visual::draw(){}

void Visual::requestDraw(){
    if(active){
        draw();
    }
}

void Visual::requestUpdate(){
    if(active){
        update();
    }
}

void Visual::midiInput(int deviceid, int masterid, int midiid, int value){}
void Visual::audioInput(int type, float value){}
void Visual::audioFFT(std::vector<float> values){}