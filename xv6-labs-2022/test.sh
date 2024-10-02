#!/bin/sh

expr `id -u` % 5000 + 25000
