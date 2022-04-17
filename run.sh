#!/bin/bash

exec >& >(tee run.log)

make
