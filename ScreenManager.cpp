#include "ScreenManager.hpp"

float ScreenManager::calcRelativeByX( const float &value ) const
{
	return wnd.getSize().x * value;
};

float ScreenManager::calcRelativeByY( const float &value ) const
{
	return wnd.getSize().y * value;
};

float ScreenManager::getPxMenuVMargin()
{
	return menuVMargin * wnd.getSize().y;
};