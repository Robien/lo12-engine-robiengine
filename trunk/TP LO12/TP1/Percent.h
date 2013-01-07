///
///  \file Percent.h
///	 \brief easy way to print an optimized %
///  \date Feb 27, 2012
///  \author romain
///

#ifndef PERCENT_H_
#define PERCENT_H_


///
/// \class Percent
/// \brief easy way to print an optimized %
///
class Percent
{
public:
    ///
    /// \brief constructor
    /// \param valMax final value corresponding at 100%
    ///
    Percent(unsigned int valMax);
    ///
    /// \brief destructor
    ///
    virtual ~Percent();

public:
    ///
    /// \brief print new percentage if it change
    /// \param valCurrent : value to compute proportion
    /// \return void
    ///
    void majIfNeeded(unsigned int valCurrent);

public:
    ///
    /// \brief print time decomposed in min, h, etc ...
    /// \param time time in seconde
    /// \return void
    ///
    void printTime(unsigned int secondes);

private:
    unsigned int _valMax;
    unsigned int _current;
    unsigned int _currentTimeS;
    unsigned int _currentTime;
    unsigned int _begin;
};

#endif /* PERCENT_H_ */
