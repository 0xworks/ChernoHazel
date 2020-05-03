#pragma once

#include "Hazel/ECS/ECSType.h"

#include <set>

namespace Hazel {

	namespace ECS {

		class System {
			friend class SystemManager;
		protected:
			std::set<Entity> m_Entities;
		};

	}
}
