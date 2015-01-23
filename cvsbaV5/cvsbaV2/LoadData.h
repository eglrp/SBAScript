#pragma once
#include <cv.h> 
#include <iostream>
using namespace std;

int Read3DPoints(
	string txtpath,
	std::vector< cv::Point3d >& points3D
	);

int ReadImgPoints(
	string txtpath,
	std::vector< cv::Point2d >& points2D
	);

int LoadData(
	std::vector< cv::Point3d >&  points3D,
	std::vector< std::vector< cv::Point2d > >& pointsImg,
	int NCAMS,
	int NPOINTS,
	std::vector<std::string> pointsImgFileList,
	string points3DFile
	);

void loadCameraPar(
	string txtpath,
	cv::Mat& cameraMatrix,
	cv::Mat& Ri,
	cv::Mat& Ti
	);