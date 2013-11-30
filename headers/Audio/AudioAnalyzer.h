//
//  AudioAnalyzer.h
//  VJ_Boilerplate
//
//  Created by Sebastian Meier on 30.09.13.
//
//

#include "KissFFT.h"
#include "cinder/audio/Input.h"
#include "cinder/audio/FftProcessor.h"
#include "cinder/audio/Io.h"
#include "cinder/audio/Output.h"
#include "cinder/audio/PcmBuffer.h"
#include "Visual.h"
#include "Shader.h"
#include "AudioInputTypes.h"
#include "cinder/System.h"
#include "Resources.h"

#include <iostream>


using namespace ci;
using namespace ci::app;
using std::list;

class AudioAnalyzer{
public:
    AudioAnalyzer();
    void setup();
    void update();
    void registerListener(Visual *visual);
    void registerListener(Shader *shader);
    void sendOutput(int type, float value);
    void sendFFt(std::vector<float> values);
    
    audio::Input mInput;
	std::shared_ptr<float> mFftDataRef;
	audio::PcmBuffer32fRef mBuffer;
    audio::TrackRef mTrack;
    // Audio file
	ci::audio::SourceRef		mAudioSource;

    float range = 0.2f;
    
    // Analyzer
	KissRef						mFft;
    
	// Data
	int32_t						mDataSize;
	float						*mInputData;
	int32_t						mInputSize;
	float						*mTimeData;
    
    
	// Tempo information
	int32_t						mFirstPeak;
	int32_t						mNeighbors;
	std::vector<int32_t>		mPeakDistances;
	int32_t						mSampleDistance;
	float						mTempo;
	float						mThreshold;

    //Waveform information
    std::vector<float>          mWaveform;
    int maxDataPoints = 5000;
    
    std::vector<Visual*> visualListeners;
    std::vector<Shader*> shaderListeners;
};