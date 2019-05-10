#pragma once
class Game;

struct RayCastResultCallback : public b2RayCastCallback
{
public:

	bool m_Hit;
	b2Body* m_pBody;
	RayCastResultCallback() { m_Hit = false; m_pBody = 0; }
	float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point,
		const b2Vec2& normal, float32 fraction)
	{
		m_Hit = true;
		m_pBody = fixture->GetBody();
		return fraction;
	}


};
