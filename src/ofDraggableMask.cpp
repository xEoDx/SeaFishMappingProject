#include "ofDraggableMask.h"

//--------------------------------------------------------------
ofDraggableMask::ofDraggableMask() :
    mShowConfig(true)
{}

//--------------------------------------------------------------
ofDraggableMask::~ofDraggableMask()
{}

//--------------------------------------------------------------
void ofDraggableMask::setup(std::string maskName, float layerWidth, float layerHeight)
{
    mMaskName = maskName + ".json";
    bool doesFileExist = mJsonElement.open(mMaskName);
    
    mConfig.layerWidth = layerWidth;
    mConfig.layerHeight = layerHeight;
    
    if(!doesFileExist)
    {
        mJsonElement.parse(mConfig.toString());
        mJsonElement.save(mMaskName);
    }
    
    loadConfig();
    
    mMask.setup(mConfig.layerWidth, mConfig.layerHeight);
    mMask.newLayer();
    
    mGui.setup(mMaskName);
    mGui.add(mSliderXPosition.setup("X", mConfig.x, 0, mConfig.layerWidth));
    mGui.add(mSliderYPosition.setup("y", mConfig.y, 0, mConfig.layerHeight));
    mGui.add(mSliderWidth.setup("width", mConfig.maskWidth, 0, mConfig.layerWidth));
    mGui.add(mSliderHeight.setup("height", mConfig.maskHeight, 0, mConfig.layerHeight));
    //TODO ADD TOGGLE FOR BLEND OR NOT ALPHA
    mGui.setPosition(mConfig.x, mConfig.y);
    
    mSliderXPosition.addListener(this, &ofDraggableMask::OnXPositionChanged);
    mSliderYPosition.addListener(this, &ofDraggableMask::OnYPositionChanged);
    mSliderWidth.addListener(this, &ofDraggableMask::OnMaskWidthChanged);
    mSliderHeight.addListener(this, &ofDraggableMask::OnMaskHeightChanged);
}

//--------------------------------------------------------------
void ofDraggableMask::saveConfig()
{
    mJsonElement.parse(mConfig.toString());
    mJsonElement.save(mMaskName);
}

//--------------------------------------------------------------
void ofDraggableMask::loadConfig()
{
    const float& layerWidth = mJsonElement["layerWidth"].asFloat();
    const float& layerHeight = mJsonElement["layerHeight"].asFloat();
    
    const float& maskWidth = mJsonElement["maskWidth"].asFloat();
    const float& maskHeight = mJsonElement["maskHeight"].asFloat();
    
    const float& x = mJsonElement["x"].asFloat();
    const float& y = mJsonElement["y"].asFloat();
    
    const float& maskBlendSize = mJsonElement["maskBlendSize"].asFloat();
    const float& isMaskBlending = mJsonElement["isMaskBlending"].asBool();
    
    mConfig.layerWidth = layerWidth;
    mConfig.layerHeight = layerHeight;
    mConfig.maskWidth = maskWidth;
    mConfig.maskHeight = maskHeight;
    mConfig.x = x;
    mConfig.y = y;
    mConfig.maskBlendSize = maskBlendSize;
    mConfig.isMaskBlending = isMaskBlending;
}

//--------------------------------------------------------------
void ofDraggableMask::OnXPositionChanged(float& value)
{
    mConfig.x = value;
}

//--------------------------------------------------------------
void ofDraggableMask::OnYPositionChanged(float& value)
{
    mConfig.y = value;
}

//--------------------------------------------------------------
void ofDraggableMask::OnMaskWidthChanged(float& value)
{
    mConfig.maskWidth = value;
}

//--------------------------------------------------------------
void ofDraggableMask::OnMaskHeightChanged(float& value)
{
    mConfig.maskHeight = value;
}

//--------------------------------------------------------------
void ofDraggableMask::beginLayer()
{
    mMask.beginLayer();
    ofSetColor(255,255);
}

//--------------------------------------------------------------
void ofDraggableMask::endLayer()
{
    mMask.endLayer();
}

//--------------------------------------------------------------
void ofDraggableMask::drawMask()
{
    beginMasking();
    endMasking();
}

//--------------------------------------------------------------
void ofDraggableMask::drawGui()
{
    if(mShowConfig)
    {
        mGui.draw();
    }
}

//--------------------------------------------------------------
void ofDraggableMask::beginMasking()
{
    mMask.beginMask();
    ofClear(0,0,0,255);
    ofSetColor(ofColor::white);
    ofFill();
    
    ofDrawRectangle(mConfig.x, mConfig.y, mConfig.maskWidth, mConfig.maskHeight);
    
    //mask blend
    drawBlendRectangle(mConfig.x, mConfig.x + mConfig.maskBlendSize, 255, 0);
    drawBlendRectangle(mConfig.x + (mConfig.maskWidth - mConfig.maskBlendSize), mConfig.x + mConfig.maskBlendSize, 0, 255);
}

//--------------------------------------------------------------
void ofDraggableMask::endMasking()
{
    mMask.endMask();
    mMask.draw();
}

//--------------------------------------------------------------
void ofDraggableMask::showConfig(bool showConfig)
{
    mShowConfig = showConfig;
}

//--------------------------------------------------------------
void ofDraggableMask::drawBlendRectangle(float initialPosition, float finalPosition,
                               float initialAlpha, float finalAlpha)
{
    for(float p = initialPosition; p <= finalPosition; p++)
    {
        float lerpedAlpha = ofLerp(initialAlpha, finalAlpha, (p-initialPosition)/(finalPosition-initialPosition));
        ofEnableAlphaBlending();
        ofSetColor(0, 0, 0, lerpedAlpha);
        ofDrawRectangle(p, 0, 1, mConfig.maskHeight);
        ofDisableAlphaBlending();
    }
}
