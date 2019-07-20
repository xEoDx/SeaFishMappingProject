#pragma once
#include "ofxGui.h"
#include "ofxFreeMapping.h"
#include "ofxFreeMask.h"

/**
 * Description: creates a rectangular mask with a width,height which
 * can have alpha blended corners. The mask can be adjusted in position
 * and dimensions.
 *
 * Gui has to be drawn outside an ofxFreeScreen, as the TransformMatrix would
 * make the render to have a different position than the input logic.
 *
 * Blend can be adjusted to have it on any of the sides of the rectangle TODO
 */
class ofDraggableMask
{
public:
    ofDraggableMask(std::string maskName);
    ~ofDraggableMask();
    
    void setup(float layerWidth, float layerHeight,
               float maskWidth, float maskHeight,
               float initialXPosition, float initialYPosition,
               float blendWidth = 20, bool blendEdges = false);
    
    void beginLayer();
    void endLayer();
    
    void drawMask();
    void drawGui();
    
    void showConfig(bool showConfig);
    
private:
    void drawBlendRectangle(float initialPosition, float finalPosition,
                       float initialAlpha, float finalAlpha);
    
    void beginMasking();
    void endMasking();
        
    void OnXPositionChanged(float& value);
    void OnYPositionChanged(float& value);
    void OnMaskWidthChanged(float& value);
    void OnMaskHeightChanged(float& value);
    
private:
    bool mShowConfig;
    std::string mMaskName;
    ofxFreeMask mMask;
    ofxFloatSlider mSliderXPosition, mSliderYPosition, mSliderWidth, mSliderHeight;
    ofxPanel mGui;
    bool mDoBlendEdges;
    float mLayerWidth;
    float mLayerHeight;
    float mMaskWidth;
    float mMaskHeight;
    float mMaskBlendWidth;
    float mMaskXPosition;
    float mMaskYPosition;
};
