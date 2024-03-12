#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>

using namespace cv;

int main()
{

    cv::VideoCapture video("/home/mzy/Downloads/坐标解算视频/绿色.mp4");
    while(1){
        cv::Mat image;
        video>>image;
        if(image.empty()){
            break;
        }
        //换成HSV空间
        Mat hsvImage;
        cvtColor(image, hsvImage, COLOR_BGR2HSV);
        //确定颜色范围
        Mat greenMask;
        Scalar lowerGreen = Scalar(36, 25, 25); // 绿色范围下阈值
        Scalar upperGreen = Scalar(86, 255, 255); // 绿色范围上阈值
        //筛选颜色
        Mat difference;
        inRange(hsvImage, lowerGreen, upperGreen, difference);

//        Mat greenChannel, blueChannel;
//        Mat difference;
 //       std::vector<cv::Mat> channels;
  //      split(image, channels);
 //       subtract(channels[1], channels[0], difference); // 绿色通道减去蓝色通道
        //Mat thresholded;
        //threshold(difference, thresholded, 0, 255, THRESH_BINARY);


        //去噪声及二值化
        Mat canny;
        Canny(difference,canny,80,160,3,false);
        //膨胀运算
        cv::Mat kernel;
        kernel=cv::getStructuringElement(0,cv::Size(3,3));
        dilate(canny,canny,kernel);

        //轮廓发现与绘制
        std::vector<std::vector<Point>> contours;
        std::vector<Vec4i> hierarchy;
        findContours(canny,contours,hierarchy,0,2,Point());

        //寻找轮廓外接矩形
        for(int n=0;n < contours.size();++n){
            //面积筛选
            double area = contourArea(contours[n]);
            if(area<9750){
                continue;
               // contours.erase(contours.begin() + n);
            }
            cv::RotatedRect rrect =minAreaRect(contours[n]);
            cv::Point2f points[4];
            rrect.points(points);
            for(int i=0;i<4;++i){
                if(i==3){
                    cv::line(image,points[i],points[0],cv::Scalar(0,255,0),2,8,0);
                    break;
                }
                cv::line(image,points[i],points[i+1],cv::Scalar(0,255,0),2,8,0);
            }

        }


        cv::imshow("video1", canny);
        cv::imshow("video2", image);
        cv::waitKey(1000 / video.get(cv::CAP_PROP_FPS));



    }
    return 0;
}
