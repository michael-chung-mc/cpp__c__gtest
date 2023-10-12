#include "comparinator.h"
#include "pch.h"
#include <cmath>

Comparinator::Comparinator()
{
	mbrEpsilon = getEpsilon();
}

bool Comparinator::checkFloat(const double &a, const double &b) const
{
	return fabs(a - b) < mbrEpsilon;
};
