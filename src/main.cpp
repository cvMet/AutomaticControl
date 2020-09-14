#include <errno.h>
#include <opencv2/opencv.hpp>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int captureScreen(cv::Mat *pmat) {
  if (!pmat) {
    fprintf(stderr, "param <pmat = NULL> is invalid\n");
    return -EINVAL;
  }
  const char *cmd = "adb shell screencap -p";
  FILE *file = popen(cmd, "r");
  if (!file) {
    int err = errno;
    fprintf(stderr, "popen('%s', 'r') failed: %s\n", cmd, strerror(err));
    return -err;
  }
  std::vector<uint8_t> bytes;
  while (1) {
    uint8_t buffer[1024];
    size_t read_len = fread(buffer, 1, sizeof(buffer), file);
    if (read_len > sizeof(buffer) || (read_len == 0 && errno == EINVAL)) {
      int err = errno;
      pclose(file);
      fprintf(stderr, "fread(buffer, 1, %lu, file) failed: %s\n",
              sizeof(buffer), strerror(err));
      return -err;
    }
    if (read_len == 0)
      break;
    bytes.insert(bytes.end(), buffer, buffer + sizeof(buffer));
  }
  pclose(file);
  if (bytes.size() == 0) {
    fprintf(stderr, "0 bytes read, IO error\n");
    return -EIO;
  }
  cv::imdecode(bytes, cv::IMREAD_UNCHANGED, pmat); // e.g. IMREAD_GRAYSCALE
  return 0;
}

int main() {
  cv::Mat mat;
  captureScreen(&mat);
  cv::imshow("show", mat);
  cv::waitKey(0);
  return 0;
}