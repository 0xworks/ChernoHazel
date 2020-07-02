#include <Hazel.h>
#include <Hazel/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Hazel {

	class Hazelnut : public Application
	{
	public:
		Hazelnut()
			: Application(WindowProps{"Hazelnut"})
		{
			PushLayer(new EditorLayer());
		}

		~Hazelnut() = default;
	};

	Application* CreateApplication()
	{
		return new Hazelnut();
	}

}
