#pragma once

#define _ENABLE_VIDEO_RECORDING (0)

#include <vector>
#include <list>

#include "ofMain.h"
#if _ENABLE_VIDEO_RECORDING
#include "ofxVideoRecorder.h"
#endif

#include "MRG.h"


class ofApp : public ofBaseApp
{
public:
  ofApp(MRG & neuron_model, const std::string & filename = "");

  void setup() override;
  void update() override;
  void draw() override;
  void exit() override;

  //---------------------------------------
  void keyPressed(int key) override;
  void keyReleased(int key) override;
  void mouseMoved(int x, int y ) override;
  void mouseDragged(int x, int y, int button) override;
  void mousePressed(int x, int y, int button) override;
  void mouseReleased(int x, int y, int button) override;
  void mouseEntered(int x, int y) override;
  void mouseExited(int x, int y) override;
  void windowResized(int w, int h) override;
  void dragEvent(ofDragInfo dragInfo) override;
  void gotMessage(ofMessage msg) override;

private:
  MRG_REAL get_vrest() const { return m_neuron_model.get_Vrest(); }

  MRG & m_neuron_model;
  std::vector<std::list<MRG_REAL>> m_data;

#if _ENABLE_VIDEO_RECORDING
  void recordingComplete(ofxVideoRecorderOutputFileCompleteEventArgs & args);

  ofxVideoRecorder m_vid_recorder;
  std::string      m_video_name;
  std::string      m_file_extension;
#endif

  static constexpr int m_fps = 30;
};
