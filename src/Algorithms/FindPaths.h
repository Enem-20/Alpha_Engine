#pragma once

#include <string>
#include <queue>

class FindPaths
{
public:
	FindPaths() = delete;
	FindPaths(FindPaths&&) = delete;
	FindPaths(const FindPaths&) = delete;
	FindPaths& operator=(FindPaths&&) = delete;

	char& FindStart(std::string graph, char start)
	{
		int length = graph.length();
		int iter = 0;
		char result = '0';

		while ((graph[iter] != start) && (iter != length - 1))
		{
			++iter;
		}

		return graph[iter];
	}

	FindPaths(std::string graph, char start)
	{
		start = FindStart(graph, start);

		std::queue<char> q;
		bool* visited = new bool[graph.length()];

		q.push(start);
		
		if()
	}
};