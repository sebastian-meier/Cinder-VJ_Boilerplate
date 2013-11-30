//
//  VJ_Boilerplate.h
//  VJ_Boilerplate
//
//  Created by Sebastian Meier on 30.09.13.
//
//

#include "Resources.h"

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

#include <iostream>
#include <vector>

#include "WindowData.h"

//Input
#include "Midi.h"
#include "AudioAnalyzer.h"

//Visual
#include "AudioViz.h"
//Add more Visuals here:

//FBO
#include "cinder/gl/Fbo.h"
#include "cinder/gl/GlslProg.h"
#include "cinder/gl/Texture.h"

//Shader
#include "Shader.h"
#include "ColorOffset.h"
//Add more shaders here:

using namespace ci;
using namespace ci::app;
using namespace std;

class VJ_Boilerplate : public AppNative {
public:
    void prepareSettings( Settings *settings );
	void setup();
	void update();
    void shutdown();
	void draw();
    
    //Display Setup
    bool multiscreen = false;
    
    //Display #1
    bool display_borderless1 = false;
    bool display_fullscreen1 = false;
    bool display_alwaysontop1 = false;
    int display_id1 = 1;
    int display_x1 = 0;
    int display_y1 = 0;
    int display_width1 = 1024;
    int display_height1 = 768;
    
    //Display #2
    bool display_borderless2 = false;
    bool display_fullscreen2 = false;
    bool display_alwaysontop2 = false;
    int display_id2 = 2;
    int display_x2 = 0;
    int display_y2 = 0;
    int display_width2 = 1024;
    int display_height2 = 768;

    //Trips
    vector<Visual*> visuals;
    
    //FBO > Texture Stuff for the shaders
    gl::Fbo::Format format;
	gl::Fbo scene;
    
    //Shader
    vector<Shader*> shaders;
    float sinOffset = 0.0;
    
    //Midi System
    Midi midi;
    //AudioAnalyzer
    AudioAnalyzer audio;
};
