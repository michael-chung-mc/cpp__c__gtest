#pragma once
#ifndef Comparinator_H
#define Comparinator_H

class Comparinator {
private:
	float EPSILON = 0.00001;
public:
	bool equalFloat(float a, float b);
	// tuples & point & vector
	template <typename Agent>
	bool equalTuple(Agent a, Agent b)
	{
		return (Comparinator::equalFloat(a.x, b.x) && Comparinator::equalFloat(a.y, b.y) && Comparinator::equalFloat(a.z, b.z) && Comparinator::equalFloat(a.w, b.w));
	};
};

#endif