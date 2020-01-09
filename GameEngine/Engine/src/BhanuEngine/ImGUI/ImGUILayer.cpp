#include "EnginePCH.h"
#include "ImGUILayer.h"
#include "Platform/OpenGL/ImGUIOpenGLRenderer.h"

//Temporary according to Cherno but not sure if I can remove GLFW/glfw3.h at all as it's giving me errors
//Don't change this order
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>

namespace BhanuEngine
{
	ImGUILayer::ImGUILayer()
		: Layer("ImGUI Layer")
	{
	}

	ImGUILayer::~ImGUILayer()
	{

	}

	void ImGUILayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark(); //Other options are StyleColorsClassic, etc.

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		// This is temporary until we use BhanuEngine Key Codes
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

		ImGui_ImplOpenGL3_Init("#version 410");

	}

	void ImGUILayer::OnDetach()
	{

	}

	void ImGUILayer::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);

		dispatcher.Dispatch<KeyPressedEvent>(ENGINE_BIND_EVENT(ImGUILayer::OnKeyPressedEvent));
		dispatcher.Dispatch<KeyReleasedEvent>(ENGINE_BIND_EVENT(ImGUILayer::OnKeyReleasedEvent));
		dispatcher.Dispatch<KeyTypedEvent>(ENGINE_BIND_EVENT(ImGUILayer::OnKeyTypedEvent));
		dispatcher.Dispatch<MouseButtonPressedEvent>(ENGINE_BIND_EVENT(ImGUILayer::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(ENGINE_BIND_EVENT(ImGUILayer::OnMouseButtonReleasedEvent));
		dispatcher.Dispatch<MouseMovedEvent>(ENGINE_BIND_EVENT(ImGUILayer::OnMouseMovedEvent));
		dispatcher.Dispatch<MouseScrolledEvent>(ENGINE_BIND_EVENT(ImGUILayer::OnMouseScrolledEvent));
		dispatcher.Dispatch<WindowResizeEvent>(ENGINE_BIND_EVENT(ImGUILayer::OnWindowResizeEvent));
	}

	bool ImGUILayer::OnKeyPressedEvent(KeyPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();

		io.KeysDown[e.GetKeyCode()] = true;
		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER]; //This is Windows Button, Mac Button, etc.

		return false;
	}

	bool ImGUILayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = false;
		return false;
	}

	bool ImGUILayer::OnKeyTypedEvent(KeyTypedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();

		int keycode = e.GetKeyCode();

		if(keycode > 0 && keycode < 0x10000)
			io.AddInputCharacter((unsigned short)keycode);

		return false;
	}

	bool ImGUILayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = true;
		return false;
	}

	bool ImGUILayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = false;
		return false;
	}

	bool ImGUILayer::OnMouseMovedEvent(MouseMovedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.GetX() , e.GetY());
		return false;
	}

	bool ImGUILayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += e.GetXOffset();
		io.MouseWheel += e.GetYOffset();
		return false;
	}

	bool ImGUILayer::OnWindowResizeEvent(WindowResizeEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(e.GetWidth() , e.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f , 1.0f);
		glViewport(0 , 0 , e.GetWidth() , e.GetHeight());
		return false;
	}

	void ImGUILayer::OnUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();
		BhanuEngineApp& app = BhanuEngineApp::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth() , app.GetWindow().GetHeight());

		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}
