#pragma once

#include <deque>
#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>

#include <Dumper.hpp>
#include <Utility.hpp>

namespace csd // stands for cosmodog
{

using Segment = Vec;

class Character : public Dumpable
{
	const float_t SegmentDist = 60.;

	float_t speed_;

	// from positive x direction, anticlockwise
	float_t rotationAngle_;

	Vec getTranslationVec() const;

public:

	std::deque<Segment> tail_; // to private!

	Character(Vec pos, float_t speed, float_t rotationAngle)
	:
		Dumpable{},
		tail_{pos},
		speed_{speed},
		rotationAngle_{rotationAngle}
	{}

	void growTail();

	void makeStep();

	// angle - in radians
	void rotate(RotDir dir, float_t angle);

	void dump() const override;
};

/*
	Returns random value from [0; 1)
*/
float_t getRandom()
{
	return static_cast<float_t>(rand()) / RAND_MAX;
}

void Character::growTail()
{
	SCOPE_DUMP;

	float_t randVal = getRandom();
	Segment newSegment{};

	if (tail_.size() >= 2)
	{
		const Segment& last 	= tail_[tail_.size() - 1];
		const Segment& prelast 	= tail_[tail_.size() - 2];
	
		newSegment = getUnitVec(prelast, last) * SegmentDist;

		// angle belongs [-23; 23] in degrees
		float_t randomAngle = (randVal - 0.5) * (M_PI / 4);

		newSegment = rotateVec(newSegment, randomAngle);
	}
	else
	{
		float_t randomAngle = randVal * M_PI * 2;

		newSegment = getUnitVec(randomAngle) * SegmentDist;
	}

	tail_.push_back(tail_.back() + newSegment);
}

/*
	Make a step with speed_ in the direction
	of rotationAngle_
*/
void Character::makeStep()
{
	SCOPE_DUMP;

	const Segment& currentHead = tail_.front();

	Vec translationVec = getTranslationVec();

	tail_.push_front(currentHead + translationVec);

	tail_.pop_back();
}

Vec Character::getTranslationVec() const
{
	return getUnitVec(rotationAngle_) * SegmentDist;
}

void Character::rotate(RotDir dir, float_t angle)
{
	switch(dir)
	{
		case RotDir::CW:

			rotationAngle_ -= angle;
			break;

		case RotDir::ACW:

			rotationAngle_ += angle;
			break;
	}
}

void Character::dump() const
{
	std::cout << "Segments: \n";

	for (const Segment& seg: tail_)
	{
		std::cout << seg << "--";
	}

	std::cout << '\n';

	std::cout << "Speed: " << speed_ << '\n';

	std::cout << "Angle: " << rotationAngle_ << '\n';

	std::cout << '\n';
}

};