/**
 * ============================================================================
 *
 * Copyright (C) 2018, Hisilicon Technologies Co., Ltd. All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   1 Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *
 *   2 Redistributions in binary form must reproduce the above copyright notice,
 *     this list of conditions and the following disclaimer in the documentation
 *     and/or other materials provided with the distribution.
 *
 *   3 Neither the names of the copyright holders nor the names of the
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 * ============================================================================
 */

#ifndef GENERAL_POST_GENERAL_POST_H_
#define GENERAL_POST_GENERAL_POST_H_

#include<vector>
#include "hiaiengine/engine.h"
#include "hiaiengine/data_type.h"
#include "data_type.h"
#include "hiaiengine/log.h"
#include "opencv2/opencv.hpp"
#include "opencv2/imgcodecs/legacy/constants_c.h"
#include "tool_api.h"
#define INPUT_SIZE 1
#define OUTPUT_SIZE 1
using namespace cv;
template <class T>
class Tensor {
  public:
    Tensor() : data_(nullptr) {}
    ~Tensor() { Clear(); }

    uint32_t Size() const {
      uint32_t size(1);
      for(auto& dim : dims_){
        size *= dim;
      }
      return size;
    }

    bool FromArray(const T* pdata, const std::vector<uint32_t>& shape){
      if(pdata == nullptr){
        return false;
      }
      Clear();
      uint32_t size(1);
      for(auto dim:shape){
        if(dim>0){
          size *= dim;
        }else{
          return false;
        }
      }
      data_ = new T[size];
      int ret = memcpy_s(data_, size * sizeof(T), pdata, size * sizeof(T));
      if(ret !=0){
        return false;
      }
      dims_ = shape;
      return true;
    }

    T& operator()(uint32_t i, ...) { 
      va_list arg_ptr;
      va_start(arg_ptr, i);
      uint32_t index = i;
      for (uint32_t idx = 1; idx < dims_.size();++idx){
        index *= dims_[idx];
        index += va_arg(arg_ptr, uint32_t);
      }
      va_end(arg_ptr);
      return data_[index];
    }

    T& operator[](unsigned int index) { return data_[index]; }
    const T& operator[](unsigned int index) const { return data_[index]; }

  private:
    void Clear(){
      if(data_ != nullptr){
        delete[] data_;
        data_ = nullptr;
      }
      dims_.clear();
    }
    std::vector<uint32_t> dims_; // tensor shape
    T* data_; //tensor data
};

/**
 * @brief: inference engine class
 */
class GeneralPost : public hiai::Engine {
public:
  /**
   * @brief: engine initialize
   * @param [in]: engine's parameters which configured in graph.config
   * @param [in]: model description
   * @return: HIAI_StatusT
   */
  HIAI_StatusT Init(const hiai::AIConfig& config,
                    const std::vector<hiai::AIModelDescription>& model_desc);
                    
  #define  sigmoid(x)  (1 / (1 + exp(-1*x)))

  /**
   * @brief: engine processor which override HIAI engine
   *         get every image, and then send data to inference engine
   * @param [in]: input size
   * @param [in]: output size
   */
  HIAI_DEFINE_PROCESS(INPUT_SIZE, OUTPUT_SIZE);

private:
    std::vector<Bbox_t> bbox;
    std::shared_ptr<BBOX_t> p_Bbox = nullptr;
  /**
   * @brief: send result
   * @return: true: success; false: failed
   */
  bool SendSentinel(std::shared_ptr<void>& arguement);

  /**
   * @brief: mark the oject based on detection result
   * @param [in]: result: engine transform image
   * @return: HIAI_StatusT
   */
  HIAI_StatusT PostProcess(
      const std::shared_ptr<EngineTrans> &result,std::vector<Bbox_t> &bbox);

  std::vector<BoundingBox>  decodeTensor(
      const std::shared_ptr<EngineTrans> &result, uint ImgW,uint Imgh);
      
  std::vector<BoundingBox> nonMaximumSuppression(const float nmsThresh, std::vector<BoundingBox> binfo);
  std::vector<BoundingBox> nmsAllClasses(const float nmsThresh, std::vector<BoundingBox>& binfo,
                                    const uint numClasses);

  void Setyolov3_param(const std::shared_ptr<EngineTrans> &result);
// callback port (engine port begin with 0)
    const uint32_t kSendDataPort = 0;

// sleep interval when queue full (unit:microseconds)
    const __useconds_t kSleepInterval = 5;

// size of output tensor vector should be 2.
    uint32_t kOutputTensorSize = 3;
    uint32_t kOutputNumIndex = 0;
    uint32_t kOutputTesnorIndex = 1;

    uint32_t kCategoryIndex = 2;
    uint32_t kScorePrecision = 3;

// bounding box line solid
    uint32_t kLineSolid = 2;

// output image prefix
    std::string kOutputFilePrefix = "out_";


// num tensor shape
    std::vector<uint32_t> kDimBBoxCnt = {32};
    std::vector<std::string> label ;
/*
const static std::vector<string> label = {"background", "person", "bicycle", "car", "motorbike",
 "aeroplane","bus", "train", "truck", "boat",
 "traffic light", "fire hydrant", "stop sign", "parking meter",
 "bench", "bird", "cat", "dog", "horse",
 "sheep", "cow", "elephant", "bear", "zebra",
 "giraffe", "backpack", "umbrella", "handbag","tie",
 "suitcase", "frisbee", "skis", "snowboard", "sports ball",
        "kite", "baseball bat", "baseball glove", "skateboard", "surfboard",
        "tennis racket", "bottle", "wine glass", "cup",
		"fork", "knife", "spoon", "bowl", "banana",
		"apple", "sandwich", "orange", "broccoli", "carrot",
		"hot dog", "pizza", "donut", "cake", "chair",
		"sofa", "potted plant", "bed", "dining table", "toilet",
		"TV monitor", "laptop", "mouse", "remote", "keyboard",
		"cell phone", "microwave", "oven", "toaster", "sink",
		"refrigerator", "book", "clock", "vase","scissors",
		"teddy bear", "hair drier", "toothbrush"};
*/
// opencv draw label params.
     double kFountScale = 0.5;

     uint32_t kLabelOffset = 11;

//const uint numClasses =
    uint numClasses = 1;
//const uint BoxTensorLabel  = 85;
    uint BoxTensorLabel  = 6;

    uint numBBoxes = 3;
    uint  BoxTensorLength ;
    float nmsThresh = 0.45;
    float MaxBoxClassThresh = 0.25;
    float MaxClassThresh = 0.6;


     std::string kFileSperator = "/";

// opencv color list for boundingbox
    vector<cv::Scalar> kColors {
            cv::Scalar(237, 149, 100), cv::Scalar(0, 215, 255), cv::Scalar(50, 205, 50),
            cv::Scalar(139, 85, 26)};
// output tensor index
    enum BBoxIndex {kTopLeftX, kTopLeftY, kLowerRigltX, kLowerRightY, kScore};
//const static std::vector<uint32_t>

    const  std::vector<uint32_t>  anchors = {116,90,156,198,373,326,30,61,62,45,59,119,10,13,16,30,33,23};
    const  std::vector<uint32_t>  kGridSize = {13,26,52};


};

#endif /* GENERAL_POST_GENERAL_POST_H_ */
