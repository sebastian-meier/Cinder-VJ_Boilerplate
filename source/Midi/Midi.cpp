//
//  Midi.cpp
//  VJ_Boilerplate
//
//  Created by Sebastian Meier on 09.10.13.
//
//

#include "Midi.h"

Midi::Midi(){
}

void Midi::setup(){
    RtMidiIn *channels = new RtMidiIn();
    int port_number = channels->getPortCount();
    delete channels;
    if(port_number>0){
        active = true;
        for(int i = 0; i<port_number; i++){
            RtMidiIn *temp = new RtMidiIn();
            devices.push_back(temp);
            devices.at(i)->openPort(i);
            devices.at(i)->ignoreTypes(false,false,false);
        }
    }
}

void Midi::update(){
    std::vector<unsigned char> message;
    double stamp;
    int nBytes;
    std::vector<std::vector<int>> events;
    for(int i = 0; i<devices.size(); i++){
        stamp = devices.at(i)->getMessage(&message);
        nBytes = message.size();
        while(nBytes >= 3){
            if(nBytes >= 3){
                //std::cout << "0:" << (int)message[0] << "\t\t 1:" << (int)message[1] << "\t\t 2:" << (int)message[2] << " \n";
                bool exists = false;
                for(int e = 0; e<events.size(); e++){
                    if(events.at(e).at(0)==i&&events.at(e).at(1)==(int)message[0]&&events.at(e).at(2)==(int)message[1]){
                        exists = true;
                        events.at(e).at(3) = (int)message[2];
                    }
                }
                if(!exists){
                    std::vector<int> t_event;
                    t_event.push_back(i);
                    t_event.push_back((int)message[0]);
                    t_event.push_back((int)message[1]);
                    t_event.push_back((int)message[2]);
                    events.push_back(t_event);
                }
            }
            stamp = devices.at(i)->getMessage( &message );
            nBytes = message.size();
        }
    }
    
    for(auto visualListener : visualListeners){
        for(auto event : events){
            visualListener->midiInput(event.at(0), event.at(1), event.at(2), event.at(3));
        }
    }
    
    for(auto shaderListener : shaderListeners){
        for(auto event : events){
            shaderListener->midiInput(event.at(0), event.at(1), event.at(2), event.at(3));
        }
    }
    
    //turn message inputs into values for data holders
    //sections 176-184
    //dials 7 (0-127)
    //slider 10 (0-127)
    //buttons 16 u 17 (0/127)
}

void Midi::registerListener(Visual *visual){
    visualListeners.push_back(visual);
}

void Midi::registerListener(Shader *shader){
    shaderListeners.push_back(shader);
}

void Midi::shutdown(){
    for(int i = 0; i<devices.size(); i++){
        delete dynamic_cast<RtMidiIn *>(devices.at(i));
    }
}