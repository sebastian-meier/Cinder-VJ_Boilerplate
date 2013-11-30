//
//  AudioAnalyzer.cpp
//  VJ_Boilerplate
//
//  Created by Sebastian Meier on 30.09.13.
//
//

#include "AudioAnalyzer.h"

AudioAnalyzer::AudioAnalyzer(){}

void AudioAnalyzer::setup(){
    // Define properties
	mDataSize		= 0;
	mFirstPeak		= -1;
	mInputSize		= 0;
	mNeighbors		= 4; //6/4/2
	mSampleDistance = 0;
	mTempo			= 0.0f;
	mThreshold		= 0.1f;
	mPeakDistances.clear();
    
	mInput = audio::Input();
	mInput.start();
    
    // Load and play audio
	//mAudioSource = audio::load( loadResource( RES_SAMPLE ) );
	//mTrack = audio::Output::addTrack( mAudioSource, false );
	//mTrack->enablePcmBuffering( true );
	//mTrack->play();
}

void AudioAnalyzer::registerListener(Visual *visual){
    visualListeners.push_back(visual);
}

void AudioAnalyzer::registerListener(Shader *shader){
    shaderListeners.push_back(shader);
}

void AudioAnalyzer::sendOutput(int type, float value){
    for(auto visualListener : visualListeners){
        visualListener->audioInput(type,value);
    }
    for(auto shaderListener : shaderListeners){
        shaderListener->audioInput(type,value);
    }
}

void AudioAnalyzer::sendFFt(std::vector<float> values){
    for(auto visualListener : visualListeners){
        visualListener->audioFFT(values);
    }
    for(auto shaderListener : shaderListeners){
        shaderListener->audioFFT(values);
    }
}

void AudioAnalyzer::update(){
    if ( cinder::app::getElapsedSeconds() < 0.5 ) {
		return;
	}
    
    // Get buffer
    mBuffer = mInput.getPcmBuffer();
    //mBuffer = mTrack->getPcmBuffer();
    
    if(mBuffer && mBuffer->getInterleavedData()){
        // Get sample count
        uint32_t sampleCount = mBuffer->getInterleavedData()->mSampleCount;
        if(sampleCount > 0){
            
            // Kiss is not initialized
            if(!mFft){
                // Initialize analyzer
                mFft = Kiss::create( sampleCount );
                // Set filter on FFT to calculate tempo based on beats
                mFft->setFilter( range, Kiss::Filter::LOW_PASS );
            }
            
            // Analyze data
            if(mBuffer->getInterleavedData()->mData != 0){

                // Set FFT data
                mInputData = mBuffer->getInterleavedData()->mData;
                mInputSize = mBuffer->getInterleavedData()->mSampleCount;
                mFft->setData( mInputData );
                
                // Get data
                mTimeData = mFft->getData();
                mDataSize = mFft->getBinSize();
                
                // Iterate through amplitude data
                for ( int32_t i = 0; i < mDataSize; i++, mSampleDistance++ ) {
                    
                    // Check value against threshold
                    if ( mTimeData[ i ] >= mThreshold ) {
                        
                        // Determine neighbor range
                        int32_t start	= math<int32_t>::max( i - mNeighbors, 0 );
                        int32_t end		= math<int32_t>::min( i + mNeighbors, mDataSize - 1 );
                        
                        // Compare this value with neighbors to find peak
                        bool peak = true;
                        for ( int32_t j = start; j < end; j++ ) {
                            if ( j != i && mTimeData[ i ] <= mTimeData[ j ] ) {
                                peak = false;
                                break;
                            }
                        }
                        
                        // This is a peak
                        if ( peak ) {
                            
                            // Add distance between this peak and last into the
                            // list. Just note position if this is the first peak.
                            if ( mFirstPeak >= 0 ) {
                                mPeakDistances.push_back( mSampleDistance );
                            } else {
                                mFirstPeak = mSampleDistance;
                            }
                            
                            // Reset distance counter
                            mSampleDistance = 0;
                            
                            sendOutput(TTAudioInputType_Peak, 1.0);
                        }else{
                            sendOutput(TTAudioInputType_Peak, 0.0);
                        }
                        
                    }
                    
                }
                
            }
            
        }
        
        // We have multiple peaks to compare
        if(mPeakDistances.size() > 1){
            
            // Add distances
            int32_t total = 0;
            uint32_t peakCount = mPeakDistances.size();
            for ( uint32_t i = 0; i < peakCount; i++ ) {
                total += mPeakDistances[ i ];
            }
            
            // Determine tempo based on average peak distance
            mTempo = total > 0 ? ( 44100.0f / ( (float)total / (float)mPeakDistances.size() ) ) * 60.0f / 1000.0f : 0.0f;
        }
        
        // Add up values, combine input and filtered values
        // to emphasize bass
        float total = 0.0f;
        for ( int32_t i = 0; i < mDataSize; i++ ) {
            if ( i * 8 < mInputSize ) {
                total += mTimeData[ i ] * 2.0f * mInputData[ i * 8 ];
            }
        }
        
        // Add average to drawing line
        mWaveform.push_back( total / (float)mDataSize );
        sendOutput(TTAudioInputType_Wave, total / (float)mDataSize);
        
        // Remove points when vector is getting large
        while ( mWaveform.size() >= maxDataPoints ) {
            mWaveform.erase( mWaveform.begin() );
        }
        
        std::vector<float> fftvalues;
        float *data = mFft->getAmplitude();
        int sampleSize = mFft->getBinSize();
        for ( int32_t n = 0; n < sampleSize && n < 128; ++n ){
            fftvalues.push_back(data[n]);
        }
        for ( int32_t i = 0; i < mDataSize && i < 256; i++ ) {
            fftvalues.push_back(mInputData[i]);
        }
        sendFFt(fftvalues);
    }
}
