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
#include "Main.h"
#include <cstdlib>
#include <memory>
#include <unistd.h>

#include "hiaiengine/api.h"
#include "hiaiengine/data_type_reg.h"
#include "tool_api.h"
#include "data_type.h"
#include "error_code.h"
#include "tensor.h"
#include "sample_data.h"
const  cv::Scalar kFontColor(0, 0, 255);

int CustomDataRecvInterface::flag =1;
std::mutex  CustomDataRecvInterface::mt;
//std::shared_ptr<hiai::Graph> CustomDataRecvInterface::m_graph= nullptr;
// register custom data
HIAI_REGISTER_DATA_TYPE("ConsoleParams", ConsoleParams);


HIAI_StatusT CustomDataRecvInterface::RecvData(
    const std::shared_ptr<void>& message) {
    mt.lock();
    MAKE_SHARED_NO_THROW(m_box_result, BBOX);
    m_box_result=static_pointer_cast<BBOX>(message);
    flag--;
    mt.unlock();
    return HIAI_OK;
}

HIAI_StatusT CustomDataRecvInterface::GetData(std::vector<Bbox> &box_result) {
        box_result=m_box_result->bbox;
        return box_result.size()==0?-1:0;
}

void CustomDataRecvInterface::SetConsoleParams(shared_ptr<ConsoleParams> &param_ptr,Input_param &input_params) {
  // no need to check anything, python script already checked
  // and parameters all fixed position
  param_ptr->model_width  = input_params.model_width;
  param_ptr->model_height = input_params.model_height;
  param_ptr->input_path  = input_params.image_path;
  param_ptr->output_path = input_params.save_path;
  param_ptr->yolov3_cfg_params =input_params.yolov3_cfg_params;
  //cout<<"set config end!\n";
}

HIAI_StatusT CustomDataRecvInterface::SetGrgument(hiai::EnginePortID &engine_id, Input_param &input_params) {
    shared_ptr<ConsoleParams> param_ptr = nullptr;
    MAKE_SHARED_NO_THROW(param_ptr, ConsoleParams);
    if (param_ptr == nullptr) {
        ERROR_LOG("Failed to send data. Reason: new data failed.");
        return kOtherError;
    }
    //设置命令行参数
    SetConsoleParams(param_ptr,input_params);
    //开始将输入的命令行参数传递到预处理中
    //  printf("start to trans input cmd arguments!\n");
    if(m_graph== nullptr){
        ERROR_LOG("Failed to send data. Reason: new data failed.");
        return kOtherError;
    }
    m_graph->SendData(engine_id, "ConsoleParams",
                      static_pointer_cast<void>(param_ptr));
//等待结束
    for (;;) {
        // finished, break
        if (flag <= 0) {
            break;
        } else {
            usleep(kSleepInterval);
        }
    }
    flag=1;//标志位同步，需要等待数据同步
    return HIAI_OK;

}
HIAI_StatusT CustomDataRecvInterface::SetCallBack(std::shared_ptr<CustomDataRecvInterface> &customDataRecvInterface)
{
    //设置Engine数据传输
    m_graph= hiai::Graph::GetInstance(kGraphId);
    if (m_graph == nullptr) {
        ERROR_LOG("Failed to get the graph-%u.", kGraphId);
        return kGetGraphInstanceFailed;
    }
    hiai::EnginePortID target_port_config;
    target_port_config.graph_id = kGraphId;
    target_port_config.engine_id = kPostEngineId;
    target_port_config.port_id = 0;
//  CustomDataRecvInterface::m_this =std::make_shared(CustomDataRecvInterface);
//  MAKE_SHARED_NO_THROW(CustomDataRecvInterface::m_this, CustomDataRecvInterface);
    //设置回调函数传接收推理后的结果
    int status = m_graph->SetDataRecvFunctor(
            target_port_config,
            customDataRecvInterface);
    if (status != HIAI_OK) {
        ERROR_LOG("Failed to set callback function.");
        return kSetCallbackFunctionError;
    }
    return HIAI_OK;
}

HIAI_StatusT CustomDataRecvInterface::Init_Atlas200dk() {
    // Step1: Global System Initialization before using HIAI Engine
    HIAI_StatusT status = HIAI_Init(kDeviceId);
    if (status != HIAI_OK) {
        ERROR_LOG("Failed to call HIAI_Init, ret=%d.", status);
        return kHiaiInitFailed;
    }

    // Step2: Create and Start the Graph
    status = hiai::Graph::CreateGraph(kGraphConfigFilePath);
    if (status != HIAI_OK) {
        ERROR_LOG("Failed to start graph, ret=%d.", status);
        return kCreateGraphFailed;
    }
    return status;
}

HIAI_StatusT CustomDataRecvInterface::Destory() {

    // destroy graph
   // printf("hiai::Graph::DestroyGraph(kGraphId)!\n");
    return hiai::Graph::DestroyGraph(kGraphId);
}

Atlasdk_process::Atlasdk_process() {
    m_custom = nullptr;
    MAKE_SHARED_NO_THROW(m_custom, CustomDataRecvInterface);
}


