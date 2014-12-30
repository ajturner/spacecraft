//////////////////////////////////////////////////////////////////////////////////////////////////
/*! \file Environment.cpp
*  \brief Implementation of the Environment encapsulation object.
*  \author $Author: nilspace $
*  \version $Revision: 1.8 $
*  \date    $Date: 2003/06/12 18:06:35 $
*//////////////////////////////////////////////////////////////////////////////////////////////////
/* 
*
*/
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "Environment.h"
#include "CentralBody/CentralBody.h"
namespace O_SESSAME {
    
/*! \brief Create an instance of Environment */
Environment::Environment() : m_CalculatedForces(3), 
                             m_CalculatedTorques(3), 
                             m_ForcesFunctor(const_cast<Environment*>(this), &Environment::GetForces),
                             m_TorquesFunctor(const_cast<Environment*>(this), &Environment::GetTorques)
{
    m_pCB = NULL;
}
    
/*! \brief Default Deconstructor */
Environment::~Environment()
{
    if(m_pCB)
        m_pCB->ReleaseReference();
}

    /*! \brief Evaluate the current disturbance torques given a state. 
        * @param _currentTime current time to evaluate at.
        * @param _currentOrbitState current orbital state.
        * @param _currentAttitudeState current attitude state.
        * @return 3-element vector of disturbance torques in the body frame (N).
        */
Vector Environment::GetTorques(const ssfTime& _currentTime, const OrbitState& _currentOrbitState, const AttitudeState& _currentAttitudeState)
{
    m_CalculatedTorques.setToValue(0);
    m_funcIterator = m_TorqueFunctions.begin();
    while (m_funcIterator != m_TorqueFunctions.end())
    {
        m_CalculatedTorques += (*m_funcIterator).Evaluate(_currentTime, _currentOrbitState, _currentAttitudeState);
        ++m_funcIterator;
    }
    return m_CalculatedTorques;
}

    /*! \brief Evaluate the current disturbance forces given a state. 
        * @param _currentTime current time to evaluate at.
        * @param _currentOrbitState current orbital state.
        * @param _currentAttitudeState current attitude state.
        * @return 3-element vector of disturbance forces in the body frame (N).
        */
Vector Environment::GetForces(const ssfTime& _currentTime, const OrbitState& _currentOrbitState, const AttitudeState& _currentAttitudeState)
{
    m_CalculatedForces.setToValue(0);
    m_funcIterator = m_ForceFunctions.begin();
    while (m_funcIterator != m_ForceFunctions.end())
    {
        m_CalculatedForces += (*m_funcIterator).Evaluate(_currentTime, _currentOrbitState, _currentAttitudeState);
        ++m_funcIterator;
    }
    return m_CalculatedForces;
}
    
    /*! \brief Set the pointer to the central body to use for modeling the environment.
        * @param _pCB pointer to the CentralBody object.
        */
void Environment::SetCentralBody(CentralBody *_pCB)
{
    m_pCB = _pCB;
    return;
}

    /*! \brief Get the pointer to the environment's central body.
        * @return pointer to the CentralBody object.
        */
const CentralBody* Environment::GetCentralBody() const
{
    return m_pCB;
}
    
    /*! \brief Add a force disturbance function to the list of force functions
        * @param _forceFunc Pointer to a force function that matches the EnvFunction prototype.
        */
void Environment::AddForceFunction(const EnvFunction &_forceFunc)
{
    // iterate through the set of Force Functions to prevent duplication.
    /** \todo Check to prevent overlapping force functions *//*
    m_funcIterator = m_ForceFunctions.begin();
    while (m_funcIterator != m_ForceFunctions.end())
    {
        if(*m_funcIterator == _forceFunc)
            return;
    }*/
    m_ForceFunctions.push_back(_forceFunc);
    return;
}
    /*! \brief Add a torque disturbance function to the list of force functions
        * @param _forceFunc Pointer to a torque function that matches the EnvFunction prototype.
        */
void Environment::AddTorqueFunction(const EnvFunction &_torqueFunc)
{
    // iterate through the set of Torque Functions to prevent duplication.
    /** \todo Check to prevent overlapping torque functions *//*
    m_funcIterator = m_TorqueFunctions.begin();
    while (m_funcIterator != m_TorqueFunctions.end())
    {
        if(*m_funcIterator == _torqueFunc)
            return;
    }*/
    m_TorqueFunctions.push_back(_torqueFunc);
    return;
}
    
    /*! \brief Get the reference to the Environment::GetForces() function.
        * @return reference to the environment's GetForces() function.
        */
const Functor& Environment::GetForceFunction() const
{
    return m_ForcesFunctor;
}

    /*! \brief Get the reference to the Environment::GetTorques() function.
        * @return reference to environment's GetTorques() function.
        */
const Functor& Environment::GetTorqueFunction() const
{
    return m_TorquesFunctor;
}
//////////////////////////////////////////////////////
// EnvFunction Member Functions
//////////////////////////////////////////////////////
    /*! \brief Create a disturbance function. 
        *
        *  Example: EnvFunction DragForce(&myDisturbanceFunction);
        * @param _EnvFuncPtr pointer to an environmental disturbance function. 
        */
EnvFunction::EnvFunction(pt2EnvFunc _EnvFuncPtr) : m_NumParameters(0) , m_EnvFuncParameters(m_NumParameters)
{
    m_EnvFuncPtr = _EnvFuncPtr;
}
    /*! \brief Create a disturbance function with a set number of parameters.
        *
        *  Example: EnvFunction DragForce(&myDisturbanceFunction, 2);
        * @param _EnvFuncPtr pointer to an environmental disturbance function. 
        * @param _numParameters number of parameters that are passed to the disturbance function.
        */
EnvFunction::EnvFunction(pt2EnvFunc _EnvFuncPtr, const int &_numParameters) : m_NumParameters(_numParameters) , m_EnvFuncParameters(m_NumParameters)
{
    m_EnvFuncPtr = _EnvFuncPtr;
}
    /*! \brief Evaluate the disturbance function at a specific state.
        *  Used to calculate the actual force or torque disturbance given the time, orbit state and attitude state.
        * @param _currentTime current time to evaluate at.
        * @param _currentOrbitState current orbital state.
        * @param _currentAttitudeState current attitude state.
        * @return 3-element vector of forces (N) or torques (Nm) from the disturbance at the specified state. 
        */
Vector EnvFunction::Evaluate(const ssfTime& _currentTime, const OrbitState& _currentOrbitState, const AttitudeState& _currentAttitudeState)
{
    return m_EnvFuncPtr(_currentTime, _currentOrbitState, _currentAttitudeState, m_EnvFuncParameters);
}

    /*! \brief Add a parameter to the parameter list.
        *
        *  The parameter is inserted in the specified position in the list of parameters, pushing any other parameters back. The list of parameters is passed into the disturbance function (ie mass, ballistic coefficient, magnetic dipole)
        *	<h4>Example:</h4> MagneticForce.AddParameter(reinterpret_cast<void*>(Spacecraft.GetDipole(), 2); where the GetDipole() function returns by reference.
        *	<p>If a parameter position is given that is beyond the last position, the parameter will be put in the last position, the intermediate parameters will be filled with empty parameters.
        * \warning Make sure the variable that you are passing in as a parameter will stay in scope during the disturbance function calls.
        * @param _parameter pointer to the data where the pertinent variable is stored. 
        * @param _paramNumber Position in the list of parameters. If none is specified, the parameter is put at the end.
        */
void EnvFunction::AddParameter(void* _parameter, int _paramNumber)
{
    if (_paramNumber > m_NumParameters)
    {    
        // Calculate the number of parameters "missing" to be temporarily filled
        int delta = _paramNumber - m_NumParameters;
        if(delta > 1)
        {
            for(int ii = 1; ii < delta; ++ii)
            {
                m_EnvFuncParameters.push_back(0);
            }
        }
        m_EnvFuncParameters.push_back(_parameter);
    }
    else
        m_EnvFuncParameters.insert(m_EnvFuncParameters.begin() + _paramNumber - 1, _parameter);
    
    m_NumParameters = _paramNumber;

}
    
    /*! \brief Changes what a parameter in the list points to.
        *  
        * @param _parameter pointer to the data where the pertinent variable is stored. 
        * @param _paramNumber Position in the list of parameters. If none is specified, the parameter is put at the end.
        */
void EnvFunction::ChangeParameter(void* _parameter, int _paramNumber)
{
    RemoveParameter(_paramNumber);
    AddParameter(_parameter, _paramNumber);
}

    /*! \brief Removes a parameter from the parameter list.
        *
        *  the parameters following the removed parameters will all move down one step to "fill the spot".
        *	<p>If no position is specified, the last parameter in the list is removed.
        *	<p>If a position is given that is greater than the number of parameters, nothing happens to the list.
        * 	<h4>Example:</h4> ParameterList = [Area, Dipole, Mass], RemoveParameter(2); ParameterList = [Area, Mass]
        * @param _paramNumber Position of the parameter to be removed. If none is specified, remove the last parameter in the list.
        */
void EnvFunction::RemoveParameter(int _paramNumber)
{
    if(_paramNumber <= m_NumParameters)
        m_EnvFuncParameters.erase(m_EnvFuncParameters.begin()+_paramNumber);
    else if(_paramNumber == -1)
        m_EnvFuncParameters.pop_back();
    else
        return;
    
    --m_NumParameters;
}
} // close namespace O_SESSAME

// Do not change the comments below - they will be added automatically by CVS
/*****************************************************************************
*	$Log: Environment.cpp,v $
*	Revision 1.8  2003/06/12 18:06:35  nilspace
*	.
*	
*	Revision 1.7  2003/06/10 15:58:52  nilspace
*	GetTorques now incrementes the function iterator.
*	
*	Revision 1.6  2003/05/22 03:42:32  nilspace
*	Moved documentation to the implementation file.
*	
*	Revision 1.5  2003/05/13 18:59:16  nilspace
*	Fixed some comments.
*	
*	Revision 1.4  2003/05/05 20:45:46  nilspace
*	Changed the pass-by-address parameters to pass-by-reference.
*	
*	Revision 1.3  2003/05/02 02:16:29  nilspace
*	Documented the API.
*	Added a GetTorquesFunction().
*	
*	Revision 1.2  2003/04/27 22:04:33  nilspace
*	Created the namespace O_SESSAME.
*	
*	Revision 1.1  2003/04/08 22:37:22  nilspace
*	Initial Submission.
*	
*
******************************************************************************/
