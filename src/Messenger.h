#pragma once

#include <functional>
#include <list>

namespace API
{
	class Messenger
	{
	public:
		static void AddListener(std::function<void()> update)
		{
			updates.push_back(update);
		}

		static void RemoveListener(std::function<void()> update)
		{
			
			//for (auto same : updates)
			//{
			//	if (same == update)
			//	{

			//	}
			//}
		}

		static std::function<void()> GetFrontListener()
		{
			return updates.front();
		}

		static std::list<std::function<void()>> GetUpdates()
		{
			return updates;
		}
	private:
		static std::list<std::function<void()>> updates;
	};
}