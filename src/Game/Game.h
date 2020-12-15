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
	
	inline static glm::ivec2 m_BoardSize;

	inline static Desk* desk;
	inline static Figure* figures_black[9];
	inline static Figure* figures_white[9];
	inline static glm::ivec2 black_home[9];
	inline static glm::ivec2 white_home[9];

	class AI final
	{
	public:
		void CollectMoves();
		void CollectMoves(std::function<Node* ()> Debut);
		void Go();

		int General_cost = 0;
		int move_mask_simple[3] = { 0, 0, 0 };
		int move_mask_simple_jump[3] = { 1 || 2, 0, 0 };
		int move_mask_block[3] = { 0, 1, 0 || 1 || 2 };
		int move_mask_jump_block[3] = { 1 || 2, 0, 1 || 2 };
		Node* Debut;
		Node* root;
	private:
		/*std::map<Figure*, Move*> Debut;*/
		
		std::map<Figure*, Move*> um_moves;
	};

	inline static AI ai;

	static enum class EGameFase
	{
		Debut,
		Begin,
		Mid,
		End
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