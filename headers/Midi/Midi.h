#pragma once

//
//  Midi.h
//  VJ_Boilerplate
//
//  Created by Sebastian Meier on 09.10.13.
//
//

#include "RtMidi.h"
#include "RtError.h"
#include "Visual.h"
#include "Shader.h"

using namespace ci;
using std::list;

class Midi{
public:
    Midi();
    void setup();
    void update();
    void registerListener(Visual *visual);
    void registerListener(Shader *shader);
    void shutdown();
    
    bool active;
    std::vector<RtMidiIn *> devices;
    std::vector<Visual*> visualListeners;
    std::vector<Shader*> shaderListeners;
};

