# OpenCV

## 一，数据载入

读图像imread           

显示图像imshow      

读视频或调用摄像头VideoCapture     

保存图像imwrite

保存视频VideoWriter

## 二，基本操作

1.图像颜色空间

​     不同模型保存不同的信息，例如YUV保存亮度信息

​	像素存储的信息取决于颜色空间

2.颜色空间转化cvtColor

3.图像数据类型转化convertTo()

4.通道分离split

5.多通道合并merge

6.寻找像素最大值与最小值minMaxLoc

7.多通道变单通道reshape

8.图像二值化threshold

9.图像透视变化getPerspectiveTransform

10.画圆circle

11.画直线line

12.画椭圆ellipse

13.画多边形rectangle

14.拷贝copyTo

15.图像的交并补

16.模版匹配

## 三，图像滤波

线性滤波

1.均值滤波blur

2.方框滤波boxFilter

3.高斯滤波GaussianBlur

4.可分离滤波sepFilter2D

非线性滤波

1.中值滤波medianBlur

2.双边滤波bilateralFilter

边缘检测convertScaleAbs

## 四，图像形态学操作

1.腐蚀（消除物体边界点，使边界向内部收缩，同时可以消除微小的结构元素）

​    先生成结构单元getStructuringElement

​    再腐蚀erode

2.膨胀（目标增强，连接相邻对象，去除小的干扰物）

dilate

3.opencv提供了将腐蚀与膨胀不同组合的函数morphologyEx

实现开运算，闭运算，形态学梯度，顶帽运算，黑帽运算，以及击中击不中变换

## 五，应用

1.形状检测

直线检测HoughLines

直线检测并定位HoughLinesP

在众多坐标点中检测是否有直线HoughLinesPointSet

直线拟合fitLine

------------------------------------

圆形检测HoughCircles          P222

---------------------------------------------------------------

轮廓检测 

​      发现轮廓findContours

​      绘制轮廓drawContours

​      轮廓面积contourArea

​       轮廓周长arcLength

轮廓外接多边形

​	外接最大矩形boundingRect

​        最小外接矩形minAreaRect

​        寻找逼近轮廓的多边形approxPolyDP











