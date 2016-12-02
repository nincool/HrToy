#ifndef _HR_ANGLE_H_
#define _HR_ANGLE_H_

#include "HrMath/Include/HrMathPrerequisites.h"
#include "HrMath/Include/HrMathCom.h"

namespace Hr
{
	/** \addtogroup Core
	*  @{
	*/
	/** \addtogroup Math
	*  @{
	*/
	/** Wrapper class which indicates a given angle value is in Radians.
	@remarks
	Radian values are interchangeable with Degree values, and conversions
	will be done automatically between them.
	*/
	class Degree;
	class Radian
	{
		REAL mRad;

	public:
		explicit Radian(REAL r = 0) : mRad(r) {}
		Radian(const Degree& d);
		Radian& operator = (const REAL& f) { mRad = f; return *this; }
		Radian& operator = (const Radian& r) { mRad = r.mRad; return *this; }
		Radian& operator = (const Degree& d);

		REAL valueDegrees() const { return mRad * HrMath::RAD2DEG(); }; // see bottom of this file
		REAL valueRadians() const { return mRad; }

		const Radian& operator + () const { return *this; }
		Radian operator + (const Radian& r) const { return Radian(mRad + r.mRad); }
		Radian operator + (const Degree& d) const;
		Radian& operator += (const Radian& r) { mRad += r.mRad; return *this; }
		Radian& operator += (const Degree& d);
		Radian operator - () const { return Radian(-mRad); }
		Radian operator - (const Radian& r) const { return Radian(mRad - r.mRad); }
		Radian operator - (const Degree& d) const;
		Radian& operator -= (const Radian& r) { mRad -= r.mRad; return *this; }
		Radian& operator -= (const Degree& d);
		Radian operator * (REAL f) const { return Radian(mRad * f); }
		Radian operator * (const Radian& f) const { return Radian(mRad * f.mRad); }
		Radian& operator *= (REAL f) { mRad *= f; return *this; }
		Radian operator / (REAL f) const { return Radian(mRad / f); }
		Radian& operator /= (REAL f) { mRad /= f; return *this; }

		bool operator <  (const Radian& r) const { return mRad <  r.mRad; }
		bool operator <= (const Radian& r) const { return mRad <= r.mRad; }
		bool operator == (const Radian& r) const { return mRad == r.mRad; }
		bool operator != (const Radian& r) const { return mRad != r.mRad; }
		bool operator >= (const Radian& r) const { return mRad >= r.mRad; }
		bool operator >  (const Radian& r) const { return mRad >  r.mRad; }
	};

	/** Wrapper class which indicates a given angle value is in Degrees.
	@remarks
	Degree values are interchangeable with Radian values, and conversions
	will be done automatically between them.
	*/
	class Degree
	{
		REAL mDeg; // if you get an error here - make sure to define/typedef 'Real' first

	public:
		explicit Degree(REAL d = 0) : mDeg(d) {}
		Degree(const Radian& r) : mDeg(r.valueDegrees()) {}
		Degree& operator = (const REAL& f) { mDeg = f; return *this; }
		Degree& operator = (const Degree& d) { mDeg = d.mDeg; return *this; }
		Degree& operator = (const Radian& r) { mDeg = r.valueDegrees(); return *this; }

		REAL valueDegrees() const { return mDeg; }
		REAL valueRadians() const {	return mDeg * HrMath::DEG2RAD();}; // see bottom of this file

		const Degree& operator + () const { return *this; }
		Degree operator + (const Degree& d) const { return Degree(mDeg + d.mDeg); }
		Degree operator + (const Radian& r) const { return Degree(mDeg + r.valueDegrees()); }
		Degree& operator += (const Degree& d) { mDeg += d.mDeg; return *this; }
		Degree& operator += (const Radian& r) { mDeg += r.valueDegrees(); return *this; }
		Degree operator - () const { return Degree(-mDeg); }
		Degree operator - (const Degree& d) const { return Degree(mDeg - d.mDeg); }
		Degree operator - (const Radian& r) const { return Degree(mDeg - r.valueDegrees()); }
		Degree& operator -= (const Degree& d) { mDeg -= d.mDeg; return *this; }
		Degree& operator -= (const Radian& r) { mDeg -= r.valueDegrees(); return *this; }
		Degree operator * (REAL f) const { return Degree(mDeg * f); }
		Degree operator * (const Degree& f) const { return Degree(mDeg * f.mDeg); }
		Degree& operator *= (REAL f) { mDeg *= f; return *this; }
		Degree operator / (REAL f) const { return Degree(mDeg / f); }
		Degree& operator /= (REAL f) { mDeg /= f; return *this; }

		bool operator <  (const Degree& d) const { return mDeg <  d.mDeg; }
		bool operator <= (const Degree& d) const { return mDeg <= d.mDeg; }
		bool operator == (const Degree& d) const { return mDeg == d.mDeg; }
		bool operator != (const Degree& d) const { return mDeg != d.mDeg; }
		bool operator >= (const Degree& d) const { return mDeg >= d.mDeg; }
		bool operator >  (const Degree& d) const { return mDeg >  d.mDeg; }

	};

	// these functions could not be defined within the class definition of class
	// Radian because they required class Degree to be defined
	inline Radian::Radian(const Degree& d) : mRad(d.valueRadians()) {
	}
	inline Radian& Radian::operator = (const Degree& d) {
		mRad = d.valueRadians(); return *this;
	}
	inline Radian Radian::operator + (const Degree& d) const {
		return Radian(mRad + d.valueRadians());
	}
	inline Radian& Radian::operator += (const Degree& d) {
		mRad += d.valueRadians();
		return *this;
	}
	inline Radian Radian::operator - (const Degree& d) const {
		return Radian(mRad - d.valueRadians());
	}
	inline Radian& Radian::operator -= (const Degree& d) {
		mRad -= d.valueRadians();
		return *this;
	}

}


#endif



