#include "ofApp.h"

//------------------------------------------------------------
void ofApp::setup()
{
    mImage.load("/Users/mun/Desktop/th.png");
    mImage.setImageType(OF_IMAGE_GRAYSCALE);
    
    // get labeling image
    mLabeling.Exec(mImage, false, 50, true, true, false);
    mResult = mLabeling.getVirtualColorImage();
    mLabel = mLabeling.getLabelingImage();
    
    // get region info
    for (int i = 0; i < mLabeling.size(); ++i)
    {
        cout << "region " << i << endl;
        cout << "pixels: " << mLabeling.getNumPixels(i) << endl;
        cout << "center points: " << mLabeling.getCenter(i) << endl;
        cout << "centroid: " << mLabeling.getCentroid(i) << endl;
        cout << "min points: " << mLabeling.getMin(i) << endl;
        cout << "max points: " << mLabeling.getMax(i) << endl << endl;
    }
    mImage.update();
    mResult.update();
    mLabel.update();
    
}

//------------------------------------------------------------
void ofApp::update()
{
}

//------------------------------------------------------------
void ofApp::draw()
{
    ofSetColor(255);
    mImage.draw(0, 0, 512, 512);
    mResult.draw(512, 0, 512, 512);
    mLabel.draw(1024, 0, 512, 512);
    
}
