#include "Tileset.h"

Tileset::Tileset(int tile_width, int tile_height, int spacing, int tile_count, int column)
{
	this->tile_width = tile_width;
	this->tile_height = tile_height;
	this->spacing = spacing;
	this->tile_count = tile_count;
	this->column = column;
}

Tileset::~Tileset()
{

}

void Tileset::Get(int& tile_width, int& tile_height, int& spacing, int& tile_count, int& column)
{
	tile_width = this->tile_width;
	tile_height = this->tile_height;
	spacing = this->spacing;
	tile_count = this->tile_count;
	column = this->column;
}