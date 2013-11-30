//
//  AudioViz.h
//  VJ_Boilerplate
//
//  Created by Sebastian Meier on 10.10.13.
//
//

#include "Visual.h"
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class AudioViz : public Visual {
public:
    void draw();
    void audioInput(int type, float value);
    void midiInput(int deviceid, int masterid, int midiid, int value);
    void audioFFT(std::vector<float> values);
    
    vector<float>values;
    vector<float>fft;
    int border = 40;
    float timelineratio = 1.0;
    bool active = true;
    bool peak = false;
};
