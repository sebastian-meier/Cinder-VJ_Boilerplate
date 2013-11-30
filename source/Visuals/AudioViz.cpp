//
//  AudioViz.cpp
//  VJ_Boilerplate
//
//  Created by Sebastian Meier on 10.10.13.
//
//

#include "AudioViz.h"

void AudioViz::audioInput(int type, float value){
    active = true;
    if(type == TTAudioInputType_Wave){
        value *= 1000000;
        values.push_back(value);
        while ( values.size() >= 1024 ) {
            values.erase( values.begin() );
        }
    }else if(type == TTAudioInputType_Peak && value == 1.0){
        peak = true;
    }
}

void AudioViz::audioFFT(std::vector<float> values){
    fft = values;
}

void AudioViz::draw(){
    //Timeline
    gl::pushMatrices();
    gl::translate(Vec2f(float(border), float(height-2*border)));
    gl::color(0.5,0.5,0.5);
    gl::lineWidth(2.0);
    for(float i = 0; i<(width-2*border) && i<values.size(); i++){
        gl::drawLine(Vec2f(i, double(values.at(int( values.size()-1-i)))*-10*timelineratio), Vec2f(i, 0.0));
    }
    gl::popMatrices();
    
    
    gl::color(0.0,1.0,1.0);
    for(float i = 0; i<fft.size(); i++){
        gl::drawLine(Vec2f(i, fft.at(int(i))*10000+400.0), Vec2f(i, 400.0));
    }
    
    gl::color(1,1,1);
    gl::drawStrokedEllipse(Vec2f(border*2, border*2), border, border);
    if(peak){
        gl::drawSolidEllipse(Vec2f(border*2, border*2), border-10, border-10);
        peak = false;
    }
}

void AudioViz::midiInput(int deviceid, int masterid, int midiid, int value){
    if(deviceid == TTNanoKontrol){
        if(masterid == TTNK_S4_S9_V1 && midiid == TTNK_S4_S9_V2){
            timelineratio = value/64.0;
        }
    }
}