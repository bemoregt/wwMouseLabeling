#include "ofApp.h"

void ofApp::setup()
{
    mImage.loadImage("src_sd.bmp");
    
    ofxLabelingUtils::convertRGBtoGray(mImage);
    
    mLabeling.Exec(mImage, false, 20, true, true, false);
    mResult = mLabeling.getVirtualColorImage();
    mLabel = mLabeling.getLabelingImage();
}

void ofApp::update()
{
}

void ofApp::draw()
{
    mImage.draw(0, 0);
    mResult.draw(640, 0);
    mLabel.draw(0, 480);
}
