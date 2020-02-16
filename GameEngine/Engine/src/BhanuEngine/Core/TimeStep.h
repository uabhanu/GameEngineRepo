#pragma once

namespace BhanuEngine
{
	class TimeStep
	{
		private:
		    float m_Time;

		public:
			TimeStep(float time = 0.0f)
				: m_Time(time)
			{
			}

			float GetSeconds() const { return m_Time; }
			float GetMilliSeconds() const { return m_Time * 1000.0f; }
	};
}
