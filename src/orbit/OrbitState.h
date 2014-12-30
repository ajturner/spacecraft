//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file OrbitState.h
*  \brief Interface to the OrbitState class.
*  \author $Author: rsharo $
*  \version $Revision: 1.10 $
*  \date    $Date: 2003/10/18 21:37:28 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/* 
* 
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __SSF_ORBIT_STATE_H__
#define __SSF_ORBIT_STATE_H__

#include "orbitframes/OrbitFrame.h"
#include "orbitstaterep/OrbitStateRepresentation.h"

namespace O_SESSAME {

/*! \brief Encapsulation of an Orbit State, including its coordinate type and reference frame.
* \ingroup OrbitToolkit
*
* \detail The OrbitState class is an abstract representation of a current orbital state, including 
*	its position and velocity (in some OrbitStateRepresentation) and respective frame (OrbitFrame). 
*	Each instance of OrbitState is a snapshot of the spacecraft at an instant in time.
*
*	\par Example:
    \code
        OrbitState myOrbitState;
    myOrbitState.SetStateRepresentation(new PositionVelocity);
    myOrbitState.SetOrbitFrame(new OrbitFrameIJK);
    Vector initPV(6);
        // Space station
        initPV(VectorIndexBase+0) = -5776.6; // km
        initPV(VectorIndexBase+1) = -157; // km       
        initPV(VectorIndexBase+2) = 3496.9; // km    
        initPV(VectorIndexBase+3) = -2.595;  // km/s
        initPV(VectorIndexBase+4) = -5.651;  // km/s        
        initPV(VectorIndexBase+5) = -4.513; // km/s
    myOrbitState.SetState(initPV);
    \endcode
*
*	\todo should OrbitState contain an ssfTime object?
*	\todo change to be a template class of the Representation Types
*/
class OrbitState
{
public:
    /*! \brief Create an initially empty orbit state object */
    OrbitState();
    /*! \brief Default deconstructor. Deletes any unused variables. */
    virtual ~OrbitState();
    /*! \brief Create an orbit state from a copy of another orbit state. */
    OrbitState(const OrbitState &_OrbStateCopy);
    
    /*! \brief Create an orbit state object from a pointer to an orbit representation (positionVelocity, keplerian, etc), and orbit frame (IJK, PQW, etc.)
        * @param _pOrbRep the orbit representation (positionVelocity vector, keplerian elements, etc.) to store in the state.
        * @param _pOrbFrame the orbit frame (IJK, SEZ, PQW, etc) that is the reference frame of the representation.
        */
    OrbitState(OrbitStateRepresentation* _pOrbRep, OrbitFrame* _pOrbFrame = NULL);
    
    /*! \brief Set (or Change) the stored orbit frame that is the reference for the represenation.
        *
        * \detail In the future, this will convert the orbit representation from the previous frame (if defined) to the new frame.
        * \todo Implement the orbit representation conversion due to an orbit frame change.
        * @param _pnewOrbitFrame pointer to the orbit frame to set or convert the orbit representation to. 
        */
    void SetOrbitFrame(OrbitFrame* _pnewOrbitFrame);
    
    /*! \brief Returns the pointer to the current reference frame of the orbit state.
        * @return pointer to the current reference frame
        */
    OrbitFrame* GetOrbitFrame() const;
    
    /*! \brief Set (or change) the orbit state's representation.
        * @param _pStateRep pointer to the new orbit state representation.
        */
    void SetStateRepresentation(OrbitStateRepresentation* _pStateRep);
    
    /*! \brief Set (or change) the orbit state's representation and reference frame.
        * @param _pStateRep pointer to the new orbit state representation.
        * @param _pOrbFrame pointer to the orbit frame to set or convert the orbit representation to. 
        */
    void SetStateRepresentation(OrbitStateRepresentation* _pStateRep, OrbitFrame* _pOrbFrame);
    
    /*! \brief Return a pointer to the orbit state's current state representation.
        * @return pointer to the current representation (positionVelocity vector, keplerian elements, etc.)
        */
    OrbitStateRepresentation* GetStateRepresentation() const;

    /*! \brief Calculates the orbit angular momentum at the current orbit state.
        *
        * \f[ {\bf} h = |{\bf r} \times {\bf v}| \f]
        * @return the orbit angular momentum.
        */
    double GetOrbitAngularMomentum() const;
    
    /*! \brief internally set the orbit representation's state.
        * \warning Depracated - do not use - will be moving to private.
        * @param _state Vector of the state components that are the same type of the orbit state representation.
        */
    void SetState(const Vector& _state);

    /*! \brief internally set the orbit representation's state and reference frame.
        * \warning Depracated - do not use - will be moving to private.
        * @param _state Vector of the state components that are the same type of the orbit state representation.
        * @param _pOrbFrame pointer to the orbit frame to set or convert the orbit representation to. 
        */
    void SetState(const Vector& _state, OrbitFrame* _pOrbFrame);
    
    /*! \brief internally return the orbit representation's state Vector.
        * \warning Depracated - do not use - will be moving to private.
        * @return Vector of the state components that are the same type of the orbit state representation.
        */
    Vector GetState() const;
    
    /*! \brief Copy an instance of OrbitState.
        * @param _OrbStateCopy right operand that is the original orbit state to be copied.
        * @return a copy of the orbit state.
        */
    OrbitState operator= (const OrbitState& _OrbStateCopy);
private:
    /*! \brief internal pointer to the current orbit state representation */
    OrbitStateRepresentation* m_pOrbitStateRepresentation;
    /*! \brief internal pointer to the current orbit state reference frame */
    OrbitFrame* m_pOrbitFrame;
};

/* Possibility of turning into a template class
OrbitState<PositionVelocity, OrbFrameIJK> initialOrbit1;
OrbitState<Keplerian, OrbFrameSEZ> initialOrbit1.ChangeType();
vs.
OrbitState initOrb1(POSITION_VELOCITY, ORBFRAME_IJK);
initOrb1.ChangeType(KEPLERIAN);
initOrb1.GetKeplerianElements();

template <TOrbRep, TOrbFrame>
class OrbitState
{
public:
    OrbitState();
    virtual ~OrbitState();
    OrbitState(const Vector& _State);
    
//    void SetOrbitFrame(const TOrbFrame &_newOrbitFrame);
    const TOrbFrame& GetOrbitFrame() const;
    
//    void SetStateRepresentation(const TOrbRep &_StateRep);
//    void SetStateRepresentation(const TOrbRep &_StateRep, const TOrbFrame &_orbFrame);
    const TOrbRep& GetStateRepresentation() const;

    void SetState(const Vector &_state);
    const Vector& GetState() const;
    
private:
    TOrbRep m_OrbitStateRepresentation;
    TOrbFrame m_OrbitFrame;

};
*/
} // close namespace O_SESSAME

#endif

// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: OrbitState.h,v $
*	Revision 1.10  2003/10/18 21:37:28  rsharo
*	Removed "../utils" from all qmake project paths. Prepended "utils
*	/" to all #include directives for utils. Removed ".h" extensions from STL header
*	s and referenced STL components from "std::" namespace.  Overall, changed to be
*	more portable.
*	
*	Revision 1.9  2003/06/12 23:08:20  nilspace
*	Fixed to calculate angular momentum.
*	
*	Revision 1.8  2003/06/12 18:02:15  nilspace
*	Added GetAngularVelocity() function.
*	
*	Revision 1.7  2003/05/22 14:33:58  nilspace
*	Added NULL default value to constructor.
*	
*	Revision 1.6  2003/05/13 18:46:29  nilspace
*	Checked pointers if they were initialized before calling.
*	
*	Revision 1.5  2003/05/02 16:16:46  nilspace
*	Documented the API.
*	
*	Revision 1.4  2003/04/29 20:56:25  nilspace
*	Update to work with Propagator.
*	
*	Revision 1.3  2003/04/29 18:47:31  nilspace
*	Added copy constructor and operator= functions.
*	
*	Revision 1.2  2003/04/23 16:26:02  nilspace
*	Updated directory structure & default parameters.
*	
*	Revision 1.1  2003/04/08 22:47:00  nilspace
*	Initial Submission.
*	
*	
*
******************************************************************************/
