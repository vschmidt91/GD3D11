#include "pch.h"
#include "BaseGraphicsEngine.h"


BaseGraphicsEngine::BaseGraphicsEngine() {}


BaseGraphicsEngine::~BaseGraphicsEngine() {}

void BaseGraphicsEngine::DrawString( std::string str, float x, float y, _zCView* view ) {}

int BaseGraphicsEngine::MeasureString( const std::string& str, int font ) {
	return 0;
}
