#pragma once
#ifndef COMPARINATOR_H
#define COMPARINATOR_H

class Comparinator {
public:
	Comparinator();
	bool checkFloat(const double &a, const double &b) const;
	// tuples & point & vector
	template <typename Agent>
	bool checkTuple(Agent a, Agent b)
	{
		return (checkFloat(a.mbrX, b.mbrX) && checkFloat(a.mbrY, b.mbrY) && checkFloat(a.mbrZ, b.mbrZ) && checkFloat(a.mbrW, b.mbrW));
	};
private:
	float mbrEpsilon;
};

#endif