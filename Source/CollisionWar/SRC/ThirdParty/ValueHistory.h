#ifndef VALUEHISTORY_H
#define VALUEHISTORY_H

class ValueHistory
{
	static const int MAX_HISTORY = 256;
	float m_samples[MAX_HISTORY];
	int m_hsamples;
public:
	ValueHistory();

	inline void addSample(const float val)
	{
		m_hsamples = (m_hsamples+MAX_HISTORY-1) % MAX_HISTORY;
		m_samples[m_hsamples] = val;
	}
	
	inline int getSampleCount() const
	{
		return MAX_HISTORY;
	}
	
	inline float getSample(const int i) const
	{
		return m_samples[(m_hsamples+i) % MAX_HISTORY];
	}
	
	float getSampleMin() const;
	float getSampleMax() const;
	float getAverage() const;
};

#endif // VALUEHISTORY_H