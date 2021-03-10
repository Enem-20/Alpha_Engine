#pragma once

#include "../Algorithms/Node.h"
#include "../Algorithms/FindPaths.h"
#include "GObject.h"
#include "Desk.h"
#include "AllowedCell.h"
#include "Figure.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include<glm/vec2.hpp>

#include<queue>
#include <list>
#include<array>
#include <memory>
#include <functional>
#include <map>

class Game final
{
public:
	Game();
	~Game();

	static bool init(const glm::ivec2& boardSize, const std::string& ExecutablePath);
	static void setBoardSize(const glm::ivec2 new_BoardSize);

	static glm::ivec2 Get_BoardSize();

	inline static GLFWwindow* MainWindow;
	inline static int** BoardGraph;
	inline static int** TargetGraph;
	inline static int** Zones;
	inline static bool** visited;
	struct KeyFuncs
	{
		size_t operator()(const glm::ivec2& k)const
		{
			return std::hash<int>()(k.x) ^ std::hash<int>()(k.y);
		}

		bool operator()(const glm::ivec2& a, const glm::ivec2& b)const
		{
			return a.x == b.x && a.y == b.y;
		}
	};
	inline static glm::ivec2 m_BoardSize;

	inline static Desk* desk;
	/*inline static Figure* figures_black[9];*/
	//inline static Figure* figures_white[9];
	inline static glm::ivec2 black_home[9];
	inline static glm::ivec2 white_home[9];
	inline static std::unordered_map<glm::ivec2, Figure*, KeyFuncs> figures_black;
	inline static std::unordered_map<glm::ivec2, Figure*, KeyFuncs> figures_white;
	inline static std::queue<std::pair<Figure*, Move*>> Debut;



	class AI final
	{
	public:
		//void CollectMoves();
		void CollectMoves(std::function<std::queue<std::pair<Figure*, Move*>> ()> Debut);
		void Deliver();
		void Embed();
		void Go();

		
		int General_cost = 0;
		std::list<Figure*> outside_layer;
		std::list<Figure*> delivery;
	private:
		//std::map<Figure*, Move*> Debut;
		
		//std::queue<std::pair<Figure*, Move*>> um_moves;
	};
	template<class T>
	class Shell_array
	{
	public:
		static T& Get(T** _array, glm::ivec2 coordinate)
		{
			return _array[coordinate.x][coordinate.y];
		}
	};
	typedef Game::Shell_array<int> shell_int;
	typedef Game::Shell_array<bool> shell_bool;
	inline static AI ai;

	static enum class EGameFase
	{
		Debut,
		Game
	};
	inline static EGameFase ECurrentGameFase;

	static enum class EGameFractionMove
	{
		White,
		Black
	};

	inline static EGameFractionMove ECurrentFractinMove;
	inline static size_t Moves_count_white;
	inline static size_t Moves_count_black;
};