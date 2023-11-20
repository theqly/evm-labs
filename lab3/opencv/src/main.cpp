#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

int main(int argc, char *argv[]) {

  cv::VideoCapture cam(0);
  if(!cam.isOpened()){
    std::cout << "video not opened" << std::endl;
    return 0;
  }

  cv::CascadeClassifier cascade;
  cascade.load("../haarcascade_frontalface_alt2.xml");

  cv::Mat frame;
  double fps = 0;
  double processingTime = 0;
  while (true) {
    auto start = (double)cv::getTickCount();
    cam.read(frame);
    std::vector<cv::Rect> faces;
    cascade.detectMultiScale(frame, faces, 1.1, 2, 0, cv::Size(30,30));
    for(auto & face : faces){
      cv::Point center(face.x + face.width*0.5, face.y + face.height*0.5);
      cv::ellipse(frame, center, cv::Size(face.width*0.5, face.height*0.5), 0, 0, 360, cv::Scalar(255, 0, 0), 3, 8, 0);
    }
    imshow("cam", frame);
    auto end = (double)cv::getTickCount();
    if (cv::waitKey(1) == 'q') break;
    fps = cv::getTickFrequency() / (end - start);
    processingTime = (end - start) / cv::getTickFrequency() * 1000;
    std::cout << "FPS: " << fps << " Processing Time: " << processingTime << " ms" << std::endl;
  }

  cam.release();
  cv::destroyAllWindows();

  return 0;
}