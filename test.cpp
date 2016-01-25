#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <chrono>
#include <ctime>

using namespace cv;
using namespace std;
using namespace std::chrono;

int main(int argc, char* argv[])
{
  int numframes = 0;
  VideoCapture cap;
    cap.set(CV_CAP_PROP_BUFFERSIZE,3);
  cap.open("http://localhost:4747/mjpegfeed?320x240");
  if(!cap.isOpened()) //if no succes, exit program
    {
      cout << "Cannot open the video cam" << endl;
      return -1;
    }
  time_point<system_clock> start, end;
  duration<double> elapsed_seconds;
  start = system_clock::now();
  namedWindow("images",1);
  for(;;)
    {
      Mat frame;
      cap >> frame;
      numframes++;
      end = system_clock::now();
      elapsed_seconds = end - start;
      if(elapsed_seconds.count() > 1.0){
	cout << "FPS : " << numframes/elapsed_seconds.count() << endl;
	numframes = 0;
	start = end;
      }
      // imshow("images",frame);
      // if(waitKey(20) >= 0) break;
    }
  return 0;
}
