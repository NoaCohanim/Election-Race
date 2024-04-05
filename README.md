# Coalition Race Simulation in C++

## Overview
This project simulates the "Coalition Race" in SPLand, a faraway democracy facing a political crisis. The goal is to help politicians form a government coalition efficiently. The program is written in C++ and focuses on memory management using classes, standard data structures, and C++ features such as the "Rule of 5".
I've worked on this project as a 2nd year stuednt in "System Programing Languages" course.

## Assignment Goals
- **Design an object-oriented system in C++.
- Gain implementation experience while handling memory management and avoiding memory leaks.
- Implement efficient solutions using standard data structures.
- Utilize C++ features such as the "Rule of 5" for managing resources.

## Assignment Definition
In SPLand, the president decided to change the method of forming a coalition after 5 elections. Now, multiple "agents" from different parties compete to create a coalition of at least 61 seats as fast as possible.

### Components
- Parties: Represented as vertices in a graph.
- Collaborations: Represented as edges between parties. Each collaboration has a "similarity score" as the edge weight.
- Agents: Belong to a party and make offers to adjacent parties to join a coalition.

### Input Configuration
- Config file in JSON format.
- Includes party details (id, name, mandates, join policy), graph structure, and agent details (id, party id, selection policy).

### Simulation Process
1. Agents offer adjacent parties to join their coalition.
2. When a party accepts an offer, it joins the coalition and clones the offering agent to assist.
3. The simulation continues until a coalition with at least 61 seats is formed or until failure.

## Implementation Details
- Graph Representation: Utilizes standard data structures to represent parties and collaborations.
- Memory Management: Implements the "Rule of 5" to handle resource management efficiently and avoid memory leaks.
- Efficiency: Focuses on efficient algorithms and data structures to simulate the coalition formation process quickly.

## Usage
1. Compile the program using a C++ compiler.
2. Provide the input configuration file in JSON format.
3. Run the executable to start the simulation.
4. View the output to see the first coalition formed or report failure.

## Example
```cpp
// Sample code snippet demonstrating the simulation process

// Read input configuration from JSON file
Config config = readConfig("input.json");

// Initialize the simulation with the provided configuration
CoalitionSimulator simulator(config);

// Start the simulation
simulator.run();

// Display the result
simulator.displayResult();
