#pragma once
#include "ofxGui.h"
#include "ofxFreeMapping.h"
#include "ofxFreeMask.h"
#include "ofxJSON.h"

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
struct MaskConfig
{
    float layerWidth;
    float layerHeight;
    float maskWidth;
    float maskHeight;
    float x;
    float y;
    float maskBlendSize;
    bool isMaskBlending;
    
    // Default init layer 1x1 otherwise we have issues
    MaskConfig() :
        layerWidth(1),
        layerHeight(1),
        maskWidth(0),
        maskHeight(0),
        x(0),
        y(0),
        maskBlendSize(0),
        isMaskBlending(false)
    {}
    
    std::string toString()
    {
        return "{"
        "\"layerWidth\": " + std::to_string(layerWidth) +
        ",\"layerHeight\":" + std::to_string(layerHeight) +
        ",\"maskWidth\":" + std::to_string(maskWidth) +
        ",\"maskHeight\":" + std::to_string(maskHeight) +
        ",\"x\":" + std::to_string(x) +
        ",\"y\":" + std::to_string(y) +
        ",\"maskBlendSize\":" + std::to_string(maskBlendSize) +
        ",\"isMaskBlending\":" + std::to_string(isMaskBlending) +
        "}";
    }
};
    
public:
    ofDraggableMask();
    ~ofDraggableMask();
    
    void setup(std::string maskName, float layerWidth, float layerHeight);
    void setup(float layerWidth, float layerHeight,
               float maskWidth, float maskHeight,
               float initialXPosition, float initialYPosition,
               float blendWidth = 20, bool blendEdges = false);
    
    void beginLayer();
    void endLayer();
    
    void drawMask();
    void drawGui();
    
    void showConfig(bool showConfig);
    void saveConfig();
    void loadConfig();
    
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
    MaskConfig mConfig;
    bool mShowConfig;
    std::string mMaskName;
    ofxJSONElement mJsonElement;
    ofxFreeMask mMask;
    ofxFloatSlider mSliderXPosition, mSliderYPosition, mSliderWidth, mSliderHeight;
    ofxPanel mGui;
};
