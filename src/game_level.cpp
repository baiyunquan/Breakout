#include "game_level.h"

#include <fstream>
#include <sstream>

void GameLevel::Load(const char* file, unsigned int levelWidth, unsigned int levelHeight)
{
	// clear old bricks
	this->Bricks.clear();
	// load from file
	unsigned int tileCode;
	GameLevel level;
	std::string line;
	std::ifstream fstream(file);
	std::vector<std::vector<unsigned int>> tileData;

	if (fstream) {
		while (std::getline(fstream, line)) {
			std::istringstream sstream(line);
			std::vector<unsigned int> row;

			while (sstream >> tileCode)
				row.push_back(tileCode);
			tileData.push_back(row);
		}
		if (tileData.size() > 0) {
			this->init(tileData, levelWidth, levelHeight);
		}
	}
}

void GameLevel::init(std::vector<std::vector<GLuint>> tileData, GLuint lvlWidth, GLuint lvlHeight)
{
	unsigned int height = tileData.size();
	unsigned int width = tileData[0].size();

	// size of each block
	float unit_height = lvlHeight / static_cast<float>(height);
	float unit_width = lvlWidth / static_cast<float>(width);
	glm::vec2 size(unit_width, unit_height);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			glm::vec2 pos(unit_width * x, unit_height * y);

			if (tileData[y][x] == 1) {
				// solid block

				GameObject obj(pos, size,
					ResourceManager::GetTexture("block_solid"),
					glm::vec3(0.8f, 0.8f, 0.7f)
				);
				obj.IsSolid = GL_TRUE;
				this->Bricks.push_back(obj);
			}
			else {
				// liquid block with various color

				glm::vec3 color = glm::vec3(1.0f);
				switch (tileData[y][x]) {
				case 2:
					color = glm::vec3(0.2f, 0.6f, 1.0f);
					break;
				case 3:
					color = glm::vec3(0.0f, 0.7f, 0.0f);
					break;
				case 4:
					color = glm::vec3(0.8f, 0.8f, 0.4f);
					break;
				case 5:
					color = glm::vec3(1.0f, 0.5f, 0.0f);
					break;
				default:
					continue;
					break;
				}
				this->Bricks.push_back(
					GameObject(pos, size, ResourceManager::GetTexture("block"), color)
				);
			}
		}
	}

}

void GameLevel::Draw(SpriteRenderer& renderer) {
	for (auto& brick : this->Bricks) {
		if (!brick.Destroyed) {
			brick.Draw(renderer);
		}
	}
}

bool GameLevel::IsCompleted() {
	for (auto& brick : this->Bricks) {
		if (!brick.IsSolid &&!brick.Destroyed) {
			return false;
		}
	}
	return true;
}