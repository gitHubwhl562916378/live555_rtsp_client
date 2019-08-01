#include <iostream>
#include "opencv2/opencv.hpp"
#include "RtspClientManager.h"

int main()
{
    RTSPClientManager rtspManager(6);
    std::thread o_thread([&]{
        std::this_thread::sleep_for(std::chrono::seconds(4));
        rtspManager.OpenRtsp("rtsp://192.168.2.253:8554/test.264",[](const AVPixelFormat format, const u_char *data, const int width, const int height){
            std::cout << "format:" << format << " width: " << width << " height:" << height << std::endl;
            cv::Mat frame(3 * height / 2, width, CV_8UC1, (void*)data);
            cv::cvtColor(frame, frame, CV_YUV2BGR_I420); //很耗cpu,i5 6核、384*288 30%左右.
            cv::imshow("small v" ,frame);
            cv::waitKey(1);
        });
        rtspManager.OpenRtsp("rtsp://192.168.2.38:5554/2",[](const AVPixelFormat format, const u_char *data, const int width, const int height){
            std::cout << "format:" << format << " width: " << width << " height:" << height << std::endl;
            cv::Mat frame(3 * height / 2, width, CV_8UC1, (void*)data);
            cv::cvtColor(frame, frame, CV_YUV2BGR_I420); //很耗cpu,i5 6核、384*288 30%左右.
            cv::imshow("big v" ,frame);
            cv::waitKey(1);
        });
        std::this_thread::sleep_for(std::chrono::seconds(5));
//        rtspManager.ShutDownClient("rtsp://192.168.2.253:8554/test.264");
    });
    rtspManager.RunEventLoop();

    return 0;
}
