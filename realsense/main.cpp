#include <librealsense2/rs.hpp>
#include <opencv2/opencv.hpp>
#include <numeric>

int main()
{
    rs2::context ctx;
    rs2::device_list dev_list = ctx.query_devices();//链接所有摄像机，相当于数组类型
    if (dev_list.size() == 0) {
        std::cout << "fail" << std::endl;
        return EXIT_FAILURE;
    }

    rs2::device device = dev_list[0];//使用第一个摄像机
    rs2::sensor sensor = device.query_sensors()[0];//调用传感器

    rs2::pipeline pipe;//创建管道
    rs2::config cfg;//数据传输对象
    cfg.enable_stream(rs2_stream::RS2_STREAM_COLOR, 640, 480, rs2_format::RS2_FORMAT_BGR8, 30);//彩色流
    cfg.enable_stream(rs2_stream::RS2_STREAM_DEPTH, 640, 480, rs2_format::RS2_FORMAT_Z16, 30);//深度流
    pipe.start(cfg);

    while (true)//将视频转换成单张图片处理
    {
        rs2::frameset frames = pipe.wait_for_frames();//等待帧

        rs2::frame color_frame = frames.get_color_frame();// 获取当前帧的颜色图像
        rs2::frame depth_frame = frames.get_depth_frame();// 获取当前帧的深度图像

        //转换成opencv
        cv::Mat color_image(cv::Size(640, 480), CV_8UC3, (void*)color_frame.get_data(), cv::Mat::AUTO_STEP);
        cv::Mat depth_image(cv::Size(640, 480), CV_16U, (void*)depth_frame.get_data(), cv::Mat::AUTO_STEP);

        cv::imshow("Color", color_image);//展示彩色图像
        cv::imshow("Depth", depth_image);//展示深度图像

        int center_x = 320;//中心点
        int center_y = 240;
        std::vector<uint16_t> depths;
        for (int i = center_x - 2; i <= center_x + 2; i++) {
            for (int j = center_y - 2; j <= center_y + 2; j++) {
                uint16_t depth_value = depth_image.at<uint16_t>(j, i);//获取中心点周边每个点的深度
                depths.push_back(depth_value);//添加到容器中去
            }
        }
        uint16_t center_depth = depth_image.at<uint16_t>(center_y, center_x);//获取中心点的深度
        float average_depth = std::accumulate(depths.begin(), depths.end(), 0) / (float)depths.size();//平均值

        std::cout << "center" << center_depth << std::endl;
        std::cout << "average" << average_depth << std::endl;

        if (cv::waitKey(1) == 27)
            break;
    }
    pipe.stop();//关闭管道

    return EXIT_SUCCESS;
}