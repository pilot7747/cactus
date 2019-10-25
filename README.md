# Cactus

## What is it?
Cactus is a simple distributed task queue. It written in C++ and has CLI API (will support Python in future). System has one master node recieving tasks and sending them to wokreks.

Why not OpenMP, Hadoop, etc? Cactus is very tiny but scallabe and very crossplatform because it needs only Protocol Buffers and HTTP server so it can run on any device including mobiles.

## Installation

__Requirements:__ Boost, Protobufs, clang or g++ compiler, make.

__Installation:__ just make.

## Usage
`cactus-master` is a master part, just run it like

`cactus-master <ip> <port>`


`cactus` is CLI API. Usage:

`cactus run 'ls /'
