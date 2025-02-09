#include "Animation.h"
#include "Entity.h"
#include "Atlas.h"
#include <RectI.h>
#include <Engine.h>

homer::Animation::Animation(Entity* parent) : Component(parent)
{
	m_Play = false;
}

void homer::Animation::Update(float dt)
{
	if (m_Play)
	{
		int m_Row = m_ClipList[m_CurrentClip].startingRow + static_cast<int>(m_CurrentFrame / m_frameInRows);
		RectI frame{
			m_frameWidth * (m_CurrentFrame % m_frameInRows),
			m_frameHeight * m_Row,
			m_frameWidth,
			m_frameHeight 
		};
		this->m_Entity->GetComponent<Atlas>()->SetCurrentFrame(frame);
		m_TimePassed += dt;
		if (m_TimePassed >= m_ClipList[m_CurrentClip].delay)
		{
			if (m_CurrentFrame + 1 == m_ClipList[m_CurrentClip].count)
			{
				if (m_Loop)
					m_CurrentFrame = 0;
				else
					Stop();
			}
			else
			{
				m_CurrentFrame += 1;
			}
			m_TimePassed = 0;
		}
	}
}

void homer::Animation::InitAnimation(int frameInRows, int frameWidth, int frameHeight)
{
	m_frameInRows = frameInRows;
	m_frameWidth = frameWidth;
	m_frameHeight = frameHeight;
}

void homer::Animation::AddClip(const std::string& name, int startingRow, int start, int count, float delay)
{
	if (m_ClipList.count(name) == 0)
	{
		m_ClipList.emplace(name, Clip{ startingRow, start, count, delay });
	}
}

void homer::Animation::Stop()
{
	m_Play = false;
	m_Loop = false;
}

std::string homer::Animation::GetCurrentClip()
{
	return m_CurrentClip;
}

bool homer::Animation::GetIsPlaying()
{
	return m_Play;
}

void homer::Animation::Play(const std::string& name, bool loop)
{
	if (m_ClipList.count(name) > 0)
	{
		m_CurrentClip = name;
		m_CurrentFrame = m_ClipList[name].start;
		m_Loop = loop;
		m_Play = true;
	}
}
