#ifdef IS_USE_MY_PCL
#include <pcl/io/pcd_io.h>
#include <pcl/io/vtk_lib_io.h>
#include <pcl/conversions.h>
#endif

#include "vtkAutoInit.h"

#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkPoints.h>
#include <vtkPointData.h>
#include <vtkCenterOfMass.h>
#include <vtkTransform.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyDataAlgorithm.h>
#include <vtkProperty.h>
#include <vtkTextActor.h>
#include <vtkTextProperty.h>

#include <string>
#include <algorithm>
#include "BasicVisualizer.h"



BasicVisualizer::BasicVisualizer()
{
	VTK_MODULE_INIT(vtkRenderingOpenGL2); // VTK was built with vtkRenderingOpenGL2
	VTK_MODULE_INIT(vtkInteractionStyle);
	VTK_MODULE_INIT(vtkRenderingFreeType);

	m_pRenderer = vtkSmartPointer<vtkRenderer>::New();
	m_bIsUseRenderWindow = false;


}


BasicVisualizer::~BasicVisualizer()
{
}

void BasicVisualizer::setPointCloudRenderingProperties(int RenderProperty,
	double value1,
	double value2,
	double value3,
	const std::string &id)
{
	switch (RenderProperty)
	{
	case VISUAL_RENDER_PROP::COLOR:
		if (ActorsContains(id)) // found
		{
			vtkSmartPointer<vtkActor> pActor = m_MapActors.at(id);
			pActor->GetProperty()->SetColor(value1, value2, value3);
		}
		break;
	default:
		break;
	}
}

void BasicVisualizer::setPointCloudRenderingProperties(int RenderProperty,
	double value1,
	double value2,
	const std::string &id)
{


}

void BasicVisualizer::setPointCloudRenderingProperties(int RenderProperty,
	double value,
	const std::string &id)
{
	switch (RenderProperty) {
	case VISUAL_RENDER_PROP::POINT_SIZE:
		if (ActorsContains(id)) // found
		{
			vtkSmartPointer<vtkActor> pActor = m_MapActors.at(id);
			pActor->GetProperty()->SetPointSize(value);
		}
		break;
	case VISUAL_RENDER_PROP::OPACITY:
		if (ActorsContains(id)) // found
		{
			vtkSmartPointer<vtkActor> pActor = m_MapActors.at(id);
			pActor->GetProperty()->SetOpacity(value);
		}
		break;
	case VISUAL_RENDER_PROP::LINE_WIDTH:
		if (ActorsContains(id)) // found
		{
			vtkSmartPointer<vtkActor> pActor = m_MapActors.at(id);
			pActor->GetProperty()->SetLineWidth(value);
		}
		break;
	default:
		;
	}

}

void BasicVisualizer::setBackgroundColor(double value1,
	double value2,
	double value3)
{
	m_BackgroundColor[0] = value1;
	m_BackgroundColor[1] = value2;
	m_BackgroundColor[2] = value3;

	if (m_pRenderer)
	{
		m_pRenderer->SetBackground(value1, value2, value3); 
	}
}

#ifdef IS_USE_MY_PCL
void BasicVisualizer::addPointCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr pCloud,const std::string &id)
{
	if (ActorsContains(id))
	{
		return;
	}
	vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
	{
		pcl::io::pointCloudTovtkPolyData(*pCloud, polydata);
	}
	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputData(polydata);
	vtkSmartPointer<vtkActor> pActor = vtkSmartPointer<vtkActor>::New();
	pActor->SetMapper(mapper);
	m_MapActors[id] = pActor;
	m_vIDInOrder.push_back(id);
}
void BasicVisualizer::addPointCloud(pcl::PointCloud<pcl::PointXYZRGBA>::Ptr pCloud, const std::string &id)
{
	if (ActorsContains(id))
	{
		return;
	}

	vtkSmartPointer<vtkPolyData> polydata = vtkSmartPointer<vtkPolyData>::New();
	{
		pcl::io::pointCloudTovtkPolyData(*pCloud, polydata);
	}
	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputData(polydata);
	vtkSmartPointer<vtkActor> pActor = vtkSmartPointer<vtkActor>::New();
	pActor->SetMapper(mapper);
	m_MapActors[id] = pActor;

	vtkSmartPointer<vtkPolyDataAlgorithm> dummy = vtkSmartPointer<vtkPolyDataAlgorithm>::New();
	m_vIDInOrder.push_back(id);
}
#endif
void BasicVisualizer::addPointCloud(vtkSmartPointer<vtkPolyDataAlgorithm> polydataAlg, 
							const std::string &id)
{
	if (ActorsContains(id))
	{
		return;
	}
	

	vtkSmartPointer<vtkPolyDataMapper> pMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	pMapper->SetInputConnection(polydataAlg->GetOutputPort());
	vtkSmartPointer<vtkActor> pActor = vtkSmartPointer<vtkActor>::New();
	pActor->SetMapper(pMapper);
	m_MapActors[id] = pActor;
	
	m_vIDInOrder.push_back(id);
}

void BasicVisualizer::addText(const std::string &text, const int locationX, const int locationY, float fontsize, double r, double g, double b, const std::string &id)
{
	// Setup the text and add it to the renderer
	vtkSmartPointer<vtkTextActor> ptextActor = vtkSmartPointer<vtkTextActor>::New();
	ptextActor->SetInput(text.c_str());
    ptextActor->SetPosition(locationX, locationY);
	ptextActor->GetTextProperty()->SetFontSize(fontsize);
	ptextActor->GetTextProperty()->SetColor(r, g, b);
	m_MapActors2D[id] = ptextActor;
	
	m_vIDInOrder.push_back(id);
}

void BasicVisualizer::TransformObject(const TRANS_PARA &Trans, const std::string &id)
{
    std::map<std::string, vtkSmartPointer<vtkActor>>::iterator  iter = m_MapActors.find(id);
    if (iter != m_MapActors.end()) //found
    {
        vtkSmartPointer<vtkCenterOfMass> COMFilter = vtkSmartPointer<vtkCenterOfMass>::New();
        COMFilter->SetInputData(vtkPolyData::SafeDownCast(iter->second->GetMapper()->GetInput()));
        COMFilter->SetUseScalarsAsWeights(false);
        COMFilter->Update();

        double center[3];
        COMFilter->GetCenter(center);


        vtkSmartPointer<vtkTransform> ptrans = vtkSmartPointer<vtkTransform>::New();
        ptrans->PostMultiply();
        ptrans->Translate(-center[0], -center[1],-center[2]);
        ptrans->RotateX( Trans.alpha);
        ptrans->RotateY(Trans.beta);
        ptrans->RotateZ(Trans.gamma);
        ptrans->Scale(Trans.scale,Trans.scale,Trans.scale);
        ptrans->Translate(center[0], center[1],center[2]);

        ptrans->Translate(Trans.dx, Trans.dy, Trans.dz);
        iter->second->SetUserTransform(ptrans);
    }

    m_pRenderer->ResetCamera();

}

void BasicVisualizer::TransformObject(const vtkSmartPointer<vtkMatrix4x4> pMat, const std::string &id)
{
	std::map<std::string, vtkSmartPointer<vtkActor>>::iterator  iter = m_MapActors.find(id);
	if (iter != m_MapActors.end()) //found
	{
		vtkSmartPointer<vtkCenterOfMass> COMFilter = vtkSmartPointer<vtkCenterOfMass>::New();
		COMFilter->SetInputData(vtkPolyData::SafeDownCast(iter->second->GetMapper()->GetInput()));
		COMFilter->SetUseScalarsAsWeights(false);
		COMFilter->Update();

		double center[3];
		COMFilter->GetCenter(center);

		vtkSmartPointer<vtkTransform> ptrans = vtkSmartPointer<vtkTransform>::New();

		ptrans->SetMatrix(pMat);
		iter->second->SetUserTransform(ptrans);
	}
	m_pRenderer->ResetCamera();

}

void BasicVisualizer::deleteObject(const std::string &id)
{
	if (ActorsContains(id)) // found
	{
		m_MapActors.erase(id);	
	}
	if (Actors2DContains(id)) // found
	{
		m_MapActors2D.erase(id);
	}
	if (IDInOrderContains(id)) // found
	{
		m_vIDInOrder.erase(std::remove(m_vIDInOrder.begin(), m_vIDInOrder.end(), id), m_vIDInOrder.end());
	}
}

void BasicVisualizer::ConstructRenderer()
{
	m_pRenderer->RemoveAllViewProps();

	for (int i = 0; i < m_vIDInOrder.size(); ++i)
	{
		std::string id = m_vIDInOrder.at(i);
		if (m_MapActors.find(id) != m_MapActors.end()) // found
		{
			m_pRenderer->AddActor(m_MapActors[id]);
		}

		if (m_MapActors2D.find(id) != m_MapActors2D.end()) // found
		{
			m_pRenderer->AddActor(m_MapActors2D[id]);
		}
	}
	m_pRenderer->SetBackground(m_BackgroundColor[0], m_BackgroundColor[1], m_BackgroundColor[2]); 
	
    m_pRenderer->ResetCamera();
}
bool BasicVisualizer::ActorsContains(const std::string &id)
{
	if (m_MapActors.find(id) != m_MapActors.end()) // found
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool BasicVisualizer::Actors2DContains(const std::string &id)
{
	if (m_MapActors2D.find(id) != m_MapActors2D.end()) // found
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool BasicVisualizer::IDInOrderContains(const std::string &id)
{
	if (std::find(m_vIDInOrder.begin(), m_vIDInOrder.end(), id) != m_vIDInOrder.end())  // found
	{
		return true;
	}
	else
	{
		return false;
	}

}


vtkSmartPointer<vtkRenderer> BasicVisualizer::GetRenderer()
{
	ConstructRenderer();
	return m_pRenderer;
}

void BasicVisualizer::Render()
{
	ConstructRenderer();
	if (m_bIsUseRenderWindow == false)
	{
		m_renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
		m_renderWindow->AddRenderer(m_pRenderer);

		m_renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
		m_renderWindowInteractor->SetRenderWindow(m_renderWindow);

		m_bIsUseRenderWindow = true;
	}

	m_renderWindow->Render();
	m_renderWindowInteractor->Start();
}

void BasicVisualizer::CleanDisplay()
{
	m_pRenderer->RemoveAllViewProps();
	/*
	for (auto it = m_MapActors.begin(); it != m_MapActors.end(); ++it)
	{
		m_pRenderer->RemoveActor(it->second);
	}
	*/

    if (m_bIsUseRenderWindow == true)
    {
        m_renderWindow->Render();
    }
}

void BasicVisualizer::clearVisualizer()
{
	CleanDisplay();
	m_MapActors.clear();
	m_MapActors2D.clear();
	m_vIDInOrder.clear();
}
