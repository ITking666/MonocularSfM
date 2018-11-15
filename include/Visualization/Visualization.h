#ifndef VISUALIZATION_H
#define VISUALIZATION_H


#include <iostream>
#include <vector>
#include <unordered_map>
#include <thread>
#include <mutex>

#include <opencv2/opencv.hpp>

#include "Reconstruction/Image.h"
#include "Reconstruction/MapPoint.h"




namespace MonocularSfM
{
/**
 *
 * 实现原理：
 * AsyncVisualization的ShowPointCloud和ShowCameras的做法是将传入的数据复制到自己的成员上。
 * 所以不会存在数据竞争问题
 *
 *
 * 用法：
 * AsyncVisualization async_visualization;
 * async_visualization.RunVisualizationThread();
 *
 * do something ...
 * async_visualization.ShowPointCloud(...);
 * async_visualization.ShowCameras(...);
 *
 * async_visualization.WaitForVisualizationThread();
 *
 */
class AsyncVisualization
{
public:
    AsyncVisualization();

    void RunVisualizationThread();
    void WaitForVisualizationThread();
    void RunVisualizationOnly();

    void ShowPointCloud(std::vector<cv::Point3f>& point_cloud,
                        std::vector<cv::Vec3b>& colors);

    void ShowPointCloud(const std::unordered_map<image_t, Image>& images,
                        const std::unordered_map<point3D_t, MapPoint>& map_points,
                        std::unordered_map<point3D_t, Color>& map_points_color);

    void ShowCameras(std::vector<cv::Mat>& Rs,
                     std::vector<cv::Mat>& ts);
    void ShowCameras(const std::unordered_map<image_t, Image>& images,
                     const std::unordered_map<image_t, bool> registered);

private:
    std::vector<cv::Point3f> point_cloud_ ;
    std::vector<cv::Vec3b> colors_;
    size_t point_cloud_change_count_ = 0;

    std::vector<cv::Mat> Rs_;
    std::vector<cv::Mat> ts_;

    size_t camera_count_ = 0;

    bool is_camera_update_ = false;
    bool is_point_cloud_update_ = false;

    std::thread* thread_ = nullptr;
};



} // namespace Undefine

#endif // VISUALIZATION_H
