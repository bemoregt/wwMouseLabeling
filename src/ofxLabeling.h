#pragma once

#include "ofMain.h"
#include "Labeling.h"

template<class SrcT, class DstT>
class ofxLabeling : public Labeling<SrcT, DstT>
{
    typedef Labeling<SrcT, DstT> base;
    
    ofImage mrLabelingImage;
    ofImage mrVirtualColorImage;
    ofShortImage mrShortImage;
    
protected:
    bool isMultiChannel(ofImage & img)
    {
        return img.getPixelsRef().getNumChannels() > 1 ? true : false;
    }
    
    bool isMultiChannel(ofShortImage & img)
    {
        return img.getPixelsRef().getNumChannels() > 1 ? true : false;
    }
    
    void generateLabelingImageAsUC(short * result, int w, int h, ofImage & dst)
    {
        dst.allocate(w, h, OF_IMAGE_GRAYSCALE);
        unsigned char * dstpx = dst.getPixels();
        short *s = result;
        for ( int i = 0; i < w * h; i++ )
        {
            dstpx[i] = static_cast<unsigned char>(*s);
            ++s;
        }
        dst.update();
    }
    
    void generateVirtualColorImage(short * result, int w, int h, ofImage & dst)
    {
        dst.allocate(w, h, OF_IMAGE_COLOR);
        unsigned char * dstpx = dst.getPixels();
        short *s = result;
        for ( int i = 0; i < w * h; i++ )
        {            
            if ( *s == 0 ) {
                dstpx[i*3+0] = 0;
                dstpx[i*3+1] = 0;
                dstpx[i*3+2] = 0;
            } else {
                double r, g, b;
                double w;
                double h = *s / 16.0;
                double s = 1.0;
                double v = 1.0;
                
                // Convert HSV to RGB.
                if ( h < 0.0 ) {
                    h += static_cast<int>( -h ) + 1;
                }
                if ( h >= 1.0 ) {
                    h -= static_cast<int>( h );
                }
                h = h * 6.0;
                w = v * ( 1.0 - s );
                
                switch ( static_cast<int>( h )) {
                    case 0:
                        r = v;
                        b = w;
                        g = b + h * ( v - w );
                        break;
                    case 1:
                        g = v;
                        b = w;
                        r = b - ( h - 2.0 ) * ( v - w );
                        break;
                    case 2:
                        g = v;
                        r = w;
                        b = r + ( h - 2.0 ) * ( v - w );
                        break;
                    case 3:
                        b = v;
                        r = w;
                        g = r - ( h - 4.0 ) * ( v - w );
                        break;
                    case 4:
                        b = v;
                        g = w;
                        r = g + ( h - 4.0 ) * ( v - w );
                        break;
                    case 5:
                        r = v;
                        g = w;
                        b = g - ( h - 6.0 ) * ( v - w );
                        break;
                    default:
                        r = g = b = 0.0;
                        break;
                }
                dstpx[i*3+0] = static_cast<unsigned char>( r * 255 );
                dstpx[i*3+1] = static_cast<unsigned char>( g * 255 );
                dstpx[i*3+2] = static_cast<unsigned char>( b * 255 );
            }
            ++s;
        }
        dst.update();
    }
    
    void generateShortImage(short * result, int w, int h, ofShortImage & dst)
    {
        unsigned short * utdst = new unsigned short[w*h];
        for (int i = 0; i < w*h; ++i)
        {
            utdst[i] = static_cast<unsigned short>( result[i] );
        }
        dst.setFromPixels(utdst, w, h, OF_IMAGE_GRAYSCALE);
        delete [] utdst;
    }
    
public:
    ofxLabeling()
    {
    }
    
    ~ofxLabeling()
    {
    }
    
    ofImage getLabelingImage(){ return mrLabelingImage; }
    ofImage getVirtualColorImage(){ return mrVirtualColorImage; }
    ofShortImage getShortImage(){ return mrShortImage; }
    
    ofImage & getLabelingImageRef(){ return mrLabelingImage; }
    ofImage & getVirtualColorImageRef(){ return mrVirtualColorImage; }
    ofShortImage & getShortImageRef(){ return mrShortImage; }
    
    int getNumRegions(){ return base::GetNumOfRegions(); }
    int size() { return getNumRegions(); }
    
    ofVec2f getCenter(const int regionIndex)
    {
        float x, y;
        base::GetResultRegionInfo(regionIndex)->GetCenter(x, y);
        return ofVec2f(x, y);
    }
    
    ofVec2f getCentroid(const int regionIndex)
    {
        float x, y;
        base::GetResultRegionInfo(regionIndex)->GetCenterOfGravity(x, y);
        return ofVec2f(x, y);
    }
    
    ofVec2f getMin(const int regionIndex)
    {
        int x, y;
        base::GetResultRegionInfo(regionIndex)->GetMin(x, y);
        return ofVec2f(x, y);
    }
    
    ofVec2f getMax(const int regionIndex)
    {
        int x, y;
        base::GetResultRegionInfo(regionIndex)->GetMax(x, y);
        return ofVec2f(x, y);
    }
    
    int getNumPixels(const int regionIndex)
    {
        return base::GetResultRegionInfo(regionIndex)->GetNumOfPixels();
    }
    
    int Exec(ofImage & src,
             const bool is_sort_region,
             const int region_size_min,
             bool gen_uc_labeling_image = true,
             bool gen_virtual_color_image = true,
             bool gen_short_image = false)
    {
        if (isMultiChannel(src))
        {
            ofLogError("ofxLabeling") << "got multi channel image";
            return 1;
        }
        
        int w = src.getWidth();
        int h = src.getHeight();
        int size = w * h;
        short * tdst = new short[size];
        
        int res = base::Exec(src.getPixels(), tdst, src.getWidth(), src.getHeight(), is_sort_region, region_size_min);
        
        if (gen_uc_labeling_image) generateLabelingImageAsUC(tdst, w, h, mrLabelingImage);
        if (gen_virtual_color_image) generateVirtualColorImage(tdst, w, h, mrVirtualColorImage);
        if (gen_short_image) generateShortImage(tdst, w, h, mrShortImage);
        
        delete [] tdst;
        
        return res;
    }
};


typedef ofxLabeling<unsigned char,short> ofxLabelingBS;
typedef ofxLabeling<short,short> ofxLabelingSS;
typedef ofxLabeling<unsigned char,short>::RegionInfo ofxRegionInfoBS;
typedef ofxLabeling<short,short>::RegionInfo ofxRegionInfoSS;
