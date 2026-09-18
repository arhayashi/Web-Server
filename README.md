# Web Server

## Overview

This repository contains code for a web server built entirely in C. It uses
network sockets to listen for incoming HTTP requests and creates the
corresponding HTTP response.

## Features 

Some notable features include the following:

- Automatic index.html serving
- File caching
- 404 response page
- Server logging

## Things to Try

## Usage

First, clone or download and unzip the repository. Then, `cd` into `src` and 
run `make all`. Finally, run `./server`. The server will be running on port
3000 by default, and can be accessed via a web browser through
`http://localhost:3000`.
