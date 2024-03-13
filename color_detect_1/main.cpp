#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>

#include<Eigen/Core>
#include<Eigen/Geometry>

using namespace cv;
using namespace Eigen;
enum DetectColor {
    BLUE,
    RED,
    GREEN
};
//图像预处理
cv::Mat TrackleImage(const cv::Mat &image, DetectColor color) {
    std::vector<cv::Mat> rgb_vector;
    cv::Mat substract_image;
    cv::Mat substract_image_other;
    cv::split(image, rgb_vector);
    //通道相减
    if (color ==  GREEN) {
        substract_image = rgb_vector[1] - rgb_vector[2];
        substract_image_other = rgb_vector[1] - rgb_vector[0];
        bitwise_and(substract_image, substract_image_other, substract_image);
    }
    if (color ==  BLUE) {
        substract_image = rgb_vector[0] - rgb_vector[2];
        substract_image_other = rgb_vector[0] - rgb_vector[1];
        bitwise_and(substract_image, substract_image_other, substract_image);
    }
    if (color ==  RED) {
        substract_image = rgb_vector[2] - rgb_vector[0];
        substract_image_other = rgb_vector[2] - rgb_vector[1];
        bitwise_and(substract_image, substract_image_other, substract_image);
    }
    cv::Mat image_gray;
    cv::cvtColor(image,image_gray,COLOR_RGB2GRAY);
    threshold(substract_image, substract_image, 10, 255, 0);
//    threshold(image_gray, image_gray,30, 255, 0);
    cv::bitwise_and(substract_image, image_gray, image_gray);
    cv::Mat kernel;
    kernel=cv::getStructuringElement(0,cv::Size(3,3));
    cv::morphologyEx(substract_image,substract_image,1,kernel,Point (1,1),7);//膨胀
    cv::morphologyEx(substract_image,substract_image,0,kernel,Point (1,1),5);//腐蚀

//    cv::imshow("image_gray",image_gray);
//    cv::imshow("image_substract",substract_image);

    cv::waitKey(100);
    return substract_image;
}

int main()
{

    cv::VideoCapture video("/home/mzy/Downloads/绿色2.mp4");
    while(1){
        cv::Mat image;
        video>>image;
        if(image.empty()){
            break;
        }

//        //换成HSV空间
//        Mat hsvImage;
//        cvtColor(image, hsvImage, COLOR_BGR2HSV);
//        //确定颜色范围
//        Mat greenMask;
//        Scalar lowerGreen = Scalar(36, 25, 25); // 绿色范围下阈值
//        Scalar upperGreen = Scalar(86, 255, 255); // 绿色范围上阈值
//        //筛选颜色
//        Mat difference;
//        inRange(hsvImage, lowerGreen, upperGreen, difference);
//
//        //去噪声及二值化
//        Mat canny;
//        Canny(difference,canny,80,160,3,false);
//
//        //膨胀运算
//        cv::Mat kernel;
//        kernel=cv::getStructuringElement(0,cv::Size(3,3));
//        dilate(canny,canny,kernel);

        cv::Mat canny = TrackleImage(image, GREEN);

        //solvePnP
        std::vector<cv::Point3f> objectPoints;  // 世界坐标系中的三维点
        std::vector<cv::Point2f> imagePoints;   // 图像上的二维点

        //写入世界坐标
        // 左上角、右上角、左下角、右下角
        objectPoints.push_back(cv::Point3f(0, 0, 0));
        objectPoints.push_back(cv::Point3f(50, 0, 0));
        objectPoints.push_back(cv::Point3f(0, 70, 0));
        objectPoints.push_back(cv::Point3f(50, 70, 0));

        //相机内参
        cv::Mat cameraMatrix = (cv::Mat_<double>(3,3) << 693.6024624916828, 0, 361.3074812350097, 0, 691.8341429463832, 284.6358127896444, 0, 0, 1);

        //相机畸变
        cv::Mat distCoeffs = (cv::Mat_<double>(1,5) << -0.4449277961420404, 0.3006474538617177, 0.0007114715188471113, -0.001948190059129423, -0.1569243973289463);

        // 输出的旋转向量
        cv::Mat rvec;

        // 输出的平移向量
        cv::Mat tvec;

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

            //画矩形
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

            //坐标迁移
            for(int i=0;i<4;++i){
                imagePoints.push_back(points[i]);
            }

            //冒泡排序
            cv::Point2f topLeft, topRight, bottomRight, bottomLeft;
            float minX = FLT_MAX, minY = FLT_MAX;
            float maxX = FLT_MIN, maxY = FLT_MIN;

            for (const auto& point : imagePoints) {
                if (point.x <= minX && point.y <= minY) {
                    topLeft = point;
                    minX = point.x;
                    minY = point.y;
                }
                if (point.x >= maxX && point.y <= minY) {
                    topRight = point;
                    maxX = point.x;
                    minY = point.y;
                }
                if (point.x >= maxX && point.y >= maxY) {
                    bottomRight = point;
                    maxX = point.x;
                    maxY = point.y;
                }
                if (point.x <= minX && point.y >= maxY) {
                    bottomLeft = point;
                    minX = point.x;
                    maxY = point.y;
                }
            }

            // 新建一个vector存放四个点坐标，按照objectPoints的存放顺序进行存放
            std::vector<cv::Point2f> imagePoints2;
            imagePoints2.push_back(topLeft);
            imagePoints2.push_back(topRight);
            imagePoints2.push_back(bottomRight);
            imagePoints2.push_back(bottomLeft);


            bool success = cv::solvePnP(objectPoints, imagePoints2, cameraMatrix, distCoeffs, rvec, tvec);

            if (success) {
                // 获取旋转向量和平移向量的结果
                cv::Mat rotationMatrix;
                cv::Rodrigues(rvec, rotationMatrix);

                //Mat转换成Matrix3d
                Eigen::Matrix3d rotationMatrix2;
                rotationMatrix2 << rotationMatrix.at<double>(0, 0), rotationMatrix.at<double>(0, 1), rotationMatrix.at<double>(0, 2),
                        rotationMatrix.at<double>(1, 0), rotationMatrix.at<double>(1, 1), rotationMatrix.at<double>(1, 2),
                        rotationMatrix.at<double>(2, 0), rotationMatrix.at<double>(2, 1), rotationMatrix.at<double>(2, 2);
                //旋转矩阵转行成欧拉角
                Eigen::Vector3d euler_angles =  rotationMatrix2.eulerAngles(2,1,0);// roll pitch yaw

//                std::cout << "旋转向量:" << std::endl << rvec << std::endl;
//                std::cout << "平移向量:" << std::endl << tvec << std::endl;
//                std::cout << "旋转矩阵:" << std::endl << rotationMatrix << std::endl;
                std::cout<<"yall pitch roll ="<<euler_angles.transpose()<<std::endl;

            }
        }

        cv::imshow("video1", canny);
        cv::imshow("video2", image);
        cv::waitKey(1000 / video.get(cv::CAP_PROP_FPS));
    }
    return 0;
}
