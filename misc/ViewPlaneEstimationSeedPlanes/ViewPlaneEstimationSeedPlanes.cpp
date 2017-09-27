// ViewPlaneEstimationSeedPlanes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <windows.h>

#include "../general/Directories/directories.h"
#include "../general/BasicVisualizer/BasicVisualizer.h"
#include "vtkSimplePointsReader.h"


void GetRandomColor(int* rgb)
{
#define COLORREF_BASE		(256)
	srand(GetTickCount());
	int byRed, byGreen, byBlue;

	byRed = rand() % COLORREF_BASE;
	byGreen = rand() % COLORREF_BASE;
	byBlue = rand() % COLORREF_BASE;
	
	rgb[0] = byRed;
	rgb[1] = byGreen;
	rgb[2] = byBlue;
	return;
}

void ViewPlaneEstimationSeedPlanes(const std::string &FolderPath)
{

	std::string tag1 = "GrownSeedPlane";
	std::string tag2 = "SeedPlane";

	std::vector<std::string> AllFilePaths;
	listAllFilesPathsFromDir(FolderPath, ".txt", AllFilePaths);
	
	std::vector<std::string> GrownSeedPlanePaths;
	std::vector<std::string> SeedPlanePaths;
	for (int i = 0; i < AllFilePaths.size(); ++i)
	{
		std::string curFilePath = AllFilePaths.at(i);
		if (CheckIfFilePathContainSubPath(curFilePath, tag1))
		{
			GrownSeedPlanePaths.push_back(curFilePath);
		}
		else if (CheckIfFilePathContainSubPath(curFilePath, tag2))
		{
			SeedPlanePaths.push_back(curFilePath);
		}
	}

	BasicVisualizer bscVisualier;

	//bscVisualier.setBackgroundColor(0.3,0.6,0.3);
	for (int i = 0; i < GrownSeedPlanePaths.size(); ++i)
	{
		vtkSmartPointer<vtkSimplePointsReader> pReader1 = vtkSmartPointer<vtkSimplePointsReader>::New();
		pReader1->SetFileName(GrownSeedPlanePaths.at(i).c_str());
		pReader1->Update();
		std::string id = "GrownSeedPlane";
		id += std::to_string(i);

		bscVisualier.addPointCloud(pReader1, id);

		//linear map color
		int color[3];
		GetRandomColor(color);
		float factor = (float)1 / (float)256;
		//float color = ((float)(GrownSeedPlanePaths.size() - i)/ (float)GrownSeedPlanePaths.size()) * 0.5 + 0.5;
		bscVisualier.setPointCloudRenderingProperties(VISUAL_RENDER_PROP::COLOR, color[0] * factor, color[1]* factor, color[2]* factor, id); //white
		bscVisualier.setPointCloudRenderingProperties(VISUAL_RENDER_PROP::OPACITY, 1, id);
	}
	
	for (int i = 0; i < SeedPlanePaths.size(); ++i)
	{
		vtkSmartPointer<vtkSimplePointsReader> pReader1 = vtkSmartPointer<vtkSimplePointsReader>::New();
		pReader1->SetFileName(SeedPlanePaths.at(i).c_str());
		pReader1->Update();
		std::string id = "SeedPlane";
		id += std::to_string(i);

		bscVisualier.addPointCloud(pReader1, id);
		bscVisualier.setPointCloudRenderingProperties(VISUAL_RENDER_PROP::COLOR, 1, 1, 1, id); //white
		bscVisualier.setPointCloudRenderingProperties(VISUAL_RENDER_PROP::OPACITY, 1, id);
	}
	bscVisualier.Render();
}

int main(int argc, char *argv[])
{
	std::string FolderPath;

	if (argc < 2)
	{
		FolderPath = "C:\\temp\\log\\Detlog2\\PlaneEstimationlog0";
	}
	else
	{
		FolderPath = argv[1];
	}

	ViewPlaneEstimationSeedPlanes(FolderPath);

	return 0;
}

