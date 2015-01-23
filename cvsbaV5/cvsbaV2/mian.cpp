#include <cv.h> 
#include <cxcore.hpp>
#include <calib3d.hpp>
#include <calib3d\calib3d_c.h>
#include <opencv2\core\mat.hpp>
#include <highgui.h> 
#include"iostream"

#include "cvsba.h"
#include "readparams.h"

#include "LoadData.h"

#include <fstream>

using namespace std; 

/*
void readDataCVFormat(char* camfile, char* ptsfile, std::vector<cv::Point3f>& points, std::vector<std::vector<cv::Point2f> >& imagePoints,
	std::vector<std::vector<int> >& visibility, std::vector<cv::Mat>& cameraMatrix, std::vector<cv::Mat>& distCoeffs,
	std::vector<cv::Mat>& R, std::vector<cv::Mat>& T);
	*/

int main(int argc, char *argv[])
{ 
	/*
	IplImage * test; 
	test = cvLoadImage ("D:\\demo.jpg"); 
	cvNamedWindow("test_demo", 1); 
	cvShowImage("test_demo", test); 
	cvWaitKey(0); 
	cvDestroyWindow("test_demo"); 
	cvReleaseImage(&test); 
	*/
	
	std::vector< cv::Point3d > points3D;
	std::vector< std::vector< cv::Point2d > > pointsImg;
	std::vector< std::vector< int > > visibility;
	std::vector< cv::Mat > cameraMatrix, distCoeffs, R, T;

	if (argc != 3) 
	{
		cout << "Input Wrong£¡" << endl;
		cout << argc << endl;
		
		return 1;
	}
	//int NPOINTS = 162; // number of 3d points
	int NPOINTS = 378;
	int NCAMS = 4; // number of cameras

	NCAMS   = atoi(argv[1]);
	NPOINTS = atoi(argv[2]);

	cout << NCAMS << endl
		<< NPOINTS << endl;

	
	// fill 3D points and Img points

	pointsImg.resize(NCAMS);
	points3D.resize(NPOINTS);

	std::vector<std::string> pointsImgFileList;
	pointsImgFileList.resize(NCAMS);
	pointsImgFileList[0] = ".//datafile//pic88.txt";
	pointsImgFileList[1] = ".//datafile//pic89.txt";
	pointsImgFileList[2] = ".//datafile//pic98.txt";
	pointsImgFileList[3] = ".//datafile//pic99.txt";

	string points3DFile = ".//datafile//threeD.txt";

	LoadData(points3D, pointsImg, NCAMS, NPOINTS,pointsImgFileList, points3DFile);

	//cout << pointsImg[1] << endl;

	// fill visibility (all points are visible)
	visibility.resize(NCAMS);
	for (int i = 0; i<NCAMS; i++) {
		visibility[i].resize(NPOINTS);
		for (int j = 0; j<NPOINTS; j++) visibility[i][j] = 1;
	}

	// fill camera intrinsics (same intrinsics for all cameras)
	cameraMatrix.resize(NCAMS);
	R.resize(NCAMS);
	for (int i = 0; i<NCAMS; i++) {
		R[i] = cv::Mat(3, 1, CV_64FC1, cv::Scalar::all(0));
	}
	T.resize(NCAMS);
	for (int i = 0; i<NCAMS; i++) {
		T[i] = cv::Mat(3, 1, CV_64FC1, cv::Scalar::all(0));
	}

	
	loadCameraPar(".//datafile//Par88.txt", cameraMatrix[0], R[0], T[0]);
	loadCameraPar(".//datafile//Par89.txt", cameraMatrix[1], R[1], T[1]);
	loadCameraPar(".//datafile//Par98.txt", cameraMatrix[2], R[2], T[2]);
	loadCameraPar(".//datafile//Par99.txt", cameraMatrix[3], R[3], T[3]);
	
	// fill distortion (assume no distortion)
	distCoeffs.resize(NCAMS);
	for (int i = 0; i<NCAMS; i++) distCoeffs[i] = cv::Mat(5, 1, CV_64FC1, cv::Scalar::all(0));
	
	//***********************************

	//****** RUN BUNDLE ADJUSTMENT ******
	cvsba::Sba sba;
	sba.run(points3D, pointsImg, visibility, cameraMatrix, R, T, distCoeffs);

	std::cout << "Initial error=" << sba.getInitialReprjError() << ". " <<
		"Final error=" << sba.getFinalReprjError() << std::endl;
	/***********************************/
	//Êä³ö
	cout << "%===============Result:=====================" << endl;

	for (int i = 0; i < NCAMS; i++)
	{
		cout << "%#"<<i<< endl << endl;
		cout <<"R"<<i<< " = "<< R[i] << endl;
		cout <<"T"<<i<< " = " <<T[i] << endl;
		cout << "%--------------------------------------------" << endl;
	}

	ofstream fcout("./cvCBA_Result.m", ios::out);
	if (!fcout) cout<<"can't write";
	for (int i = 0; i < NCAMS; i++)
	{
		fcout << "%#" << i << endl << endl;
		fcout << "R" << i << " = " << R[i] << ";" << endl;
		fcout << "T" << i << " = " << T[i] << ";" << endl;
		fcout << "%--------------------------------------------" << endl;
	}
	fcout << "%--------------------------------------------" << endl;
	fcout.close();
	
	//getchar();
	
	return 0;
}
