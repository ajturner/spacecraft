//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file OrbitStateRepresentation.h
*  \brief Interface to the Orbit State Representation abstract Class.
*  \author $Author: rsharo $
*  \version $Revision: 1.9 $
*  \date    $Date: 2003/10/18 21:37:28 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/* 
*
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __SSF_ORBIT_REPRESENTATION_H__
#define __SSF_ORBIT_REPRESENTATION_H__

#include "Matrix.h"
#include "../orbitframes/OrbitFrame.h"
namespace O_SESSAME {

/** @defgroup OrbitStateRepresentation Orbit State Represenations
* \ingroup OrbitToolkit
* The orbit state representations are the various ways of storing a trajectory of 
* an object in 3-dimensional space.
* 
*/

/*! \brief Abstract base type of the orbit state representation.
* \ingroup OrbitStateRepresentation
*
* \detail The OrbitStateRepresentation class provides an interface to the 
*	group of orbit state representations. This representation can be 
*	position & velocity, keplerian elements, canonical parameters, or any 
*	other representation of an orbit state.
*
*	\par 
*	There can never be an actual instantiation of an OrbitStateRepresentation. 
*	This is an abstract data type (ADT) and just provides a required interface 
*	for the derived types. Don't try to use: OrbitStateRepresentation myOrbRep;
*	Just use as a pointer to the derived types.
*
*	\par Example:
*	
*
*/ 
class OrbitStateRepresentation
{
public:
    /*! \brief Set the orbit representation using position and velocity components.
        * @param _Position 3-element vector of position components. (km)
        * @param _Velocity 3-element vector of vector components. (km/s)
        */
    virtual void SetPositionVelocity(const Vector &_Position, const Vector &_Velocity) = 0;

    /*! \brief Set the orbit representation using position and velocity components.
        * @param _PositionVelocity 6-element vector of position \& velocity components. (km, km/s)
        */
    virtual void SetPositionVelocity(const Vector &_PositionVelocity) = 0;
    
    /*! \brief Return the position and velocity vectors of the orbit state.
        * @return 6-element vector of position and velocity vector components. [km, km, km, km/s, km/s, km/s]^T
        */    
    virtual Vector GetPositionVelocity() const = 0;

    /*! \brief Return the position and velocity vectors of the orbit state by reference (through the input parameters)
        * @param _Position a Vector through which to return the 3-element position vector. (km)
        * @param _Velocity a Vector through which to return the 3-element velocity vector. (km/s)
        */
    virtual void GetPositionVelocity(Vector &_Position, Vector &_Velocity) const = 0;

    /*! \brief Return a pointer to a new instance of a derived orbit state representation type.
        *
        * \detail This is used to request memory for a new instance of a derived instance when the 
        *	actual type of the derived object is unknown. By calling this function, the compiler 
        *	links to the correct derived function to return a pointer and allocate memory of 
        *	the correct type.
        *	\par Example: 
        *	\code 
                * OrbitStateRepresentation* newOrbRep = oldOrbRep->NewPointer();
        *       \endcode
        * @return a pointer to a new allocation of memory for the appropriate representation.
        */
    virtual OrbitStateRepresentation* NewPointer() = 0;

    /*! \brief Return a pointer to a copy of a derived instance orbit state representation type.
        *
        * \detail This is used to request memory for and copy of an instance of a derived representation when the 
        *	actual type of the derived object is unknown. By calling this function, the compiler 
        *	links to the correct derived function to return a pointer and allocate memory of 
        *	the correct type and copy the data.
        *	\par Example: 
                \code 
        * OrbitStateRepresentation* copyOldOrbRep = oldOrbRep->Clone();
                \endcode
        * @return a pointer to a copy of the appropriate representation.
        */
    virtual OrbitStateRepresentation* Clone() = 0;

//    virtual void SetState(const Vector &_Elements1, const Vector &_Elements2) = 0;
    /*! \brief Set the vector of the representation's state vector.
        * \warning Depracted - Do Not Use - will be moved internally
        */
    virtual void SetState(const Vector &_Elements) = 0;
    
    /*! \brief Return a vector of the representation's state vector.
        * \warning Depracted - Do Not Use - will be moved internally
        */
    virtual Vector GetState() const = 0;
    
protected:

private:

};
} // close namespace O_SESSAME

#endif

// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: OrbitStateRepresentation.h,v $
*	Revision 1.9  2003/10/18 21:37:28  rsharo
*	Removed "../utils" from all qmake project paths. Prepended "utils
*	/" to all #include directives for utils. Removed ".h" extensions from STL header
*	s and referenced STL components from "std::" namespace.  Overall, changed to be
*	more portable.
*	
*	Revision 1.8  2003/05/13 18:47:56  nilspace
*	Fixed comments for better formatting.
*	
*	Revision 1.7  2003/05/05 20:47:38  nilspace
*	Changed the Get/SetPositionVelocity functions to not require a OrbitFrame.
*	
*	Revision 1.6  2003/05/02 16:16:46  nilspace
*	Documented the API.
*	
*	Revision 1.5  2003/04/29 18:48:31  nilspace
*	Added NewPointer and Clone functions to help in getting the correct memory allocation.
*	
*	Revision 1.4  2003/04/24 21:14:23  nilspace
*	const'd all Get() functions.
*	
*	Revision 1.3  2003/04/23 16:26:08  nilspace
*	Updated directory structure & default parameters.
*	
*	Revision 1.2  2003/04/22 18:06:08  nilspace
*	Added math for Matthew Berry.
*	
*	Revision 1.1  2003/04/08 22:47:35  nilspace
*	Initial Submission.
*	
*
******************************************************************************/
