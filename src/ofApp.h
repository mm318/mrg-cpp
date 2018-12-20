#pragma once

#include "ofMain.h"
#include "MRG.h"


class ofApp : public ofBaseApp
{
public:
  ofApp(RingBuffer<MRG_MATRIX_REAL> & input_buffer) : ofBaseApp(), m_input_buffer(input_buffer) {}

  void setup();
  void update();
  void draw();

  void setupSignedNoiseDemo();
  void updateSignedNoiseDemo();
  void renderSignedNoiseDemo();
  void renderNoisyRobotArmDemo();

  //---------------------------------------
  void keyPressed(int key);
  void keyReleased(int key);
  void mouseMoved(int x, int y );
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  void mouseEntered(int x, int y);
  void mouseExited(int x, int y);
  void windowResized(int w, int h);
  void dragEvent(ofDragInfo dragInfo);
  void gotMessage(ofMessage msg);

private:
  RingBuffer<MRG_MATRIX_REAL> & m_input_buffer;

  float * signedNoiseData;
  int nSignedNoiseData;

  float radialNoiseCursor;
  float radialNoiseDemoX;
  float radialNoiseDemoY;
  float radialNoiseDemoR; // radius
};
