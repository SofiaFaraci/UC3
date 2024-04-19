/******************************************************************************
 *                                                                            *
 * Copyright (C) 2020 Fondazione Istituto Italiano di Tecnologia (IIT)        *
 * All Rights Reserved.                                                       *
 *                                                                            *
 ******************************************************************************/

#include <mutex>
#include <rclcpp/rclcpp.hpp>
#include <scheduler_interfaces/srv/update_poi.hpp>
#include <scheduler_interfaces/srv/reset.hpp>
#include <scheduler_interfaces/srv/get_current_poi.hpp>
#include <scheduler_interfaces/srv/update_action.hpp>
#include <scheduler_interfaces/srv/get_current_action.hpp>
#include <map>
#include "TourStorage.h"

class SchedulerComponent
{
public:
    SchedulerComponent() = default;

    bool start(int argc, char*argv[]);

    bool close();
    void spin();
    void UpdatePoi([[maybe_unused]] const std::shared_ptr<scheduler_interfaces::srv::UpdatePoi::Request> request,
                std::shared_ptr<scheduler_interfaces::srv::UpdatePoi::Response>      response);
    void GetCurrentPoi([[maybe_unused]] const std::shared_ptr<scheduler_interfaces::srv::GetCurrentPoi::Request> request,
                std::shared_ptr<scheduler_interfaces::srv::GetCurrentPoi::Response>      response);
    void Reset( [[maybe_unused]] const std::shared_ptr<scheduler_interfaces::srv::Reset::Request> request,
                std::shared_ptr<scheduler_interfaces::srv::Reset::Response>      response);
    void UpdateAction([[maybe_unused]] const std::shared_ptr<scheduler_interfaces::srv::UpdateAction::Request> request,
                std::shared_ptr<scheduler_interfaces::srv::UpdateAction::Response>      response);
    void GetCurrentAction([[maybe_unused]] const std::shared_ptr<scheduler_interfaces::srv::GetCurrentAction::Request> request,
                std::shared_ptr<scheduler_interfaces::srv::GetCurrentAction::Response>      response);

private:
    rclcpp::Node::SharedPtr m_node;
    rclcpp::Service<scheduler_interfaces::srv::UpdatePoi>::SharedPtr m_updatePoiService;
    rclcpp::Service<scheduler_interfaces::srv::GetCurrentPoi>::SharedPtr m_getCurrentPoiService;
    rclcpp::Service<scheduler_interfaces::srv::Reset>::SharedPtr m_resetService;
    rclcpp::Service<scheduler_interfaces::srv::UpdateAction>::SharedPtr m_updateActionService;
    rclcpp::Service<scheduler_interfaces::srv::GetCurrentAction>::SharedPtr m_getCurrentActionService;

    std::mutex m_mutex;
    int32_t m_currentPoi{0};
    int32_t m_currentAction{0};
    std::shared_ptr<TourStorage> m_tourStorage;
};
