#!coding utf-8
import os

file = '/var/lib/jenkins/workspace/test_cplusplus/log.txt'
if os.path.exists(file):
      print 'success'
else:
      print 'failure'
