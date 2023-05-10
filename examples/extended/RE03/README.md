# RE03 - An extended example for run and event

Example adapted from /extended/runAndEvent/RE03

## Introduction

This example demonstrates how to use UI-command base scoring. It create parallel world(s) for defining scoring mesh(es).

Due to some performance overhead, this functionality is not 
provided by default. To get it included, the pointer to 
G4ScoringManager must be accessed. The access to the static 
method G4ScoringManager::GetScoringManager() activates this 
functionality. 

## Geometry and primary particle
It has just one water box in the world volume filled by air.
No detector in the mass geometry. Particle gun shoots a gamma
into the water box.

## Physics
The physics list is taken from referenced physics-list FTFP_BERT
in Geant4.
