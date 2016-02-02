#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>
#include <ctime>
#include <curl/curl.h>
#include <vector>
#include <sstream>
using namespace cv;
using namespace std;
using namespace std::chrono;

size_t write_data(char *ptr,size_t size, size_t nmemb, void *userdata){
  ostringstream * stream = (ostringstream *) userdata;
  size_t count = size * nmemb;
  stream->write(ptr,count);
  return count;
}

cv::Mat curlImg(){
  CURL * curl;
  CURLcode res;
  ostringstream stream;
  curl = curl_easy_init();
  curl_easy_setopt(curl, CURLOPT_URL, "http://192.168.0.6:8080/shot.jpg");
  curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION, write_data); //pass the write function
  curl_easy_setopt(curl,CURLOPT_WRITEDATA,&stream); // pass the stream ptr when the write function is called
  res = curl_easy_perform(curl); //startcurl
  string output = stream.str();
  curl_easy_cleanup(curl); //cleanup
  vector<char> data = vector<char> (output.begin(),output.end()); //convert string into vector
  Mat data_mat = cv::Mat(data); //creat the mat datatype from vector
  Mat image = cv::imdecode(data_mat,1); //read image from buffer
  return image;
}

int main(int argc, char* argv[])
{
  int numframes = 0;
  VideoCapture cap;






  time_point<system_clock> start, end;
  duration<double> elapsed_seconds;
  start = system_clock::now();
  namedWindow("images",1);
  for(;;)
    {
      Mat frame = curlImg();
      numframes++;
      end = system_clock::now();
      elapsed_seconds = end - start;
      if(elapsed_seconds.count() > 1.0){
	cout << "FPS : " << numframes/elapsed_seconds.count() << endl;
	numframes = 0;
	start = end;
      }
      imshow("images",frame);
      if(waitKey(20) >= 0) break;
    }
  return 0;
}
