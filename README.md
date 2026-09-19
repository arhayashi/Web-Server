# Web Server

## Overview

This repository contains code for a web server built entirely in C. It uses
network sockets to listen for incoming HTTP requests and creates the
corresponding HTTP response. It also provides logs to the terminal so that you
can see what the web server is doing.

## Features 

Some notable features include the following:

- Automatic index.html serving
- File caching
- 404 not found page
- Server logging to the terminal

## Things to Try

- Visit `http://localhost:3000` to see an example of automatic index.html 
serving
- Visit `http://localhost:3000/cat.jpeg` to see a cute cat image
- Visit a non-existent page to view the 404 not found page

## Usage

First, clone or download and unzip the repository. Then, `cd` into `src` and 
run `make all`. Finally, to start the server, run `./server`. The server will
be running on port 3000 by default, and can be accessed via a web browser
through `http://localhost:3000`.
