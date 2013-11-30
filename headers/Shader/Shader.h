#pragma once

//
//  Shader.h
//  VJ_Boilerplate
//
//  Created by Sebastian Meier on 06.10.13.
//
//

#include "cinder/gl/GlslProg.h"
#include "AudioInputTypes.h"
#include "MidiControllerConfig.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class Shader{
public:
    Shader();
    
    void setup(std::string vert, std::string frag);
    void requestStart();
    void start();
    void requestEnd();
    void end();
    
    void requestSet();
    virtual void set();
    
    virtual void midiInput(int deviceid, int masterid, int midiid, int value);
    virtual void audioInput(int type, float value);
    virtual void audioFFT(std::vector<float> values);
    
    gl::GlslProg shader;
    
    bool active = false;
};
