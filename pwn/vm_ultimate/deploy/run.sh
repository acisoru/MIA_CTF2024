#!/bin/sh
socat tcp-listen:1777,reuseaddr,fork exec:"./ultimate_vm"

