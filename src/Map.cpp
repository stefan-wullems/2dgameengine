#include <fstream>

#include "./Map.h"
#include "./Game.h"
#include "./EntityManager.h"

#include "./Components/TileComponent.h"

extern EntityManager manager;

Map::Map(std::string textureId, int scale, int tileSize) {
  this->textureId = textureId;
  this->scale = scale;
  this->tileSize = tileSize;
}

void Map::LoadMap(std::string fileName, int tileAmountX, int tileAmountY) {
  std::fstream file;
  file.open(fileName);

  for(int y = 0; y < tileAmountY; y++) {
    for(int x = 0; x < tileAmountX; x++) {
      char ch;
      file.get(ch);
      int sourceY = atoi(&ch) * this->tileSize;
      file.get(ch);
      int sourceX = atoi(&ch) * this->tileSize;
      this->AddTile(sourceX, sourceY , x * this->scale * this->tileSize, y * this->scale * this->tileSize);
      file.ignore();
    }
  }

  file.close();
}

void Map::AddTile(int sourceX, int sourceY, int posX, int posY) {
  Entity& tile = manager.AddEntity("tile");
  tile.AddComponent<TileComponent>(sourceX, sourceY, posX, posY, this->tileSize, this->scale, this->textureId);
}