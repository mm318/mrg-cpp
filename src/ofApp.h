#pragma once

#include <vector>
#include <list>

#include "ofMain.h"
#include "ofxVideoRecorder.h"

#include "MRG.h"

#define _ENABLE_VIDEO_RECORDING (1)


class ofApp : public ofBaseApp
{
public:
  ofApp(MRG & neuron_model, const std::string & filename = "",
        int width = 1024, int height = 768);

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

  void recordingComplete(ofxVideoRecorderOutputFileCompleteEventArgs & args);

  MRG & m_neuron_model;
  std::vector<std::list<MRG_REAL>> m_data;

#if _ENABLE_VIDEO_RECORDING
  ofxVideoRecorder m_vid_recorder;
  std::string      m_video_name;
  std::string      m_file_extension;
#endif
  const int        m_width;
  const int        m_height;
  static constexpr int m_fps = 30;
};
