# pragma once

#include <mutex>
#include <thread>
#include <rclcpp/rclcpp.hpp>
#include "SetPoi1SkillSM.h"
#include <bt_interfaces_dummy/msg/action_response.hpp>
#include <scheduler_interfaces_dummy/srv/set_poi.hpp> 



#include <bt_interfaces_dummy/srv/tick_action.hpp>



#define SERVICE_TIMEOUT 8

enum class Status{
	undefined,
	success,
	failure
};

class SetPoi1Skill
{
public:
	SetPoi1Skill(std::string name );
	bool start(int argc, char * argv[]);
	static void spin(std::shared_ptr<rclcpp::Node> node);
	
	void tick( [[maybe_unused]] const std::shared_ptr<bt_interfaces_dummy::srv::TickAction::Request> request,
			   std::shared_ptr<bt_interfaces_dummy::srv::TickAction::Response>      response);
	
	
	

private:
	std::shared_ptr<std::thread> m_threadSpin;
	std::shared_ptr<rclcpp::Node> m_node;
	std::mutex m_requestMutex;
	std::string m_name;
	SetPoi1SkillAction m_stateMachine;
	std::atomic<Status> m_tickResult{Status::undefined};
	rclcpp::Service<bt_interfaces_dummy::srv::TickAction>::SharedPtr m_tickService;
	
	
	
	
	
};

