#include "screenCapture.hpp"

#include <opencv2/highgui.hpp>

using namespace cv;

int main() {
  ScreenCapture capture(CAP_TYPE_ANDROID);
  Mat image;
  capture.captureScreen(&image);
  imshow("image", image);
  waitKey(0);
  return 0;
}