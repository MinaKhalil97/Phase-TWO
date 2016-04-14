#include "Component.h"

Component::Component(const GraphicsInfo &r_GfxInfo )
{
	m_GfxInfo = r_GfxInfo;	

}

GraphicsInfo Component::Get()
{
	return m_GfxInfo;
}

bool Component::isGate()
{
	return IsGate;
}

Component::Component()
{}

Component::~Component()
{}

