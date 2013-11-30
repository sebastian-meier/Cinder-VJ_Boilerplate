//
//  Shader.cpp
//  VJ_Boilerplate
//
//  Created by Sebastian Meier on 06.10.13.
//
//

#include "Shader.h"

Shader::Shader(){}

void Shader::setup(std::string vert, std::string frag){
    shader = gl::GlslProg( loadResource( vert ), loadResource( frag ) );
}

void Shader::requestStart(){
    if(active){
        start();
    }
}

void Shader::start(){
    shader.bind();
	shader.uniform("tex0", 0);
}

void Shader::requestSet(){
    if(active){
        set();
    }
}

void Shader::set(){}

void Shader::requestEnd(){
    if(active){
        end();
    }
}

void Shader::end(){
    shader.unbind();
}

void Shader::midiInput(int deviceid, int masterid, int midiid, int value){}
void Shader::audioInput(int type, float value){};
void Shader::audioFFT(std::vector<float> values){}