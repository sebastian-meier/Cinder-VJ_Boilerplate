#pragma once

//
//  Visual.h
//  VJ_Boilerplate
//
//  Created by Sebastian Meier on 29.09.13.
//
//

#include "cinder/gl/Vbo.h"
#include "cinder/gl/gl.h"
#include "AudioInputTypes.h"
#include "MidiControllerConfig.h"

using namespace ci;
using std::list;

class Visual{
 public:
    Visual();
    
    virtual void setup(int w, int h);
    virtual void requestUpdate();
    virtual void update();
    virtual void init();
    virtual void requestDraw();
    virtual void draw();
    virtual void midiInput(int deviceid, int masterid, int midiid, int value);
    virtual void audioInput(int type, float value);
    virtual void audioFFT(std::vector<float> values);
    
    int height;
    int width;
    
    bool active = false;
};