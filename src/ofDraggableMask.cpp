#include "ofDraggableMask.h"

//--------------------------------------------------------------
ofDraggableMask::ofDraggableMask(std::string maskName) :
    mMaskName(maskName),
    mShowConfig(true)
{}

//--------------------------------------------------------------
ofDraggableMask::~ofDraggableMask()
{}

//--------------------------------------------------------------
void ofDraggableMask::setup(float layerWidth, float layerHeight,
                            float maskWidth, float maskHeight,
                            float initialXPosition, float initialYPosition,
                            float blendWidth, bool blendEdges)
{
    mLayerWidth = layerWidth;
    mLayerHeight = layerHeight;
    mMaskWidth = maskWidth;
    mMaskHeight = maskHeight;
    mMaskXPosition = initialXPosition;
    mMaskYPosition = initialYPosition;
    mDoBlendEdges = blendEdges;
    mMaskBlendWidth = blendWidth;
    
    mMask.setup(layerWidth, layerHeight);
    mMask.newLayer();
    
    mGui.setup(mMaskName);
    mGui.add(mSliderXPosition.setup("X", mMaskXPosition, 0, mLayerWidth));
    mGui.add(mSliderYPosition.setup("y", mMaskYPosition, 0, mLayerHeight));
    mGui.add(mSliderWidth.setup("width", mMaskWidth, 0, mLayerWidth));
    mGui.add(mSliderHeight.setup("height", mMaskHeight, 0, mLayerHeight));
    mGui.setPosition(mMaskXPosition, mMaskYPosition);
    
    mSliderXPosition.addListener(this, &ofDraggableMask::OnXPositionChanged);
    mSliderYPosition.addListener(this, &ofDraggableMask::OnYPositionChanged);
    mSliderWidth.addListener(this, &ofDraggableMask::OnMaskWidthChanged);
    mSliderHeight.addListener(this, &ofDraggableMask::OnMaskHeightChanged);
}

//--------------------------------------------------------------
void ofDraggableMask::OnXPositionChanged(float& value)
{
    mMaskXPosition = value;
}

//--------------------------------------------------------------
void ofDraggableMask::OnYPositionChanged(float& value)
{
    mMaskYPosition = value;
}

//--------------------------------------------------------------
void ofDraggableMask::OnMaskWidthChanged(float& value)
{
    mMaskWidth = value;
}

//--------------------------------------------------------------
void ofDraggableMask::OnMaskHeightChanged(float& value)
{
    mMaskHeight = value;
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
    
    ofDrawRectangle(mMaskXPosition, mMaskYPosition, mMaskWidth, mMaskHeight);
    
    //mask blend
    drawBlendRectangle(mMaskXPosition, mMaskXPosition + mMaskBlendWidth, 255, 0);
    drawBlendRectangle(mMaskXPosition + (mMaskWidth - mMaskBlendWidth), mMaskXPosition + mMaskWidth, 0, 255);
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
        ofDrawRectangle(p, 0, 1, mMaskHeight);
        ofDisableAlphaBlending();
    }
}
