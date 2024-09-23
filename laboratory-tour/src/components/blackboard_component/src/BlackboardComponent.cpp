/******************************************************************************
 *                                                                            *
 * Copyright (C) 2020 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/


#include "BlackboardComponent.h"

bool BlackboardComponent::start(int argc, char*argv[])
{

    if(!rclcpp::ok())
    {
        rclcpp::init(/*argc*/ argc, /*argv*/ argv);
    }
    m_node = rclcpp::Node::make_shared("BlackboardComponentNode");
    
    m_setIntService = m_node->create_service<blackboard_interfaces::srv::SetIntBlackboard>("/BlackboardComponent/SetInt",  
                                                                                std::bind(&BlackboardComponent::SetInt,
                                                                                this,
                                                                                std::placeholders::_1,
                                                                                std::placeholders::_2));
    m_getIntService = m_node->create_service<blackboard_interfaces::srv::GetIntBlackboard>("/BlackboardComponent/GetInt",  
                                                                                std::bind(&BlackboardComponent::GetInt,
                                                                                this,
                                                                                std::placeholders::_1,
                                                                                std::placeholders::_2));

    RCLCPP_DEBUG(m_node->get_logger(), "BlackboardComponent::start");
    std::cout << "BlackboardComponent::start" << std::endl;        
    return true;

}

bool BlackboardComponent::close()
{
    rclcpp::shutdown();  
    return true;
}

void BlackboardComponent::spin()
{
    rclcpp::spin(m_node);  
}


void BlackboardComponent::GetInt( const std::shared_ptr<blackboard_interfaces::srv::GetIntBlackboard::Request> request,
             std::shared_ptr<blackboard_interfaces::srv::GetIntBlackboard::Response>      response) 
{
    std::lock_guard<std::mutex> lock(m_mutexInt);
    int32_t value = request->field_name;
    std::string field_name = std::to_string(value);
    std::cout << "Request: " << request->field_name << "translation " << field_name << std::endl; 
    if (field_name == "") {
        response->is_ok = false;
        response->error_msg = "missing required field name";
    } else {
        if (!m_intBlacboard.contains(field_name)) {
            response->is_ok = false;
            response->error_msg = "field not found";
        } else {
            response->value = m_intBlacboard.find(field_name)->second; 
            std::cout << "GetInt: " << field_name << " " << response->value << std::endl; 
            response->is_ok = true;
        }
    }
}


void BlackboardComponent::SetInt( const std::shared_ptr<blackboard_interfaces::srv::SetIntBlackboard::Request> request,
             std::shared_ptr<blackboard_interfaces::srv::SetIntBlackboard::Response>      response) 
{
    std::lock_guard<std::mutex> lock(m_mutexInt);
    std::cout << "SetInt: " << std::endl;
    // std::string field_name = std::to_string(request->field_name);
    // std::cout << "Request: " << request->field_name << "translation " << field_name << std::endl; 
    // if (field_name == "") {
    //     response->is_ok = false;
    //     response->error_msg = "missing required field name";
    // } else {
    //     if (m_intBlacboard.contains(field_name)) {
    //         response->error_msg = "field already present, overwriting";
    //     } 
    //     m_intBlacboard.insert_or_assign(field_name, request->value); 
    //     std::cout << "SetInt: " << field_name << " " << request->value << std::endl; 
    //     response->is_ok = true;
    // }
    response->is_ok = true;

}
