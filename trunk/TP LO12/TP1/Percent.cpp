///
///  \file Percent.cpp
///	 \brief Description
///  \date Feb 27, 2012
///  \author romain
///

#include "Percent.h"
#include "iostream"
#include <time.h>

Percent::Percent(unsigned int valMax) :
        _valMax(valMax), _current(101),  _currentTimeS(0), _currentTime(0),_begin(time(NULL))
{
}

Percent::~Percent()
{
}

void Percent::printTime(unsigned int secondes)
{
    unsigned int min = secondes / 60;
    unsigned int h = min / 60;
    unsigned int j = h / 24;
    unsigned int sem = j / 7;
    unsigned int m = sem / 4;
    unsigned int a = m / 12;
    unsigned int d = a / 10;
    unsigned int mil = d / 100;

    unsigned int s = secondes - min * 60;
    min -= h * 60;
    h -= j * 24;
    j -= sem / 7;
    sem -= m * 4;
    m -= a * 12;
    a -= d * 10;
    d -= mil * 100;
    bool av = false;
    if (mil > 0)
    {
        if (av && (d > 0 || a > 0 || m > 0 || sem > 0 || j > 0 || h > 0 || min > 0 || s > 0))
        {
            std::cout << ", ";
        }
        else if (av)
        {
            std::cout << " and ";

        }
        av = true;
        std::cout << mil << " millenium";
        if (mil > 1)
        {
            std::cout << "s";
        }
    }
    if (d > 0)
    {
        if (av && (a > 0 || m > 0 || sem > 0 || j > 0 || h > 0 || min > 0 || s > 0))
        {
            std::cout << ", ";
        }
        else if (av)
        {
            std::cout << " and ";

        }
        av = true;
        std::cout << d << " decade";
        if (d > 1)
        {
            std::cout << "s";
        }
    }
    if (a > 0)
    {
        if (av && (m > 0 || sem > 0 || j > 0 || h > 0 || min > 0 || s > 0))
        {
            std::cout << ", ";
        }
        else if (av)
        {
            std::cout << " and ";

        }
        av = true;
        std::cout << a << " year";
        if (a > 1)
        {
            std::cout << "s";
        }
    }
    if (m > 0)
    {
        if (av && (sem > 0 || j > 0 || h > 0 || min > 0 || s > 0))
        {
            std::cout << ", ";
        }
        else if (av)
        {
            std::cout << " and ";

        }
        av = true;
        std::cout << m << " month";
        if (m > 1)
        {
            std::cout << "s";
        }
    }
    if (sem > 0)
    {
        if (av && (j > 0 || h > 0 || min > 0 || s > 0))
        {
            std::cout << ", ";
        }
        else if (av)
        {
            std::cout << " and ";

        }
        av = true;
        std::cout << sem << " week";
        if (sem > 1)
        {
            std::cout << "s";
        }
    }
    if (j > 0)
    {
        if (av && (h > 0 || min > 0 || s > 0))
        {
            std::cout << ", ";
        }
        else if (av)
        {
            std::cout << " and ";

        }
        av = true;
        std::cout << j << " day";
        if (j > 1)
        {
            std::cout << "s";
        }
    }
    if (h > 0)
    {
        if (av && (min > 0 || s > 0))
        {
            std::cout << ", ";
        }
        else if (av)
        {
            std::cout << " and ";

        }
        av = true;
        std::cout << h << "h";
    }
    if (min > 0)
    {
        if (av && (s > 0))
        {
            std::cout << ", ";
        }
        else if (av)
        {
            std::cout << " and ";

        }
        av = true;
        std::cout << min << "min";
    }
    if (s > 0)
    {
        if (av)
        {
            std::cout << " and ";

        }
        av = true;
        std::cout << s << "s";
    }
}

void Percent::majIfNeeded(unsigned int valCurrent)
{
    unsigned int tmp;
    unsigned int elapsed = time(NULL) - _begin;
    if (_current != (tmp = valCurrent * 100 / _valMax)
            || (elapsed > 0 && _currentTime != elapsed
                    && (unsigned int) (elapsed / (((float) valCurrent) / ((float) _valMax)) - elapsed) != _currentTimeS))
    {
        std::cout << "\r";
		std::cout << "[";
		unsigned int TAILLE_PROGRESS_BAR = 20;
		for (unsigned int i = 0; i < TAILLE_PROGRESS_BAR; ++i)
		{
			if ((valCurrent *TAILLE_PROGRESS_BAR / _valMax) > i)
			{
				std::cout << "#";
			}
			else
			{
				std::cout << " ";
			}
		}
		std::cout << "] ";
		std::cout << valCurrent * 100 / _valMax << "% ";
        if (elapsed > 0 && ((float) valCurrent) / ((float) _valMax) > 0
                && (elapsed > 0 && _currentTime != elapsed
                        && (unsigned int) (elapsed / (((float) valCurrent) / ((float) _valMax)) - elapsed) != _currentTimeS))
        {
            _currentTimeS = (unsigned int) (elapsed / (((float) valCurrent) / ((float) _valMax)) - elapsed);
            printTime((unsigned int) (elapsed / (((float) valCurrent) / ((float) _valMax)) - elapsed));
            std::cout << "                                            ";
//            std::cout << (unsigned int) (elapsed / (((float) valCurrent) / ((float) _valMax)) - elapsed) << "s          ";
        }
        _currentTime = elapsed;
        std::flush(std::cout);
        _current = tmp;
    }
}

