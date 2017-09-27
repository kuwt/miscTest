#pragma once
/**************************************************

A Very Basic VTK Visualizer

* If you do not plan to use Point Cloud Library(PCL), 
comment #define IS_USE_MY_PCL

*****************************************************/
//#define IS_USE_MY_PCL

#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkPolyDataAlgorithm.h>
#include <vtkMatrix4x4.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkDataSet.h>
#include <vtkLODActor.h>

#include <vtkLineSource.h>
#include <map>
#include <vector>


#ifdef IS_USE_MY_PCL
#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#endif

namespace VISUAL_RENDER_PROP
{
	/** \brief Set of rendering properties. */
	enum RenderProp
	{
		POINT_SIZE,            /**< integer starting from 1 */
		OPACITY,               /**< Float going from 0.0 (transparent) to 1.0 (opaque) */
		LINE_WIDTH,            /**< Integer starting from 1 */
		COLOR,                 /**< 3 floats (R, G, B) going from 0.0 (dark) to 1.0 (light) */
	};
}

struct TRANS_PARA
{
    // Rigid body has 6 degree of freedom
    float dx;
    float dy;
    float dz;
    float alpha;
    float beta;
    float gamma;
    float scale;


   TRANS_PARA:: TRANS_PARA() : dx(0), dy(0) , dz(0),  alpha(0),  beta(0), gamma(0), scale(1) {}
   TRANS_PARA:: TRANS_PARA(float dx, float dy, float dz, float alpha,float beta, float gamma , float scale ) :  dx(dx), dy(dy) , dz(dz), alpha(alpha),  beta(beta), gamma(gamma), scale(scale) {}
};

class BasicVisualizer
{
public:
	BasicVisualizer();
	~BasicVisualizer();

	void setPointCloudRenderingProperties(int RenderProperty,
		double value1,
		double value2,
		double value3,
		const std::string &id);

	void setPointCloudRenderingProperties(int RenderProperty,
		double value1,
		double value2,
		const std::string &id);

	void setPointCloudRenderingProperties(	int RenderProperty,
											double value,
											const std::string &id);

	void setBackgroundColor(double value1,
							double value2,
							double value3);

#ifdef IS_USE_MY_PCL
	
	void addPointCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr pCloud, const std::string &id);
	void addPointCloud(pcl::PointCloud<pcl::PointXYZRGBA>::Ptr pCloud, const std::string &id);

#endif
	void addPointCloud(vtkSmartPointer<vtkPolyDataAlgorithm> polydataAlg, const std::string &id);
	void addText(const std::string &text, const int locationX, const int locationY, float fontsize, double r, double g, double b, const std::string &id);
	/**********************************
	To use this template, 
	P1 and P2 needs to be a structure with members 
	x, y, z as numerical value
	***********************************/
	template <typename P1, typename P2> void
		addLine(const P1 &pt0, const P2 &pt1, double r, double g, double b, const std::string &id)
	{
        if (ActorsContains(id))
		{
			return;
		}

		double p0[3] = { pt0.x, pt0.y, pt0.z };
		double p1[3] = { pt1.x, pt1.y, pt1.z };

		vtkSmartPointer<vtkLineSource> lineSource = vtkSmartPointer<vtkLineSource>::New();
		lineSource->SetPoint1(p0);
		lineSource->SetPoint2(p1);
		lineSource->Update();

		vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
		mapper->SetInputConnection(lineSource->GetOutputPort());
		vtkSmartPointer<vtkActor> pActor = vtkSmartPointer<vtkActor>::New();
		pActor->SetMapper(mapper);
		pActor->GetProperty()->SetRepresentationToWireframe();
		pActor->GetProperty()->SetColor(r, g, b);
		m_MapActors[id] = pActor;

		vtkSmartPointer<vtkPolyDataAlgorithm> dummy = vtkSmartPointer<vtkPolyDataAlgorithm>::New();
		m_vIDInOrder.push_back(id);

	}

    void TransformObject(const TRANS_PARA &Trans, const std::string &id);
	void TransformObject(const vtkSmartPointer<vtkMatrix4x4> pMat, const std::string &id);
	void deleteObject(const std::string &id);

    vtkSmartPointer<vtkRenderer> GetRenderer();  // Use external render window
    void Render();  // Use Its own render window, if use external render window, never call this

	void CleanDisplay();
	void clearVisualizer();

private:
	void ConstructRenderer();

	bool ActorsContains(const std::string &id);
	bool Actors2DContains(const std::string &id);
	bool IDInOrderContains(const std::string &id);

	vtkSmartPointer<vtkRenderer> m_pRenderer;
	vtkSmartPointer<vtkRenderWindow> m_renderWindow;
	vtkSmartPointer<vtkRenderWindowInteractor> m_renderWindowInteractor;

	bool m_bIsUseRenderWindow;
	std::vector<std::string>  m_vIDInOrder;
	std::map<std::string, vtkSmartPointer<vtkActor>>  m_MapActors;
	std::map<std::string, vtkSmartPointer<vtkActor2D>> m_MapActors2D;

	float m_BackgroundColor[3] = {0,0,0};
};

