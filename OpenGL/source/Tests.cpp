#include "Tests.h"
#include "imgui/imgui.h"

namespace test
{
	TestMenu::TestMenu(Tests*& currentTest)
		: m_CurrentTest(currentTest)
	{
		
	}

	void TestMenu::OnImGuiRender()
	{
		for (auto& test : m_Tests)
		{
			if (ImGui::Button(test.first.c_str()))
				m_CurrentTest = test.second();
		}
	}
}