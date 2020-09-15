#include <opencv2/opencv.hpp>

enum CaptureType { CAP_TYPE_ANDROID };

class ScreenCapture {
private:
  static int __captureFromAndroid(cv::Mat *);

public:
  ScreenCapture(CaptureType);
  ~ScreenCapture();

  int (*captureScreen)(cv::Mat *);
};
