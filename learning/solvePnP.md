# solvePnP

用途：解决三维空间点到二维图像点的投影问题，即确定物体相对于相机的姿态（位置和旋转）

​           同时，可以从已知的几何形状和对应的图像中恢复出场景的三维结构。

OpenCV提供了PnP问题的解算函数

```cpp
bool solvePnP( InputArray objectPoints, InputArray imagePoints,
                            InputArray cameraMatrix, InputArray distCoeffs,
                            OutputArray rvec, OutputArray tvec,
                            bool useExtrinsicGuess = false, int flags = SOLVEPNP_ITERATIVE );
//作用：根据3D-2D点对应关系，获得物体的位姿。
//此函数返回旋转和平移向量，可用来将物体坐标系中的3D点变换到相机坐标系下
```

```cpp
bool solvePnPRansac( InputArray objectPoints, InputArray imagePoints,
                                  InputArray cameraMatrix, InputArray distCoeffs,
                                  OutputArray rvec, OutputArray tvec,
                                  bool useExtrinsicGuess = false, int iterationsCount = 100,
                                  float reprojectionError = 8.0, double confidence = 0.99,
                                  OutputArray inliers = noArray(), int flags = SOLVEPNP_ITERATIVE );
//使用Ransac算法剔除异常点
```

具体实践：

1.使用solvePnP前，需要已具备如下参数

```cpp
vector<Point3f>objPts;	//3D点数组，世界坐标系物体点坐标，至少4个点
vector<Point2f>imgPts;	//2D点数组，与以上物体点一一对应的图像点坐标
Mat cameraMatrix;	//相机内参矩阵，3x3矩阵
Mat distCoeff;	//相机畸变系数矩阵，我一般是用1x5矩阵，如果相机没有畸变，可以把所有元素置为0
```

2.然后调用

```cpp
Mat rvec, tvec;	//声明用于接收运算结果的两个矢量
solvePnP(objPts, imgPts, cameraMatrix, distCoeff, rvec, tvec);
```

3.得到解算结果后，rvec为旋转矢量形式，后续计算不方便，所以一般会用Rodrigues公式转为旋转矩阵，以下直接将rvec和tvec一起转为位姿矩阵

```cpp
Mat wldInCam = Mat::zeros(4, 4, CV_64FC1);
Rodrigues(rvec, wldInCam(Rect(0, 0, 3, 3)));
tvec.copyTo(wldInCam(Rect(3, 0, 1, 3)));
```

4.得到的wldInCam即为世界坐标系在相机坐标系中的位姿，如果需要求相机在世界坐标系中的位姿，可取逆即可

```cpp
Mat camInWld = wldInCam.inv();
```

