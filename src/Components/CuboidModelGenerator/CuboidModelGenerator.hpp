/*!
 * \file
 * \brief 
 * \author Michal Laszkowski
 */

#ifndef CUBOIDMODELGENERATOR_HPP_
#define CUBOIDMODELGENERATOR_HPP_

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "DataStream.hpp"
#include "Property.hpp"
#include "EventHandler2.hpp"

#include "Types/Features.hpp"

#include <opencv2/opencv.hpp>

#if CV_MAJOR_VERSION == 2
#if CV_MINOR_VERSION > 3
#include <opencv2/nonfree/features2d.hpp>
#endif
#elif CV_MAJOR_VERSION == 3
#include <opencv2/nonfree/features2d.hpp>
#endif


#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <Types/PointXYZSIFT.hpp>

namespace Processors {
namespace CuboidModelGenerator {

using namespace cv;

/*!
 * \class CuboidModelGenerator
 * \brief CuboidModelGenerator processor class.
 *
 * 
 */
class CuboidModelGenerator: public Base::Component{
public:
	/*!
	 * Constructor.
	 */
	CuboidModelGenerator(const std::string & name = "CuboidModelGenerator");

	/*!
	 * Destructor
	 */
	virtual ~CuboidModelGenerator();

	/*!
	 * Prepare components interface (register streams and handlers).
	 * At this point, all properties are already initialized and loaded to 
	 * values set in config file.
	 */
	void prepareInterface();

protected:

	/*!
	 * Connects source to given device.
	 */
	bool onInit();

	/*!
	 * Disconnect source from device, closes streams, etc.
	 */
	bool onFinish();

	/*!
	 * Start component
	 */
	bool onStart();

	/*!
	 * Stop component
	 */
	bool onStop();

    void loadData();
    void sift(cv::Mat input, cv::Mat &descriptors, Types::Features &features);


	// Input data streams

	// Output data streams
	Base::DataStreamOut<pcl::PointCloud<pcl::PointXYZRGB>::Ptr> out_cloud_xyzrgb;
    Base::DataStreamOut<pcl::PointCloud<PointXYZSIFT>::Ptr> out_cloud_xyzsift;

    // Handlers
    /// Generates model on the basis of cuboid model and textures loaded from files.
    Base::EventHandler2 h_generateModel;

    /// Handler returning model.
    Base::EventHandler2 h_returnModel;

    /// JSON file containing geometric properties of the cuboid and list of files with textures.
	Base::Property<std::string> dataJSONname;

    Base::Property<bool> generate_on_init;

    Base::Property<int> resolution;

    /// Function responsible for generation of SOM cuboid model.
    void generateModel();

    /// Function setting the generateModel flag.
    void generateModelPressed();

    /// Function responsible for cyclic return of SOM cuboid model.
    void returnModel();

    /// Image with left side texture.
    cv::Mat left;
    /// Image with right side texture.
    cv::Mat right;
    /// Image with top side texture.
    cv::Mat top;
    /// Image with bottom side texture.
    cv::Mat bottom;
    /// Image with front side texture.
    cv::Mat front;
    /// Image with back side texture.
    cv::Mat back;
    /// Image with left side mask.
    cv::Mat left_mask;
    /// Image with right side mask.
    cv::Mat right_mask;
    /// Image with top side mask.
    cv::Mat top_mask;
    /// Image with bottom side mask.
    cv::Mat bottom_mask;
    /// Image with front side mask.
    cv::Mat front_mask;
    /// Image with back side mask.
    cv::Mat back_mask;

    /// Sizes of the cuboid.
    int width,depth,height;

    /// Flag indicating that the user pressed the generateModelButton
    bool generateModel_flag;

    bool generate_top, generate_bottom, generate_left, generate_right, generate_front, generate_back;
    bool mask_top, mask_bottom, mask_left, mask_right, mask_front, mask_back;

    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_xyzrgb;
    pcl::PointCloud<PointXYZSIFT>::Ptr cloud_xyzsift;
};

} //: namespace CuboidModelGenerator
} //: namespace Processors

/*
 * Register processor component.
 */
REGISTER_COMPONENT("CuboidModelGenerator", Processors::CuboidModelGenerator::CuboidModelGenerator)

#endif /* CUBOIDMODELGENERATOR_HPP_ */
