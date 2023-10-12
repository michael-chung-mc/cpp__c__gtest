#include "light.h"
#include "tuple.h"
#include "color.h"
#include "comparinator.h"

PointSource::PointSource()
{
    this->mbrPosition = Point(0,0,0);
    this->mbrIntensity = Color(0,0,0);
}

PointSource::PointSource(Point position, Color intensity)
{
    this->mbrPosition = position;
    this->mbrIntensity = intensity;
}

bool PointSource::checkEqual(const PointSource &other) const
{
    Comparinator ce = Comparinator();
    return ce.checkTuple(this->mbrPosition,other.mbrPosition) && mbrIntensity.checkEqual(other.mbrIntensity);
}