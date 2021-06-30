#pragma once
#include <chrono> //chrono is fine for now, but OS specific libraries will be more accurate

namespace brcl
{

	class Timestep
	{
	public:

		Timestep(float time = 0.0f) :
			m_Time(time) {}

		operator float() const { return m_Time; }

		float GetSeconds() const { return m_Time; }
		
		Timestep& operator+=(const Timestep& delta)
		{
			m_Time += delta;
			return *this;
		}

		std::string ToString() const
		{
			std::stringstream ss;
			ss << GetSeconds() << "s";
			return ss.str();
		}

	private:
		float m_Time;
	};

	
	class Timer
	{
	public:
		Timer(const std::string& name = "Debug")
			: m_Start(std::chrono::high_resolution_clock::now()), m_Name(name) {}

		void Reset()
		{
			m_Start = std::chrono::high_resolution_clock::now();
		}
		
		//get time in seconds
		Timestep GetTime() const
		{
			m_Last = std::chrono::high_resolution_clock::now();
			std::chrono::duration<float> time = m_Last - m_Start;
			return Timestep(time.count());
		}


		std::string ToString() const
		{
			std::stringstream ss;
			ss << m_Name << " Timer: " << GetTime().ToString();
			return ss.str();
		}
	
	private:
		std::chrono::time_point<std::chrono::steady_clock> m_Start;
		mutable std::chrono::time_point<std::chrono::steady_clock> m_Last;

		std::string m_Name;
	};
	
}