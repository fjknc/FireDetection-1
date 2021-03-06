/*
 * Author: Emoy Kim
 * E-mail: emoy.kim_AT_gmail.com
 * 
 * This code is a free software; it can be freely used, changed and redistributed.
 * If you use any version of the code, please reference the code.
 * 
 */

#pragma once

#include "TrainedColorFireDetection.h"
#include "RChannelFireDetection.h"
#include "CovarianceFireDetection.h"
#include "FlowRateFireDetection.h"

class UnitedFireDetection
{
   Mat ProcessResult;
   Mat Background;

   unique_ptr<TrainedColorFireDetection> TrainedColorBasedDetector;
   unique_ptr<RChannelFireDetection> RedChannelBasedDetector;
   unique_ptr<CovarianceFireDetection> CovarianceBasedDetector;
   unique_ptr<FlowRateFireDetection> FlowRateBasedDetector;
   
   void balanceColor(Mat& balanced_frame, const Mat& frame) const;
   void extractForeground(Mat& foreground, const Mat& frame);
   void extractFireColorPixelsOnly(Mat& fire_color_region, const Mat& frame, const Mat& mask) const;
   void extractFireColorRegion(vector<Rect>& fires, Mat& fire_color_region, const Mat& frame);
   void transformOriginalFirePosition(vector<Rect>& fires) const;
   void drawAllCandidates(const vector<Rect>& fires, const Scalar& box_color, const int& extended_size);
   void setFireRegion(Mat& fire_region, const vector<Rect>& fires) const;
   void findIntersection(vector<Rect>& intersection, const vector<vector<Rect>>& sets) const;


public:
   UnitedFireDetection(const UnitedFireDetection&) = delete;
   UnitedFireDetection(const UnitedFireDetection&&) = delete;
   UnitedFireDetection& operator=(const UnitedFireDetection&) = delete;
   UnitedFireDetection& operator=(const UnitedFireDetection&&) = delete;

   UnitedFireDetection(const uint& max_fire_num_to_find);
   ~UnitedFireDetection() = default;

   void detectFire(vector<Rect>& fires, const Mat& frame);
   void informOfSceneChanged() const;
};