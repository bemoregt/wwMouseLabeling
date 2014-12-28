#pragma once

#include "ofMain.h"
#include "ofxLabeling.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    ofImage mImage;
    ofImage mResult;
    ofImage mLabel;
    
    ofxLabelingBS mLabeling;
    
};
