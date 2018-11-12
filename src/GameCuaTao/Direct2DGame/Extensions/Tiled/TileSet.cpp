#include "TileSet.h"

TileSet::TileSet(std::shared_ptr<Texture> texture, int tileWidth, int tileHeight, int rows, int columns)
{
	this->texture = texture;
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;

	for (auto row = 0; row < rows; row++)
	{
		for (auto column = 0; column < columns; column++)
		{
			auto rect = Rect{
				tileWidth * row,
				tileHeight * column,
				tileWidth,
				tileHeight,
			};

			auto textureRegion = TextureRegion{ texture, rect };
			tiles.emplace(std::make_pair(row, column), Tile{ textureRegion });
		}
	}
}

Tile &TileSet::GetTile(int row, int column)
{
	return tiles.at(std::make_pair(row, column));
}