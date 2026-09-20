# COS-214-Practical-5

# Campus Guard: Emergency Response Coordination 🚨

**Course:** COS 214 - Practical 5 (2026)  
**Language:** C++11  
**Team Members:** Lwandiso, [Member 2 Name], [Member 3 Name]  

## About the Project
CampusGuard is an emergency-response coordination platform designed for a large university campus. During a campus incident, multiple operational units—such as security teams, medical responders, facilities staff, and access-control systems—need to coordinate quickly and effectively. 

Some of these systems are modern, while others rely on legacy or externally managed interfaces. The goal of this project is to build a cohesive C++11 application that manages the lifecycle of an incident from reporting to resolution, without tightly coupling every component to one another.

## What We Are Building
We are designing and implementing an integrated object-oriented system that demonstrates practical, scenario-driven usage of Gang of Four (GoF) design patterns. Instead of isolated textbook examples, our patterns will collaborate to form a single, working application.

**Core System Features:**
*   Registering and updating the status of campus incidents.
*   Dispatching response units (security, medical, facilities).
*   Managing building access (locking, unlocking, restricting areas).
*   Executing complex emergency workflows.
*   Integrating an incompatible legacy/external service.

**Architectural Patterns Used:**
*   **Command:** To encapsulate operator requests (e.g., dispatching units, issuing alerts) as standalone objects.
*   **Mediator:** To coordinate communication between response components without direct many-to-many dependencies.
*   **Adapter:** To integrate legacy or external communication services into the CampusGuard interface.
*   **Facade:** To provide a simplified, high-level interface for complex multi-step emergency workflows.
*   **[Chosen Pattern 1]:** *(To be updated after team discussion)*
*   **[Chosen Pattern 2]:** *(To be updated after team discussion)*

## Build and Execution Instructions (Docker)
This project is containerized to ensure a consistent build and runtime environment for demonstration and assessment. 

To build and run the complete CampusGuard application, ensure you have Docker installed and run the following command in the root directory:

```bash
docker compose up --build
```

This command will compile the source code using the provided `Makefile` via `std=c++11` and execute the integrated runtime scenarios. Memory management and leak checks have been verified using Valgrind.