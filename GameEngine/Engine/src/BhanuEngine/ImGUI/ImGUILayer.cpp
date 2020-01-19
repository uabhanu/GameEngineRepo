#include "EnginePCH.h"
#include "ImGUILayer.h"

#include <imgui.h>
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>
//Temporary 
#include <glad/glad.h>
#include <GLFW/glfw3.h> //Don't change this order

#include "BhanuEngine/BhanuEngineApp.h" //Don't change this order

namespace BhanuEngine
{
	ImGUILayer::ImGUILayer()
		: Layer("ImGUILayer")
	{
	}

	ImGUILayer::~ImGUILayer()
	{
	}

	void ImGUILayer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGUILayer::End()
	{
		ImGuiIO& io = ImGui::GetIO();
		BhanuEngineApp& engineApp = BhanuEngineApp::Get();
		io.DisplaySize = ImVec2(engineApp.GetWindow().GetWidth() , engineApp.GetWindow().GetHeight());

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	void ImGUILayer::OnAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;

		ImGui::StyleColorsDark(); //Classic & Light Colours are other available options

		ImGuiStyle& style = ImGui::GetStyle();

		if(io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		BhanuEngineApp& engineApp = BhanuEngineApp::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(engineApp.GetWindow().GetNativeWindow());

		ImGui_ImplGlfw_InitForOpenGL(window , true);
		ImGui_ImplOpenGL3_Init("#version 440"); //If any issue, try 410 instead

	}

	void ImGUILayer::OnDetach()
	{
		ImGui_ImplGlfw_Shutdown();
		ImGui_ImplOpenGL3_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGUILayer::OnImGUIRender()
	{
		static bool show = true;
		ImGui::ShowDemoWindow(&show);
	}
}