//
//  ColorOffset.h
//  VJ_Boilerplate
//
//  Created by Sebastian Meier on 06.10.13.
//
//

#include "Shader.h"
#include "cinder/Rand.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class ColorOffset : public Shader {
public:
    void set();
    void setOffsetGreen(Vec2f green);
    void setOffsetRed(Vec2f red);
    void setAlpha(float a);
    void midiInput(int deviceid, int masterid, int midiid, int value);
    
    float alpha = 0.0;
    Vec2f redOffset = Vec2f(0.0, 0.0);
    Vec2f greenOffset = Vec2f(0.0, 0.0);
};
