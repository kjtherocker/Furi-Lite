#pragma once
class TweenFuncs;

enum TweenTypes
{
    TweenTypeUndefined,
    TweenTypeLinear,
    TweenTypeEaseIn,
    TweenTypeBounceIn,
};

class Tween 
{

protected:
    float m_StartValue;
    float m_ValueRange;
    double m_TimePassed;
    double m_TotalTime;
    float m_Elasticity;
    float m_Return;
    TweenTypes m_TweenType;
    
public:
    Tween(float startvalue, float valuerange, double timepassed, double totaltime, TweenTypes tweentype);
    Tween(float startvalue, float valuerange, double timepassed, double totaltime, float elasticity, TweenTypes tweentype);
    ~Tween();

	void SetupTween(float startvalue, float valuerange, double timepassed, double totaltime, TweenTypes tweentype);
    virtual void Update(float deltatime);
    float GetReturn();

};