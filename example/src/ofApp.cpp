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
    for (int i = 0; i < mLabeling.GetNumOfRegions() - 1; ++i)
    {
        ofxRegionInfoBS * ri = mLabeling.GetResultRegionInfo(i);
        
        int ix, iy;
        float x, y;
        
        cout << "region " << i << endl;
        
        ri->GetCenter(x, y);
        cout << "center: " << x << " " << y << endl;
        
        ri->GetCenterOfGravity(x, y);
        cout << "center of gravity: " << x << " " << y << endl;
        
        ri->GetMin(ix, iy);
        cout << "min point: " << ix << " " << iy << endl;
        
        ri->GetMax(ix, iy);
        cout << "max point: " << ix << " " << iy << endl;
        
        cout << "number of pixels: " << ri->GetNumOfPixels() << "\n\n";
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
