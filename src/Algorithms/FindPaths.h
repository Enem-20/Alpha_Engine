#pragma once

#define line_minus line - 1 > -1
#define line_plus line + 1 < 8
#define column_minus column - 1 > -1
#define column_plus column + 1 < 8

#include <glad/glad.h>
#include <glm/vec2.hpp>
#include "../Renderer/Sprite.h"

#include <string>
#include <queue>
#include <unordered_map>
#include <memory>
#include "../Resources/ResourceManager.h"

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

	FindPaths(std::shared_ptr<Renderer::Sprite> allowed_cell)
		:allowed_cell(allowed_cell)
	{
		GLfloat vertexCoords[] =
		{
			//x  y
			0.f, 0.f,
			0.f, 1.f,
			1.f, 1.f,

			1.f, 1.f,
			1.f, 0.f,
			0.f, 0.f
		};

		graph = new char* [8];
		visited = new bool* [8];

		for (int i = 0; i < 8; ++i)
		{
			graph[i] = new char[8];
		}

		visited = new bool* [8];

		for (int i = 0; i < 8; ++i)
		{
			visited[i] = new bool[8];
		}


		glGenVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		glGenBuffers(1, &m_vertexCoordsVBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexCoordsVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexCoords), &vertexCoords, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	~FindPaths()
	{
		glDeleteBuffers(1, &m_vertexCoordsVBO);
		glDeleteVertexArrays(1, &m_VAO);
	}

	void FindPath_king(int line, int column)
	{
		std::queue<char> q;
		
		q.push(graph[line][column]);
		q.emplace(Find_cross(line, column));
		q.emplace(Find_diagonal(line, column));

		memset(visited, 0, 8 * sizeof(*visited));
	}

	std::queue<char> Find_cross(int line, int column)
	{
		std::queue<char> q;

		if (line - 1 > -1 && graph[line - 1][column] != 'O' && !visited[line - 1][column])
		{
			visited[line - 1][column] = true;
			q.push(graph[line - 1][column]);
		}
		if (line + 1 < 8 && graph[line + 1][column] != 'O' && !visited[line + 1][column])
		{
			visited[line + 1][column] = true;
			q.push(graph[line + 1][column]);
		}
		if (column - 1 > -1 && graph[line][column - 1] != 'O' && !visited[line][column - 1])
		{
			visited[line][column - 1] = true;
			q.push(graph[line][column - 1]);
		}
		if (column + 1 < 8 && graph[line][column + 1] != 'O' && !visited[line][column + 1])
		{
			visited[line][column + 1] = true;
			q.push(graph[line][column + 1]);
		}

		return q;
	}
	std::queue<char> Find_diagonal(int line, int column)
	{
		std::queue<char> q;

		if (line_minus && column_minus && graph[line - 1][column - 1] != 'O' && !visited[line - 1][column - 1])
		{
			visited[line - 1][column - 1] = true;
			q.push(graph[line - 1][column - 1]);
		}
		if (line_minus && column_plus && graph[line - 1][column + 1] != 'O' && !visited[line - 1][column + 1])
		{
			visited[line - 1][column + 1] = true;
			q.push(graph[line - 1][column + 1]);
		}
		if (line_plus && line_minus && graph[line + 1][column - 1] != 'O' && !visited[line + 1][column - 1])
		{
			visited[line + 1][column - 1] = true;
			q.push(graph[line + 1][column - 1]);
		}
		if (line_plus && line_plus && graph[line + 1][column + 1] != 'O' && !visited[line + 1][column + 1])
		{
			visited[line + 1][column + 1] = true;
			q.push(graph[line + 1][column + 1]);
		}

		return q;
	}

private:
	char** graph;
	bool** visited;
	char start;

	GLuint m_VAO;
	GLuint m_vertexCoordsVBO;
	std::shared_ptr<Renderer::Sprite> allowed_cell;
};