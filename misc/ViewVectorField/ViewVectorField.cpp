#include "vtkAutoInit.h" 
VTK_MODULE_INIT(vtkRenderingOpenGL2); // VTK was built with vtkRenderingOpenGL2
VTK_MODULE_INIT(vtkInteractionStyle);


#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkCubeSource.h>
#include <vtkArrowSource.h>
#include <vtkPolyData.h>
#include <vtkPoints.h>
#include <vtkPointData.h>
#include <vtkDataArray.h>
#include <vtkGlyph3D.h>
#include <vtkCellArray.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSimplePointsReader.h>
#include <vtkDoubleArray.h>
#include <vtkPolyDataAlgorithm.h>

#include <sstream>

int ViewVectorField(const std::string &data, const std::string &Normal)
{
	/*
	vtkSmartPointer<vtkPoints> points =
	vtkSmartPointer<vtkPoints>::New();
	points->InsertNextPoint(0, 0, 0);
	points->InsertNextPoint(1, 1, 1);
	points->InsertNextPoint(2, 2, 2);
	vtkSmartPointer<vtkPolyData> polydata =
	vtkSmartPointer<vtkPolyData>::New();
	polydata->SetPoints(points);
	*/

	vtkSmartPointer<vtkSimplePointsReader> pReader1 = vtkSmartPointer<vtkSimplePointsReader>::New();
	pReader1->SetFileName(data.c_str());

	/*
	vtkSmartPointer<vtkSimplePointsReader> pReader2 = vtkSmartPointer<vtkSimplePointsReader>::New();
	pReader2->SetFileName("C:\\sourcecode\\astri\\ObjectRecognition\\ObjectRecognition\\Normal.txt");
	*/

	vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
	pReader1->Update();
	polydata = pReader1->GetOutput();


	//polydata->GetPointData()->SetNormals(polydata2->GetPointData()->GetArray(0));
	//pReader1->GetOutput()->GetPointData()->SetNormals(pReader2->GetOutput()->GetPointData()->GetArray(0));

	vtkSmartPointer<vtkDoubleArray> pointNormalsArray = vtkSmartPointer<vtkDoubleArray>::New();
	{
		pointNormalsArray->SetNumberOfComponents(3); //3d normals (ie x,y,z)
		int NumOfData = polydata->GetNumberOfPoints();
		pointNormalsArray->SetNumberOfTuples(NumOfData);

		std::ifstream filestream(Normal);
		std::string line;
		int iter = 0;
		while (std::getline(filestream, line) && iter < NumOfData)
		{
			double x, y, z;
			std::stringstream linestream;
			linestream << line;
			linestream >> x >> y >> z;
			double pN[3] = { x, y, z };
			pointNormalsArray->SetTuple(iter, pN);
			iter++;
		}
	}

	polydata->GetPointData()->SetNormals(pointNormalsArray);


	vtkSmartPointer<vtkPolyData> glyph = vtkSmartPointer<vtkPolyData>::New();
	// Create anything you want here, we will use a cube for the demo.
	// Setup the arrows
	vtkSmartPointer<vtkArrowSource> arrowSource = vtkSmartPointer<vtkArrowSource>::New();

	vtkSmartPointer<vtkGlyph3D> glyph3D = vtkSmartPointer<vtkGlyph3D>::New();

	glyph3D->SetSourceConnection(arrowSource->GetOutputPort());
	glyph3D->OrientOn();
	glyph3D->SetVectorModeToUseNormal();
	glyph3D->SetScaleFactor(0.004);
	glyph3D->SetInputData(polydata);
	//glyph3D->SetInputConnection(polyDataAlg->GetOutputPort());
	//glyph3D->SetInputConnection(pReader1->GetOutputPort());
	glyph3D->Update();


	// Visualize
	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(glyph3D->GetOutputPort());

	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
	vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
	renderWindow->AddRenderer(renderer);
	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	renderWindowInteractor->SetRenderWindow(renderWindow);

	renderer->AddActor(actor);
	renderer->SetBackground(.3, .6, .3); // Background color green

	renderWindow->Render();
	renderWindowInteractor->Start();

	return EXIT_SUCCESS;

}


int main(int argc, char *argv[])
{
	std::string DataPath;
	std::string VectorPath;

	if (argc < 3)
	{
		DataPath = "C:\\temp\\log\\Detlog0\\PlaneEstimationlog0\\Plane_Est_SortedRawData.txt";
		VectorPath = "C:\\temp\\log\\Detlog0\\PlaneEstimationlog0\\Plane_Est_SortedNormal.txt";
	}
	else
	{
		DataPath = argv[1];
		VectorPath = argv[2];
	}

	ViewVectorField(
		DataPath
		, VectorPath);

	return 0;
}