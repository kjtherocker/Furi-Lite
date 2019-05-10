#include "GamePCH.h"

Tween::Tween(float startvalue, float valuerange, double timepassed, double totaltime, TweenTypes tweentype)
{
    m_StartValue = startvalue;
    m_ValueRange = valuerange;
    m_TimePassed = timepassed;
    m_TotalTime = totaltime;
    m_TweenType = tweentype;
    m_Return = 0;
}

Tween::Tween(float startvalue, float valuerange, double timepassed, double totaltime, float elasticity, TweenTypes tweentype)
{
    m_StartValue = startvalue;
    m_ValueRange = valuerange;
    m_TimePassed = timepassed;
    m_TotalTime = totaltime;
    m_Elasticity = elasticity;
    m_TweenType = tweentype;
    m_Return = 0;
}

Tween::~Tween()
{

}


void Tween::Update(float deltatime)
{
    if (m_TweenType == TweenTypeLinear)
    {
        m_Return = TweenFunc_Linear(m_StartValue, m_ValueRange, m_TimePassed, m_TotalTime);
    }
    if (m_TweenType == TweenTypeEaseIn)
    {
        m_Return = TweenFunc_ElasticEaseIn(m_StartValue, m_ValueRange, m_TimePassed, m_TotalTime);
    }
    if (m_TweenType == TweenTypeBounceIn)
    {
        m_Return = TweenFunc_BounceEaseIn(m_StartValue, m_ValueRange, m_TimePassed, m_TotalTime);
    }
}

float Tween::GetReturn()
{
    return m_Return;
}

void Tween::SetupTween(float startvalue, float valuerange, double timepassed, double totaltime, TweenTypes tweentype)
{
	m_StartValue = startvalue;
	m_ValueRange = valuerange;
	m_TimePassed = timepassed;
	m_TotalTime = totaltime;
	m_TweenType = tweentype;
}


