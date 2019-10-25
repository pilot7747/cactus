# Cactus

## What is it?
Cactus is a simple distributed task queue. It is written in C++ and has CLI API (will support Python in the future). The system has one master node receiving tasks and sending them to workers.

Why not OpenMP, Hadoop, etc? Cactus is very tiny but scalable and very cross-platform because it needs only Protocol Buffers and HTTP server so it can run on any device including mobiles.

## Installation

__Requirements:__ Boost, Protobufs, clang or g++ compiler, make.

__Installation:__ just make.

## Usage
`cactus-master` is a master part, just run it like

`cactus-master <ip> <port>`

Run workers by following command:

`cactus-worker <master-ip> <port>`


`cactus` is CLI API. Usage:

`cactus run 'ls /'`
