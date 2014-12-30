//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file Time.h
*  \brief Implementation of the Time class.
*  \author $Author: rsharo $
*  \version $Revision: 1.10 $
*  \date    $Date: 2003/10/18 22:02:11 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/*  
* \todo Finish implementing the rest of the time representatins.
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "utils/Time.h"

namespace O_SESSAME {

static int DaysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
 
/*! \brief Calculates the Julian Date given a time in seconds since the system epoch.
    * \ingroup TimeUtils
    * \relates ssfTime
    * This function takes in seconds since epoch and returns the datetime in Julian Date 
    * format. Since the input time is seconds since system epoch (Jan 1, 1970 at midnight for 
    * linux), the JulianDate function uses the system gmtime() function to convert to a DateTime
    * struct. 
    * \warning be careful of differences in system epoch times (Unix vs. Windows).
    * @param _time The time to be converted in seconds since the system epoch time.
    * @return this function returns the conversion from seconds since system epoch time to 
    *	Julian Date.
    */
ssfJulianDate JulianDate(const ssfSeconds &_time)
{
    time_t t = static_cast<time_t>(floor(_time));
    tm DateTime = *gmtime(&t);
    ssfJulianDate JD = 0;
    double uSec = _time - floor(_time);
    JD += 367 * (DateTime.tm_year + 1900);
    JD -= floor((7 * ((DateTime.tm_year + 1900) + floor(((DateTime.tm_mon + 1) + 9)/12))) / 4);
    JD += floor((275 * (DateTime.tm_mon + 1)) / 9);
    JD += DateTime.tm_mday;
    JD += 1721013.5;
    JD += (((DateTime.tm_sec + uSec)/60.0 + DateTime.tm_min) / 60.0 + DateTime.tm_hour) / 24;
    return JD;
}

void DayofYear2YMD(int _dayOfYear, int _year, int &_month, int &_day)
{	
    int total = 0;
    // Is it a leap-year?
    if (_year % 4 == 0)
        DaysInMonth[1] = 29;
    for (_month = 0; total + DaysInMonth[_month+1] < _dayOfYear; ++_month)
    {
        total += DaysInMonth[_month];
    }
    ++_month;
    _day = _dayOfYear - total;
    return;
}

/*! \fn ssfJulianDate ssfTime::GetJulianDate() const
*
/f[
\mbox{Julian Date} & = & 367(year) - floor\left(\frac{7\left[year+floor\left(\frac{month+9}{12}\right)\right]}{4}\right) \\
& & + floor\left(\frac{275month}{9}\right) + day + 1,721,013.5\\ 
& & + \frac{\frac{\left(\frac{seconds}{60} + minute\right)}{60}+hour}{24} 
/f]
*/
ssfJulianDate ssfTime::GetJulianDate() const
{
/*
    time_t t = static_cast<time_t>(floor(m_StoredTime));
    tm DateTime = *gmtime(&t);
    ssfJulianDate JD = 0;
    double uSec = m_StoredTime - floor(m_StoredTime);
    JD += 367 * (DateTime.tm_year + 1900);
    JD -= floor((7 * ((DateTime.tm_year + 1900) + floor(((DateTime.tm_mon + 1) + 9)/12))) / 4);
    JD += floor((275 * (DateTime.tm_mon + 1)) / 9);
    JD += DateTime.tm_mday;
    JD += 1721013.5;
    JD += (((DateTime.tm_sec + uSec)/60.0 + DateTime.tm_min) / 60.0 + DateTime.tm_hour) / 24;
    return JD;
*/
    return JulianDate(m_StoredTime);
}

ssfJulianDate ssfTime::GetEpochJulianDate() const
{
    return JulianDate(m_EpochTime);
}
void ssfTime::Set(int year, int month, int day, int hour, int minute, double seconds)
{
    tm DateTime;
    DateTime.tm_year = year - 1900;
    DateTime.tm_mon = month - 1;
    DateTime.tm_mday = day;
    DateTime.tm_hour = hour;
    DateTime.tm_min = minute;
    DateTime.tm_sec = static_cast<int>(floor(seconds));
    m_StoredTime = static_cast<ssfSeconds>(timegm(&DateTime));
    m_StoredTime += seconds - floor(seconds);
}

void ssfTime::SetEpoch(int year, int month, int day, int hour, int minute, double seconds)
{
    tm DateTime;
    DateTime.tm_year = year - 1900;
    DateTime.tm_mon = month - 1;
    DateTime.tm_mday = day;
    DateTime.tm_hour = hour;
    DateTime.tm_min = minute;
    DateTime.tm_sec = static_cast<int>(floor(seconds));
    m_EpochTime = static_cast<ssfSeconds>(timegm(&DateTime));
    m_EpochTime += seconds - floor(seconds);
}


void ssfTime::SetJulianDate(ssfJulianDate _newJD)
{
    // Since the Julian Date is measured in days, while the 
    // internal time is stored in seconds since the system epoch,
    // subtract the system Julian Date from the specified
    // Julian Date and convert to seconds.
    m_StoredTime = (_newJD - JulianDate(0)) * 24 * 60 * 60;
    return;
}

void ssfTime::SetEpochJulianDate(ssfJulianDate _newJD)
{
    // Since the Julian Date is measured in days, while the 
    // internal time is stored in seconds since the system epoch,
    // subtract the system Julian Date from the specified
    // Julian Date and convert to seconds.
    m_EpochTime = (_newJD - JulianDate(0)) * 24 * 60 * 60;
    return;
}

Angle ssfTime::GetGreenwichMeanSiderealTime() const
{
    double Tut1 = (this->GetJulianDate() - c_GreenwichSiderealEpochTime.GetJulianDate() - 2451545) / 36525;
    return  1.753368560 + 628.3319706889*Tut1 + 6.7707*pow(10,-6)*pow(Tut1,2) - 4.5*pow(10,-10)*pow(Tut1,3);
}
    
Angle ssfTime::GetEpochGreenwichMeanSiderealTime() const
{
    double Tut1 = (this->GetEpochJulianDate() - c_GreenwichSiderealEpochTime.GetJulianDate() - 2451545) / 36525;
    return  1.753368560 + 628.3319706889*Tut1 + 6.7707*pow(10,-6)*pow(Tut1,2) - 4.5*pow(10,-10)*pow(Tut1,3);
}
    
std::ostream & operator << (std::ostream& s, ssfTime& t)
{
    s << std::setprecision(TIME_PRECISION) << t.GetSeconds();
    return s;
}
} // close namespace O_SESSAME

// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: Time.cpp,v $
*	Revision 1.10  2003/10/18 22:02:11  rsharo
*	Fixed CR-LF problem.
*	
*	Revision 1.9  2003/10/18 21:37:29  rsharo
*	Removed "../utils" from all qmake project paths. Prepended "utils
*	/" to all #include directives for utils. Removed ".h" extensions from STL header
*	s and referenced STL components from "std::" namespace.  Overall, changed to be
*	more portable.
*	
*	Revision 1.8  2003/06/10 14:49:16  nilspace
*	removed commas from numbers.
*	
*	Revision 1.7  2003/06/10 01:11:46  nilspace
*	Fixed Time to build correctly (changed Greenwich epoch time to object instead of pointer)
*	
*	Revision 1.6  2003/06/09 19:41:30  nilspace
*	Added SetEpoch(year,month,day,hour,minute,second)
*	
*	Revision 1.5  2003/05/21 13:35:59  nilspace
*	Fixed the second GetJulianDate to be GetEpochJulianDate
*	
*	Revision 1.4  2003/05/21 03:57:52  nilspace
*	Added GetEpochJulianDate and comments to JulianDate conversion function.
*	
*	Revision 1.3  2003/05/20 17:44:21  nilspace
*	Updated comments.
*	
*	Revision 1.2  2003/04/27 22:04:34  nilspace
*	Created the namespace O_SESSAME.
*	
*	Revision 1.1  2003/04/23 14:46:49  nilspace
*	New Time class for simulation time.
*	
*
******************************************************************************/

