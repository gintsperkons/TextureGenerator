#!/bin/bash

echo "Running setup.sh..." 
./setup.sh &&

echo "Running Make..."
make &&

echo "Running run.sh..."
./run.sh &&

echo "All steps completed."
