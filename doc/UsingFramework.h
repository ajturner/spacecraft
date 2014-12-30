/*! \page UsingOpenSESSAME Using the Open-SESSAME Framework
\ref TableOfContents
<hr>
    This section is meant to describe the design philosophy and methodology behind the <em>Open-Source, Extensible Spacecraft Simulation And Modeling Environment</em> Framework. It should give the reader a better understanding of the design of the framework and how to use it. 
  
  \section Philosophy
  No, this section is not for expounding upon the virtues of Plato or Kant or Nietzsche. What it is mean to convey is the philosophy behind the development of, and developing simulations with, the Open-SESSAME Framework. Hopefully this will give you a little better insight into the design of the framework, and how best to use, maintain, and extend it.
  
  First off, I think it is important to lay out the actual title of the framework:
  - <b>Open-Source</b> - the source is free (as in beer) and available for users and developers. Changes are propagated back to the community via the publicly hosted repository so the software continues to grow \& mature.
  
  - <b>Extensible</b> - the framework is designed with the premise that functionality will be added as necessary by new users and developers. The code is plainly written and well-documented to ease understanding of the source, and also encourages development via @em hotspots, points which assist in adding functionality (ie environmental disturbance functions, dynamic equations, kinematic representations, etc.)
  
  - <b>Spacecraft</b> - Open-SESSAME is developed with the target of simulating spacecraft and satellites in outer space. While there are generic mathematical and operational toolboxes (matrix, rotation, XML storage) as part of the software package, these libraries were developed or interfaced with the given goal in mind.
  
  - <b>Simulation And Modeling</b> - Simulation is providing a user with a non-real, but approximated environment that accurately corresponds to the real-world. Modeling is the creation of the physical dynamics and characteristics of this simulated world. Open-SESSAME is meant to be used as both a stand-alone model of spacecraft, and for use in creating simulations which interact with hardware and other software programs. 
  
  - <b>Environment</b> - the environment is the entire collection of dynamics, disturbances, data handling operations and interfaces that allow the user to interact with the simulation.
  
  - <b>Framework</b> - Open-SESSAME is a framework. It provides the tools and libraries that are combined together to create a simulation environment. By themselves they do not constitute an application, but must be joined by the user/developer in a meaningful way to simulate and analyze their particular problem. 
  
  \section Methodology
    So how do you actually create a simulation? A complete Open-Sessame simulation application (remember, Open-Sessame is just a framework, it is up to you to develop the application) consists of the following parts:
    - Attitude dynamics equation
    - Attitude kinematics equation
    - Orbit dynamics equation
    - Environmental disturbance torque \& force functions (may include a central body)
    - Physical object definition (mass, moments of inertia, ballistic coefficient, etc)
    - Propagator defining the coupling of the attitude \& orbit dynamics
    - Integrators (both orbital & attitude) and Interpolators
    - Data handling (history, saving, restoring, graphical output, input)
    - Communications (only if running on distributed machines or using hardware)
    
    Each of these components is implemented in one of the various toolboxes that compose the Open-Sessame Framework. The user must build the appropriate component (for example, writing the right-hand side of the attitude dynamics equation using momentum wheels) using the toolboxes and examples. These are then brought together in a main function to facilitate communication between the components to run the simulation. See \ref Examples for more help.
    
    \section Components Framework Components
    Below is a UML-esque diagram showing the Open-Sessame simulation application architecture. Components are color coded as follows:
    - @em Purple: #RotationLibrary
    - @em Blue: Attitude toolkit
    - @em Pink: Orbit toolkit
    - @em Green: Environment library
    - @em Brown: Dynamics library
    - @em Yellow: Data Handling library
    
    \image html Open-SESSAME_Architecture.jpg
    \image latex Open-SESSAME_Architecture.pdf "Open-Sessame Framework Architecture"
    
    Simple arrows indicate a "@em has-a" relationship (OrbitState has an OrbitRep and an OrbitFrame).
    Empty arrow heads indicate a derived class, or "@em is-a" (Quaternion is a Vector), and therefore has all the same functionality of the base class (Quaternion has all the funcionality of a Vector, as well as any more implemented in the Quaternion class itself).
    
    The components (each of the boxes) are coupled as shown to implement an actual spacecraft simulation application for modeling \& analysis. 
*/
