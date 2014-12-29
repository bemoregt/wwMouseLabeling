#include "ofApp.h"

void ofApp::setup()
{
    mImage.loadImage("sample.bmp");
    mImage.setImageType(OF_IMAGE_GRAYSCALE);
    
    // get labeling image
    mLabeling.Exec(mImage, false, 20, true, true, false);
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
}

void ofApp::update()
{
}

void ofApp::draw()
{
    mImage.draw(0, 0);
    mResult.draw(320, 0);
    mLabel.draw(320 * 2, 0);
}
