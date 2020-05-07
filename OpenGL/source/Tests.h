// Based on the Cherno Youtube opengl tutorial youtube channel
#pragma once
#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include "TestEventHandler.hpp"
#include "transform.h"
#include "camera.h"
//#include "imgui/imgui.h"

namespace test {
	class Tests
	{
	public:
		Tests(){}
		virtual ~Tests(){}
		virtual void OnUpdate(double& updateTime, bool& isRunning) {}
		virtual void OnRender(float updateTime){}
		virtual void OnImGuiRender(){}
		virtual void OnEventUpdate(TestEventHandler& e) {}
		virtual void UpdateTransform(Transform& t) {}
		virtual void UpdateCamera(Camera& c) {}
	};

	class TestMenu : public Tests
	{
	public:

		TestMenu(Tests*& currentTest);
		void OnImGuiRender() override;
		template <typename T>
		void AddTest(const std::string& name)
		{
			std::cout << "Adding Test to list" << std::endl;
			// use a lambda function to return the template T pased to the function
			// because we do not know the class that will be passed unitl compile time.
			// All the functions that are passed must have the same framework to call the functions accurately
			m_Tests.push_back(std::make_pair(name, []() {return new T(); }));
		}
	private:
		Tests*& m_CurrentTest;
		std::vector <std::pair<std::string, std::function<Tests* () >>> m_Tests;
	};
}