#include <iostream>  
#include <iomanip>  
#include <fstream>  
#include <cv.h> 

using namespace std;



int ReadImgPoints(string txtpath, 
	std::vector< cv::Point2d >& points2D
	)
{
	char buffer[50];
	ifstream myfile(txtpath);

	if (!myfile) {
		cout << "Unable to open myfile";
		getchar();
		exit(0);
	}
	
	float a, b;
	
	int i = 0;

	while (!myfile.eof()&& i<points2D.size() )
	{
		myfile.getline(buffer, 100);
		sscanf_s(buffer, "%f %f", &a, &b);
		//cout << a << " " << b << endl;
		points2D[i] = cv::Point2d(a, b);
		i++;
	}
	myfile.close();
	return 0;
}

//===============================================
int Read3DPoints(string txtpath,
	std::vector< cv::Point3d >& points3D
	)
{
	char buffer[100];
	ifstream myfile(txtpath);

	if (!myfile) {
		cout << "Unable to open myfile";
		getchar();
		exit(0);
	}

	float a, b ,c;

	int i = 0;

	while (!myfile.eof() && i<points3D.size())
	{
		myfile.getline(buffer, 50);
		sscanf_s(buffer, "%f %f %f", &a, &b, &c);
		//cout << a << " " << b << endl;
		points3D[i] = cv::Point3d(a, b, c);
		i++;
	}
	myfile.close();
	return 0;
}

int LoadData(
	std::vector< cv::Point3d >&  points3D,
	std::vector< std::vector< cv::Point2d > >& pointsImg,
	int NCAMS,
	int NPOINTS,
	std::vector<std::string> pointsImgFileList,
	string points3DFile
	)
{

	
	pointsImg.resize(NCAMS);
	for (int i = 0; i < NCAMS; i++)
	{
		pointsImg[i].resize(NPOINTS);
		ReadImgPoints(
			pointsImgFileList[i],
			pointsImg[i]
			);
	}
	
	points3D.resize(NPOINTS);
	Read3DPoints(
		points3DFile,
		points3D
		);
		
	return 0;
}

//===================================================================
void loadCameraPar(
	string txtpath,
	cv::Mat& cameraMatrix,
	cv::Mat& Ri,
	cv::Mat& Ti
	)
{
	char buffer[100];
	ifstream myfile(txtpath);

	if (!myfile) {
		cout << "Unable to open myfile";
		getchar();
		exit(0);
	}

	float a, b, c;

	int i = 0,j = 0,lenIndex = 0;

	float data[3][3];

	//摄像机内参====================================
	while (i<3)
	{
		myfile.getline(buffer, 100);
		sscanf_s(buffer, "%f %f %f", &a, &b, &c);
		//cout <<"read"<< a << " " << b << " " << c << endl;
		data[i][0] = a;   data[i][1] = b;   data[i][2] = c;
		i++;
		lenIndex++;
	}
	cameraMatrix = cv::Mat::eye(3, 3, CV_64FC1);
	cameraMatrix.ptr<double>(0)[0] = data[0][0];
	cameraMatrix.ptr<double>(0)[4] = data[1][1];
	cameraMatrix.ptr<double>(0)[2] = data[0][2];
	cameraMatrix.ptr<double>(0)[5] = data[1][2];

	//==============================================
	//摄像机R==============================
	myfile.getline(buffer, 100); //空一行
 
	myfile.getline(buffer, 100);
	sscanf_s(buffer, "%f  %f  %f", &a, &b, &c);
	//cout << "read" << a << " " << b << " " << c << endl;
	Ri.ptr<double>(0)[0] = a;
	Ri.ptr<double>(0)[1] = b;
	Ri.ptr<double>(0)[2] = c;
	//==============================================
	//摄像机T==============================
	myfile.getline(buffer, 100);
	sscanf_s(buffer, "%f  %f  %f", &a, &b, &c);
	//cout << "read" << a << " " << b << " " << c << endl;
	Ti.ptr<double>(0)[0] = a;
	Ti.ptr<double>(0)[1] = b;
	Ti.ptr<double>(0)[2] = c;

	//cout << "~~~~~~~~~~~~~~~~~~~~~~"<< endl;
	//==============================================


	myfile.close();

}
