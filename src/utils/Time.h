//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file Time.h
*  \brief Encapsulation of the Time object, the global time instance, and time functions.
*  \author $Author: rsharo $
*  \version $Revision: 1.15 $
*  \date    $Date: 2003/10/18 21:54:44 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/* \todo Finish implementing the rest of the time representatins.
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __SSF_TIME_H__
#define __SSF_TIME_H__
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <iostream>
#include <iomanip>

#include "MathUtils.h"

//
// If <time.h> didn't define timegm()...
#if !defined(timegm)
//
// ... Then declare a function that emulates timegm(). This function doesn't
// have public documentation (doxygen) because we don't want anybody to call
// it explicitly.  When people call timegm(), we'll redefine it as a 
// mktime_from_utc() call only where necessary.
time_t mktime_from_utc(struct tm *t);
#define timegm(T) mktime_from_utc(T)
#endif

namespace O_SESSAME {
//////////////////////////////////////////////////////////////////////////////////////////////////
/*! @defgroup Utilies Utilities
* The Utilities are the collection of classes and function that can provide miscellaneous functionality 
* to assist with the spacecraft simulation. This includes a time object, plotting, timing of execution 
* speed, interface to lower-level software and operating system components and general math functions.
*
* \par Extension Points:
*	Any other operating system calls should be encapsulated in a utility class/function to 
* ease the use of the tool/call and help promote cross-platform compatability. This may include 
* file storage and retrieval functions, communications protocols, or database interoperability.
*/

/*! @defgroup TimeUtils Time Utilities
* \ingroup Utilities
* @{
*/
typedef double ssfSeconds;	/*< Simulation representation of seconds \ingroup Utilities*/
typedef double ssfJulianDate;	/*< Simulation representation of Julian Dates \ingroup Utilities */

#define TIME_PRECISION 15	/*< Precision of time output when outputting seconds */
/*! @} */

class ssfTime;

/*! \brief Simulation Time object
* \ingroup TimeUtils
*
*  ssfTime is used to encapsulate a representation of time and provide the 
* 	functionality for converting between different time representations (ie
* 	Mean Solar, Sidereal, Julian Date, etc.) The ssfTime object includes both 
*	a stored time, as well as an epoch that the time can be measured from.
* \par Example:
* \code
* ssfTime simTime;
* ssfSeconds integrationTime = 10;
* simTime.Set(integrationTime);
* 
* ssfTime nowTime(Now());
* \endcode
*/
class ssfTime
{
public:
    /*! \brief Default constructor. Initializes the time to 0 seconds. */
    ssfTime() 				
        {Set(ssfSeconds(0)); SetEpoch(ssfSeconds(0));};
    /*! \brief Constructor creates a time object as a copy of a time struct.
        * @param _Time tm struct to be copied as the time object.
        */
    ssfTime(tm _Time) 			
        {Set(_Time);};
    /*! \brief Constructor creates a time object as a copy of a timeval struct.
        *
        *  
        *struct timeval {
        *     long    tv_sec;         // seconds
        *     long    tv_usec;        // and microseconds
        *    };
        * @param _Time timeval struct to be copied as the time object.
        */
    ssfTime(timeval _Time) 			
        {Set(_Time);};
    /*! \brief Constructor creates time object based on number of seconds.
        * @param _Time number of seconds to set the time object to.
        */
    ssfTime(ssfSeconds _Time)		
        {Set(_Time);};
    
    /*! \brief Constructor creates time object based on a calendar date.
        * @param year 4-digit year (must be between 1900-2100)
        * @param month numeric month (1-12)
        * @param day day of the month (1-31)
        * @param hour hour in 24-hour format (0-23)
        * @param minute minutes of the hour (0-59)
        * @param seconds seconds of the minute (0-59.9999999999)
        */
    ssfTime(int year, int month, int day, int hour, int minute, double seconds)		
        {Set(year, month, day, hour, minute, seconds);};
    
    /*! \brief Set the ssfTime object to a specified time struct.
        * @param _newTime the time to store in a tm struct
        */
    void Set(tm _newTime) 		
        {Set(static_cast<ssfSeconds>(timegm(&_newTime)));};
    
    /*! \brief Set the time object as a copy of a timeval struct.
        *
        *  
        * struct timeval {
        *     long    tv_sec;         // seconds
        *     long    tv_usec;        // and microseconds
        *     };
        * @param _Time timeval struct to set the time object.
        */
    void Set(timeval _Time) 			
        {Set(_Time.tv_sec + _Time.tv_usec/1000000.);};
        
    /*! \brief Set the ssfTime object to a specified time in seconds.
        * 
        * @param _newTime the time to store
        */
    void Set(ssfSeconds _newTime) 	
        {m_StoredTime = _newTime;};
    
    /*! \brief Set the ssfTime object to a specified Julian Date.
        * @param _newJD Julian Date to set.
        */
    void SetJulianDate(ssfJulianDate _newJD);
        
    /*! \brief Set the Epoch to a specified Julian Date.
        * @param _newJD Julian Date to set.
        */
    void SetEpochJulianDate(ssfJulianDate _newJD);
    
    /*! \brief Set the ssfTime object based on a calendar date.
        * @param year 4-digit year (must be between 1900-2100)
        * @param month numeric month (1-12)
        * @param day day of the month (1-31)
        * @param hour hour in 24-hour format (0-23)
        * @param minute minutes of the hour (0-59)
        * @param seconds seconds of the minute (0-59.9999999999)
        */
    void Set(int year, int month, int day, int hour, int minute, double seconds);
        
    /*! \brief Set the current time after epoch.
        * @param _timeAfter time (in seconds) after epoch
        */
    void SetTimeAfterEpoch(ssfSeconds _timeAfter)	
        {Set(m_EpochTime + _timeAfter);}; 
    
    /*! \brief Set the epoch time 
        * @param _newEpochTime new Epoch (seconds)
        */
    void SetEpoch(ssfSeconds _newEpochTime) 	
        {m_EpochTime = _newEpochTime;};
    
    /*! \brief Set the epoch time 
        * @param _newEpochTime new Epoch (tm struct)
        */
    void SetEpoch(tm _newEpochTime) 	
        {SetEpoch(static_cast<ssfSeconds>(timegm(&_newEpochTime)));};
        
    /*! \brief Set the epoch time from a timeval struct.
        *
        *  
        * struct timeval {
        *     long    tv_sec;         // seconds
        *     long    tv_usec;        // and microseconds
        *     };
        * @param _Time timeval struct used to set the Epoch time.
        */
    void SetEpoch(const timeval &_Time) 			
        {SetEpoch(_Time.tv_sec + _Time.tv_usec/1000000.);};
    
    /*! \brief Set the epoch of the ssfTime object based on a calendar date.
        * @param year 4-digit year (must be between 1900-2100)
        * @param month numeric month (1-12)
        * @param day day of the month (1-31)
        * @param hour hour in 24-hour format (0-23)
        * @param minute minutes of the hour (0-59)
        * @param seconds seconds of the minute (0-59.9999999999)
        */
    void SetEpoch(int year, int month, int day, int hour, int minute, double seconds);
    
    /*! \brief Return the current time in seconds 
        * @return currently stored time (seconds)
        */
    ssfSeconds GetSeconds()  const	
        {return m_StoredTime;};

    /*! \brief Return a tm struct of the date, time of the stored time. 
        * @return tm struct of the date-time
        * @em tm Struct Definition:
        \code
        * int tm_sec;     // seconds (0 - 60) 
        * int tm_min;     // minutes (0 - 59) 
        * int tm_hour;    // hours (0 - 23) 
        * int tm_mday;    // day of month (1 - 31) 
        * int tm_mon;     // month of year (0 - 11) 
        * int tm_year;    // year - 1900 
        * int tm_wday;    // day of week (Sunday = 0) 
        * int tm_yday;    // day of year (0 - 365) 
        * int tm_isdst;   // is summer time in effect? 
        * char *tm_zone;  // abbreviation of timezone name 
        * long tm_gmtoff; // offset from UTC in seconds 
        \endcode
        * \par Example:
        * \code 
        * cout << myTime.GetDateTime().tm_mon << "/" << myTime.GetEpochDateTime().tm_mday << "/" << myTime.GetEpochDateTime().tm_year;
        * \endcode 
        * \warning does not return sub-seconds (rounded to lowest second)
        */
    tm GetDateTime()  const	
        {time_t t = static_cast<time_t>(floor(m_StoredTime));return *gmtime(&t);};
    
    /*! \brief Return the epoch in a tm struct of the date-time . 
        * @return tm struct of the date-time.
        *
        * @em tm Struct Definition:
        \code
        * int tm_sec;     // seconds (0 - 60) 
        * int tm_min;     // minutes (0 - 59) 
        * int tm_hour;    // hours (0 - 23) 
        * int tm_mday;    // day of month (1 - 31) 
        * int tm_mon;     // month of year (0 - 11) 
        * int tm_year;    // year - 1900 
        * int tm_wday;    // day of week (Sunday = 0) 
        * int tm_yday;    // day of year (0 - 365) 
        * int tm_isdst;   // is summer time in effect? 
        * char *tm_zone;  // abbreviation of timezone name 
        * long tm_gmtoff; // offset from UTC in seconds 
        \endcode
        * \par Example:
        * \code 
        * cout << myTime.GetEpochDateTime().tm_mon << "/" << myTime.GetEpochDateTime().tm_mday << "/" << myTime.GetEpochDateTime().tm_year;
        * \endcode 
        * \warning does not return sub-seconds (rounded to lowest second)
        */
    tm GetEpochDateTime()  const	
        {time_t t = static_cast<time_t>(floor(m_EpochTime));return *gmtime(&t);};
        
    /*! \brief Return the current Epoch 
        * @return currently stored epoch time (tm struct)
        */
    ssfSeconds GetEpoch() const 
        {return m_EpochTime;};
        
        
    /*! \brief Get the Julian Date of the time object.
        * @return This function returns the Julian Date (DETAIL JD OUTPUT)
        */ 
    ssfJulianDate GetJulianDate() const;
    
    /*! \brief Get the Julian Date of the time object's epoch.
        * @return This function returns the Epoch in Julian Date format (DETAIL JD OUTPUT)
        */ 
    ssfJulianDate GetEpochJulianDate() const;
    
        
    /*! \brief Calculate the Greenwich sidereal time of the stored time.
        * @return Greenwich sidereal time, measured from epoch in 1970, [rad]
        */ 
    Angle GetGreenwichMeanSiderealTime() const;
    
    /*! \brief Get the Julian Date of the time object's epoch.
        *
        * ref Vallado p.61-63
        * \warning need to change to accept different epochs & account for rotation of central body
        * @return Greenwich sidereal time of the epoch, measured from epoch in 1970, [rad]
        */ 
    Angle GetEpochGreenwichMeanSiderealTime() const;

    /*! \brief Return the current Epoch 
        *
        * ref Vallado p.61-63
        * \warning need to change to accept different epochs & account for rotation of central body
        * @return currently stored epoch time (tm struct)
        */
//    tm GetEpoch() const 
  //      {return *gmtime(&m_EpochTime);};
    
    /*! \brief Return the time since epoch 
        * @return the number of seconds that have passed since epoch
        */
    ssfSeconds SecondsSinceEpoch() const
        {return static_cast<ssfSeconds>(m_StoredTime - m_EpochTime);};
    
    /*! \brief Add specified number of seconds to the current time and return a new object.
        * @param rhsSeconds Number of seconds to be added.
        * @return new Time object whose current time is equal to the original time plus rhsSeconds.
        */
    ssfTime operator+ (const int& rhsSeconds) const
        {return operator+(static_cast<ssfSeconds>(rhsSeconds));};
    
    /*! \brief Add specified number of seconds to the current time.
        * @param rhsSeconds Number of seconds to be added.
        * @return the same time object with the current time plus rhsSeconds.
        */    
    ssfTime operator+= (const int& rhsSeconds)
        {return operator+=(static_cast<ssfSeconds>(rhsSeconds));};       

    /*! \brief Add specified number of seconds to the current time and return a new object.
        * @param rhsSeconds Number of seconds to be added.
        * @return new Time object whose current time is equal to the original time plus rhsSeconds.
        */
    ssfTime operator+ (const long& rhsSeconds) const
        {return operator+(static_cast<ssfSeconds>(rhsSeconds));};

    /*! \brief Add specified number of seconds to the current time.
        * @param rhsSeconds Number of seconds to be added.
        * @return the same time object with the current time plus rhsSeconds.
        */ 
    ssfTime operator+= (const long& rhsSeconds)
        {return operator+=(static_cast<ssfSeconds>(rhsSeconds));}; 
    
    /*! \brief Add specified number of seconds to the current time and return a new object.
        * @param rhsSeconds Number of seconds to be added.
        * @return new Time object whose current time is equal to the original time plus rhsSeconds.
        */
    ssfTime operator+ (const ssfSeconds& rhsSeconds) const
        {return ssfTime(m_StoredTime + rhsSeconds);};
    
    /*! \brief Add specified number of seconds to the current time.
        * @param rhsSeconds Number of seconds to be added.
        * @return the same time object with the current time plus rhsSeconds.
        */ 
    ssfTime operator+= (const ssfSeconds& rhsSeconds)
        {m_StoredTime += rhsSeconds; return *this;}; 
        
    /*! \brief Subtract two time objects (the stored times).
        * @param rhs time object to be subtracted.
        * @return new time object that is the difference between the lhs and the rhs.
        */ 
    ssfSeconds operator- (const ssfTime &rhs) const
        {return (m_StoredTime - rhs.GetSeconds());};
        
    /*! \brief Greater than comparison two time objects (the stored times).
        * @param rhs time object to be compared with.
        * @return TRUE if the left operand's stored time is greater than the right operand's stored time, FALSE if it is not.
        */ 
    bool operator> (const ssfTime &rhs) const
        {return (m_StoredTime > rhs.GetSeconds());};
        
    /*! \brief Greater than or equal comparison two time objects (the stored times).
        * @param rhs time object to be compared with.
        * @return TRUE if the left operand's stored time is greater than or equal to the right operand's stored time, FALSE if it is not.
        */ 
    bool operator>= (const ssfTime &rhs) const
        {return (m_StoredTime >= rhs.GetSeconds());};

    /*! \brief Less than comparison two time objects (the stored times).
        * @param rhs time object to be compared with.
        * @return TRUE if the left operand's stored time is less than the right operand's stored time, FALSE if it is not.
        */ 
    bool operator< (const ssfTime &rhs) const
        {return (m_StoredTime < rhs.GetSeconds());};
        
    /*! \brief Less than or equal comparison two time objects (the stored times).
        * @param rhs time object to be compared with.
        * @return TRUE if the left operand's stored time is Less than or equal to the right operand's stored time, FALSE if it is not.
        */ 
    bool operator<= (const ssfTime &rhs) const
        {return (m_StoredTime <= rhs.GetSeconds());};
                
    /*! \brief Compare the equality of two time objects (the stored times).
        * @param rhs time object to be compared with.
        * @return TRUE if the stored times are equal, FALSE if they are not.
        * \todo Determine if it needs to compare the Epoch times as well.
        */ 
    bool operator== (const ssfTime &rhs) const
        {return (m_StoredTime == rhs.GetSeconds());};
   
     /*! \brief Compare the inequality of two time objects (the stored times).
        * @param rhs time object to be compared with.
        * @return TRUE if the stored times are not equal, FALSE if they are equal.
        * \todo Determine if it needs to compare the Epoch times as well.
        */ 
    bool operator!= (const ssfTime &rhs) const
        {return (m_StoredTime != rhs.GetSeconds());};
                
    /*! \brief output the time in seconds format
    */
    friend std::ostream & operator << (std::ostream& s, ssfTime& t);
private:
    ssfSeconds m_StoredTime; /*!< Internally stored time (seconds) */
    ssfSeconds m_EpochTime;  /*!< Internatlly stored Epoch time (seconds) */
    
};

    /*! \brief time used as epoch for measuring Greenwich sidereal time. 
    * 
    * 
    */
    static const ssfTime c_GreenwichSiderealEpochTime = ssfTime(1970,1,1,0,0,0);
    /*! actual Greenwich sidereal time at the specified epoch, m_GreenwichSiderealEpochTime. */
    static const Angle c_GreenwichSiderealTimeAtEpoch = 1.74933340; 
    
/*! \brief Returns the current time in seconds since Midnight GMT, January 1st, 1970.
    * \ingroup TimeUtils
    * \relates Time
    * @return number of seconds since Midnight UTC, January 1st, 1970
    */
inline ssfSeconds Now()			
        {timeval tv; gettimeofday(&tv, NULL); return (tv.tv_sec + tv.tv_usec/1000000.);}
       // {return time((time_t *)0);}; 
        

/*! \brief Initializes the tick/tock counter 
* \ingroup TimeUtils
* \relates Time
*
*  Used for calculating the time during operations. First tick() is called, then
* when the operation has been completed tock() is called which returns the time (in seconds) 
* since tick() was called.
* \sa tock()
\code
tick();
for (int ii = 0; ii < 10; ++ii) {
    ii += ii*ii;
}
cout << tock();
\endcode
* the sample code would output the time it took to calculate \f$\sum{ii^2}\f$ to the console.
*/
static ssfTime tickTime(-1); /*< global variable used to store the initial tick() time */
static ssfTime tockTime(-1); /*< global variable used to store the ending tock() time */

inline void tick()
{
    tickTime.Set(Now());
    return;
}
/*! \brief Stops the tick/tock counter and returns the time (in seconds) since tick() was called.
* \ingroup TimeUtils
* \relates Time
* \sa tick()
*/
inline ssfSeconds tock()
{
    if(tickTime.GetSeconds() > -1)
    {
        tockTime.Set(Now());
        return tockTime-tickTime;
    }
    else
        return -1;
}

/*! \brief Converts the day of the year (1-365) (given a year) to the Month and Day of they year
* \ingroup TimeUtils
* \relates Time
*/
void DayofYear2YMD(int _dayOfYear, int _year, int &_month, int &_day);

} // close namespace O_SESSAME

#endif 

// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: Time.h,v $
*	Revision 1.15  2003/10/18 21:54:44  rsharo
*	Fixed CF-LF problem and added missing comment.
*	
*	Revision 1.14  2003/10/18 21:37:29  rsharo
*	Removed "../utils" from all qmake project paths. Prepended "utils
*	/" to all #include directives for utils. Removed ".h" extensions from STL header
*	s and referenced STL components from "std::" namespace.  Overall, changed to be
*	more portable.
*	
*	Revision 1.13  2003/06/11 14:22:34  nilspace
*	Added comments to GetDateTime() and GetEpochDateTime()
*	
*	Revision 1.12  2003/06/10 01:11:46  nilspace
*	Fixed Time to build correctly (changed Greenwich epoch time to object instead of pointer)
*	
*	Revision 1.11  2003/06/09 19:41:30  nilspace
*	Added SetEpoch(year,month,day,hour,minute,second)
*	
*	Revision 1.10  2003/06/06 00:34:47  nilspace
*	?
*	
*	Revision 1.9  2003/05/21 03:57:52  nilspace
*	Added GetEpochJulianDate and comments to JulianDate conversion function.
*	
*	Revision 1.8  2003/05/19 21:19:49  nilspace
*	Made calls to overloaded Set() and SetEpoch() functions recursive calls to Set(ssfSeconds) and SetEpoch(ssfSeconds)
*	
*	Revision 1.7  2003/05/19 19:21:37  nilspace
*	Added #include<sys/time.h>
*	
*	Revision 1.6  2003/05/16 14:01:24  nilspace
*	Called gettimeofday(timeval*) to have Now(), and tick/tock return seconds with subsecond decimal parts.
*	
*	Revision 1.5  2003/05/09 23:44:29  nilspace
*	Added operator!=()
*	
*	Revision 1.4  2003/04/30 16:32:48  nilspace
*	Added operator== to ssfTime
*	
*	Revision 1.3  2003/04/27 22:04:34  nilspace
*	Created the namespace O_SESSAME.
*	
*	Revision 1.2  2003/04/25 13:45:56  nilspace
*	const'd Get() functions.
*	
*	Revision 1.1  2003/04/23 14:14:45  nilspace
*	New simulation time.
*	
*
******************************************************************************/
