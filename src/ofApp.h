#pragma once

#include <list>

#include "ofMain.h"
#include "MRG.h"


class ofApp : public ofBaseApp
{
public:
  ofApp(MRG & neuron_model);

  void setup();
  void update();
  void draw();

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
  MRG & m_neuron_model;
  std::list<MRG_REAL> m_data;
};
