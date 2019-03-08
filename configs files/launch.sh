#!/bin/bash
#create the vm and activate pml
#xl create conf_hadoop.cfg
xl create conf.cfg
#xl enable-log-dirty 1

#pin the cpus
xl vcpu-pin 0 0 0
xl vcpu-pin 0 1 1
#xl vcpu-pin 0 2 3
#xl vcpu-pin 0 3 3

