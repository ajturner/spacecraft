//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file PositionVelocity.h
*  \brief Implementation of the Position/Velocity Coordinate Type Class.
*  \author $Author: nilspace $
*  \version $Revision: 1.7 $
*  \date    $Date: 2003/05/13 18:47:56 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/* \warning OrbitFrame conversions not included yet
* \todo include conversion functions
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __SSF_POSITIONVELOCITY_H__
#define __SSF_POSITIONVELOCITY_H__
#include "Matrix.h"
#include "OrbitStateRepresentation.h"

namespace O_SESSAME {
/*! \ingroup OrbitStateRepresentation @{ */
#define NUM_POSVEL_ELEMENTS 6 /*!< Number of elements in the Position/Velocity elements vector */
/** @} */

/*! \brief Position & Velocity representation of the orbital position.
* \ingroup OrbitStateRepresentation 
*
* \detail The PositionVelocity class stores the position and velocity components of an orbital position.
*	This should be used in an OrbitState object to also store the appropriate reference frame.
*
*	\par Example:
*	
*/ 
class PositionVelocity : public OrbitStateRepresentation
{
public:
    /*! \brief Create an initially empty PositionVelocity orbit state representation. */
    PositionVelocity();
    /*! \brief Create a PositionVelocity orbit state representation from a vector of the position & velocity elements.
        * @param _State 6-element vector of the position and velocity components. (km, km/s)
        */   
    PositionVelocity(const Vector &_State);
    /*! \brief Create a PositionVelocity orbit state representation from the position & velocity vectors.
        * @param _Position 3-element vector of the position components. (km)
        * @param _Velocity 3-element vector of the velocity components. (km/s)
        */   
    PositionVelocity(const Vector &_Position, const Vector &_Velocity);

    /*! \brief Default Deconstructor */
    virtual ~PositionVelocity();

    /*! \brief Set the PositionVelocity representation directly from the position and velocity vectors.
        * @param _Position 3-element vector of position components. (km)
        * @param _Velocity 3-element vector of vector components. (km/s)
        * @param _TargetOrbFrame Reference frame that the vector components are in.
        */
    void SetPositionVelocity(const Vector &_Position, const Vector &_Velocity);
    /*! \brief Set the PositionVelocity representation by converting the position and velocity vector.
        * @param _Position 6-element vector of position and velocity components. (km, km/s)
        * @param _TargetOrbFrame Reference frame that the vector components are in.
        */
    void SetPositionVelocity(const Vector &_PositionVelocity) 		{SetState(_PositionVelocity);};
    
    /*! \brief Return the stored position and velocity vector.
        * @return 6-element vector of position and velocity vector components. [km, km, km, km/s, km/s, km/s]^T
        */  
    Vector GetPositionVelocity() const 					{return GetState();};

    /*! \brief Return the stored position and velocity vectors by reference.
        * @param _Position a Vector through which to return the 3-element position vector. (km)
        * @param _Velocity a Vector through which to return the 3-element velocity vector. (km/s)
        */
    void GetPositionVelocity(Vector &_Position, Vector &_Velocity) const {GetState(_Position, _Velocity); return;};

    /*! \brief Return a pointer to a new instance of a PositionVelocity orbit state representation type.
        *
        * \detail This is used to request memory for a new instance of a PositionVelocity. It is necessary 
        *	when attempting to get a pointer from the abstract data type OrbitStateRepresentation 
        *	and the actual representation type isn't known.
        * @return a pointer to a new allocation of memory for the PositionVelocity object.
        */
    virtual PositionVelocity* NewPointer();
    /*! \brief Return a pointer to a copy of the PositionVelocity orbit state representation instance.
        *
        * \detail This is used to request memory for a copy of this instance of PositionVelocity. It is necessary 
        *	when attempting to get a pointer from the abstract data type OrbitStateRepresentation 
        *	and the actual representation type isn't known.
        * @return a pointer to a copy of the PositionVelocity object.
        */
    virtual PositionVelocity* Clone();

    
    virtual void SetState(const Vector &_State);
    virtual void SetState(const Vector &_Position, const Vector &_Velocity);
    virtual Vector GetState() const;
    virtual void GetState(Vector &_Position, Vector &_Velocity) const;

private:
    /*! 6x1 vector of position and velocity vector components (km, km/s) */
    Vector m_Elements;
};
} // close namespace O_SESSAME

#endif

// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: PositionVelocity.h,v $
*	Revision 1.7  2003/05/13 18:47:56  nilspace
*	Fixed comments for better formatting.
*	
*	Revision 1.6  2003/05/02 16:16:47  nilspace
*	Documented the API.
*	
*	Revision 1.5  2003/04/29 18:48:31  nilspace
*	Added NewPointer and Clone functions to help in getting the correct memory allocation.
*	
*	Revision 1.4  2003/04/24 20:19:31  nilspace
*	const'd all Get() functions.
*	
*	Revision 1.3  2003/04/23 18:52:29  nilspace
*	Updated to call correct OrbitFrame::GetRotation calls.
*	Added temporary PI and MU values.
*	Added K_Vector Values.
*	
*	Revision 1.2  2003/04/22 18:06:08  nilspace
*	Added math for Matthew Berry.
*	
*	Revision 1.1  2003/04/08 22:47:35  nilspace
*	Initial Submission.
*	
*
******************************************************************************/
